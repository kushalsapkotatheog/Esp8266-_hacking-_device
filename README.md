🧠 Project Description:
This project is a Wi-Fi Evil Twin Attack Simulator built using an ESP8266 microcontroller. It creates a fake wireless access point (AP) mimicking public hotspots like "Free_World_Link_1_HOUR", and serves a captive portal phishing page to collect target device credentials or redirect them to a custom IP address. It includes a web-based admin panel for dynamic SSID and redirect configuration without re-uploading code.

💡 Features:
📡 Creates a Rogue Wi-Fi Access Point with a custom SSID (e.g., Free_World_Link_1_HOUR)

🧠 Captive Portal and DNS Hijacking – all requests are redirected to the ESP for phishing or spoofing.

🌐 Admin Panel via Web UI at http://192.168.4.1/admin

Change redirect IP (e.g., 192.168.4.69)

Change broadcasted SSID

💾 EEPROM Storage – settings are stored persistently across reboots.

🚀 Auto-redirect unknown requests to a custom phishing site or fake login page.

🧭 Uptime and IP info shown in dashboard.

🔒 No internet dependency — runs locally on the ESP8266.

⚙️ Hardware Requirements:
✅ ESP8266 board (e.g., NodeMCU, Wemos D1 Mini)

✅ Micro-USB cable

✅ PC with Arduino IDE

✅ Wi-Fi-enabled device (for testing: phone, PC, etc.)

📦 Software & Libraries Used:
ESP8266WiFi.h

DNSServer.h

ESP8266WebServer.h

EEPROM.h

Arduino IDE with ESP8266 board support

🛠 Setup Instructions:
Flash the code to your ESP8266 using Arduino IDE.

ESP broadcasts a fake Wi-Fi network named Free_World_Link_1_HOUR.

When someone connects, any site they try to visit redirects to your set redirect target (192.168.4.69, configurable).

Admin can visit http://192.168.4.1/admin to modify settings.

⚠️ Legal Disclaimer:
This tool is for educational and research purposes only. Unauthorized use of this code in real-world networks may be illegal. Always get explicit permission before testing on any network you do not own.

✨ Credits:
Made by Kushal
Custom firmware & UI design by Kushal
Built with love, curiosity, and a little mischief. 😄
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

