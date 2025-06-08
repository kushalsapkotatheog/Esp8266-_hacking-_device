# 🛰️ ESP8266 Evil Twin Wi-Fi Simulator

A **Wi-Fi Evil Twin Attack Simulator** built on the ESP8266 that creates a rogue wireless hotspot mimicking open public networks. It hijacks DNS requests and serves a configurable phishing or redirect page, complete with an admin control panel and persistent settings.

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

---

## 🔥 Flash via Web Browser

Want to flash it **without Arduino IDE**? Use [ESP Web Tools](https://esp.huhn.me/) — just connect your ESP8266 via USB and click the button below:

👉 **[Flash with ESP Web Tools](https://esp.huhn.me/)**  
> Compatible with Chrome / Edge / Opera on desktop (not mobile)

---

## 🧠 Project Description

This project is a **Wi-Fi Evil Twin Attack Simulator** built using an ESP8266 microcontroller.  
It creates a fake wireless access point (AP) mimicking public hotspots like **"Free_World_Link_1_HOUR"**, and serves a captive portal phishing page to collect credentials or redirect traffic to any custom IP.

Includes a full web-based admin panel at `http://192.168.4.1/admin` to modify SSID and redirect target live — no reupload needed!

---

## 💡 Features

- 📡 **Fake Wi-Fi Access Point** with custom SSID (e.g. `Free_World_Link_1_HOUR`)
- 🧠 **Captive Portal + DNS Hijacking**: all domains resolve to the ESP
- 🌐 **Web Admin Panel**: change SSID & redirect address at runtime
- 💾 **EEPROM Storage**: saves settings across reboots
- 🚀 **Auto-redirect** clients to phishing/fake login site
- 🧭 **Dashboard**: Uptime, IP, and current config shown
- 🔒 **Offline**: Works standalone without internet

---

## ⚙️ Requirements

### Hardware
- ✅ ESP8266 board (NodeMCU, Wemos D1 Mini, etc.)
- ✅ Micro-USB cable
- ✅ Any Wi-Fi-enabled device (for testing)
- ✅ Computer with USB

### Software / Libraries
- [ESP8266 core for Arduino](https://github.com/esp8266/Arduino)
- `ESP8266WiFi.h`, `DNSServer.h`, `ESP8266WebServer.h`, `EEPROM.h`

---

## 🛠 How to Use

1. **Flash firmware** using [ESP Web Tools](https://esp.huhn.me/) or Arduino IDE.
2. ESP will broadcast a Wi-Fi named:  
   🟡 `Free_World_Link_1_HOUR`
3. Connect with any device (PC or phone).
4. Any URL visited will redirect to:  
   🔴 `http://192.168.4.69` (default — editable)
5. To manage settings, open:  
   🔧 `http://192.168.4.1/admin`

---

## ✍️ Customize

In the web admin panel you can:
- Change **Redirect Target** (e.g. `192.168.4.69:8080`)
- Change **Wi-Fi SSID**
- Save changes — device reboots and applies immediately

---

## ⚠️ Disclaimer

> This tool is for **educational and research** purposes **only**.  
> **Do not deploy** on networks you don’t own or have **explicit permission** to test.  
> Misuse of this code may violate **local laws**.

---

## ✨ Credits

- **Made by Kushal**  
- Custom firmware & UI design by **Kushal**  
- Built with love, curiosity, and a little mischief 😄

---

## 📜 License

This project is licensed under the **MIT License**.  
See [`LICENSE`](./LICENSE) file for full terms.
