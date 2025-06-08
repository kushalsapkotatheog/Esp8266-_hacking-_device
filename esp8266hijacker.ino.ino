/*
  ESP8266 WiFi Hotspot with Redirect Admin Panel
  - Creates a WiFi Access Point with configurable SSID
  - Redirects all clients to a configurable target IP:Port
  - Admin panel at http://192.168.4.1/admin to change settings
  - Settings saved in EEPROM for persistence

  Made by Kushal
*/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String redirectTarget = "";
String ssidName = "FreeWiFi_Access";
unsigned long startMillis;

const int EEPROM_SIZE = 256;
const int REDIRECT_OFFSET = 0;
const int SSID_OFFSET = 128;
const int VERSION_OFFSET = 255;
const byte EEPROM_VERSION = 0x42;

String readFromEEPROM(int offset) {
  char data[128];
  for (int i = 0; i < 128; ++i) {
    data[i] = EEPROM.read(offset + i);
    if (data[i] == '\0') break;
  }
  return String(data);
}

void writeToEEPROM(int offset, String content) {
  for (int i = 0; i < 128; ++i) EEPROM.write(offset + i, 0);  // Clear
  for (int i = 0; i < content.length() && i < 127; ++i) {
    EEPROM.write(offset + i, content[i]);
  }
  EEPROM.write(offset + content.length(), '\0');
  EEPROM.commit();
}

String getUptime() {
  unsigned long seconds = (millis() - startMillis) / 1000;
  int h = seconds / 3600;
  int m = (seconds % 3600) / 60;
  int s = seconds % 60;
  return String(h) + "h " + m + "m " + s + "s";
}

const char* adminPage = R"====(
<!DOCTYPE html>
<html>
<head>
  <title>ESP8266 Admin</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: sans-serif; background: #121212; color: #eee; padding: 20px; }
    h2 { color: #03a9f4; }
    nav { margin-bottom: 20px; }
    nav a { padding: 10px 15px; text-decoration: none; color: white; background: #333; margin-right: 10px; border-radius: 5px; }
    nav a.active { background: #03a9f4; }
    section { display: none; }
    section.active { display: block; }
    input[type=text], input[type=submit] {
      width: 100%%; padding: 10px; margin: 8px 0; box-sizing: border-box;
    }
    input[type=submit] {
      background-color: #03a9f4; color: white; border: none;
      cursor: pointer; font-size: 16px;
    }
    .info-box { background: #1e1e1e; padding: 10px; border-radius: 8px; margin-bottom: 10px; }
  </style>
</head>
<body>
  <h2>ESP8266 Admin Panel</h2>
  <nav>
    <a href="#" onclick="showTab('dashboard')" id="tab-dashboard" class="active">Dashboard</a>
    <a href="#" onclick="showTab('settings')" id="tab-settings">Settings</a>
  </nav>

  <section id="dashboard" class="active">
    <div class="info-box">SSID: <b>%SSID%</b></div>
    <div class="info-box">Redirect Target: <b>%REDIRECT%</b></div>
    <div class="info-box">ESP IP: <b>%IP%</b></div>
    <div class="info-box">Uptime: <b>%UPTIME%</b></div>
  </section>

  <section id="settings">
    <form action="/save" method="POST">
      <label>Redirect to (IP:Port):</label>
      <input type="text" name="target" value="%REDIRECT%" placeholder="192.168.4.33:8080">

      <label>WiFi SSID Name:</label>
      <input type="text" name="ssid" value="%SSID%" placeholder="MyHotspot">

      <input type="submit" value="Save & Reboot">
    </form>
  </section>

  <script>
    function showTab(tab) {
      document.querySelectorAll('section').forEach(s => s.classList.remove('active'));
      document.querySelectorAll('nav a').forEach(a => a.classList.remove('active'));
      document.getElementById(tab).classList.add('active');
      document.getElementById('tab-' + tab).classList.add('active');
    }
  </script>
</body>
</html>
)====";

void sendAdminPage() {
  String page = adminPage;
  page.replace("%REDIRECT%", redirectTarget);
  page.replace("%SSID%", ssidName);
  page.replace("%IP%", WiFi.softAPIP().toString());
  page.replace("%UPTIME%", getUptime());
  webServer.send(200, "text/html", page);
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  startMillis = millis();

  // EEPROM version check and default init
  if (EEPROM.read(VERSION_OFFSET) != EEPROM_VERSION) {
    Serial.println("EEPROM not initialized. Setting defaults.");
    redirectTarget = "192.168.4.69";              // <-- Default redirect IP:Port
    ssidName = "Free_World_Link_1_HOUR";          // <-- Default WiFi SSID

    writeToEEPROM(REDIRECT_OFFSET, redirectTarget);
    writeToEEPROM(SSID_OFFSET, ssidName);
    EEPROM.write(VERSION_OFFSET, EEPROM_VERSION);
    EEPROM.commit();
  } else {
    redirectTarget = readFromEEPROM(REDIRECT_OFFSET);
    ssidName = readFromEEPROM(SSID_OFFSET);
    if (ssidName == "") ssidName = "FreeWiFi_Access";
  }

  // Start WiFi AP
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssidName.c_str());

  // Start DNS server for captive portal redirect
  dnsServer.start(DNS_PORT, "*", apIP);

  // Web server routes
  webServer.on("/admin", sendAdminPage);
  webServer.on("/save", HTTP_POST, []() {
    if (webServer.hasArg("target")) {
      redirectTarget = webServer.arg("target");
      writeToEEPROM(REDIRECT_OFFSET, redirectTarget);
    }
    if (webServer.hasArg("ssid")) {
      ssidName = webServer.arg("ssid");
      writeToEEPROM(SSID_OFFSET, ssidName);
    }
    webServer.send(200, "text/html", "<p>Settings saved. Rebooting...</p>");
    delay(2000);
    ESP.restart();
  });

  // Redirect all other requests to the redirectTarget IP:Port
  webServer.onNotFound([]() {
    if (redirectTarget.length() > 0) {
      webServer.sendHeader("Location", "http://" + redirectTarget, true);
      webServer.send(302, "text/plain", "");
    } else {
      webServer.send(200, "text/html", "<p>No redirect set. Go to <a href='/admin'>Admin Panel</a></p>");
    }
  });

  webServer.begin();
  Serial.println("Access Point started with SSID: " + ssidName);
  Serial.println("Admin panel at http://" + apIP.toString() + "/admin");
  Serial.println("Redirect target: " + redirectTarget);
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}