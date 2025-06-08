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
   <img src="https://github.com/user-attachments/assets/d761d7cd-2f3d-4ff4-8389-75fb55318c0a" alt="Redirect Default" width="300" />

**Redirecting**  
<img src="https://github.com/user-attachments/assets/41631b2e-baf2-43a3-b5a8-d845c4193313" alt="Redirecting" width="300" />

**Login**  
<img src="https://github.com/user-attachments/assets/3115bf53-53ac-4b1b-a169-984748138ea3" alt="Login" width="300" />

5. To manage settings, open:  
   🔧 `http://192.168.4.1/admin`  
   <img src="https://github.com/user-attachments/assets/190e4255-4cfa-4cb2-bfa2-75597b85c50c" alt="Admin Panel" width="300" />

---

## ✍️ Customize

In the web admin panel you can:  
- Change **Redirect Target** (e.g. `192.168.4.69:8080`)  
- Change **Wi-Fi SSID**  
- Save changes — device reboots and applies immediately  
<img src="https://github.com/user-attachments/assets/d0c76235-b328-41dd-99f3-4e578d837cc7" alt="Admin Settings" width="300" />

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
