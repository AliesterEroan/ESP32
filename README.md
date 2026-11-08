# ESP — ESP32 Arduino Sketch Collection

> A personal collection of standalone ESP32 sketches (Arduino IDE) covering WiFi, BLE, OLED displays, sensors, MQTT, QR scanning, and embedded web dashboards — experiment folder, not a single product.

Each subfolder is an independent sketch targeting the ESP32 (ESP-IDF/Arduino core). There is no shared build system: open any folder in the Arduino IDE (board: ESP32) and flash it. Sketches are a mix of completed demos and works-in-progress, with French and English comments.

---

## 📜 Table of Contents

- [✨ Features](#-features)
- [🚀 Installation](#-installation)
- [📖 Usage](#-usage)
- [🏗️ Architecture](#-architecture)
- [🛠️ Technologies Used](#-technologies-used)
- [⚠️ Limitations](#-limitations)
- [🔒 Privacy](#-privacy)
- [📜 License](#-license)
- [📧 Contact](#-contact)

---

## ✨ Features

### Connectivity
- **`AP_Mode/`** — ESP32 as a WiFi access point (`ESP32_Yessin` SSID); prints connected-station count to Serial every 2 s.
- **`LED_ble/`, `ble/`** — Bluetooth Classic (`BluetoothSerial`) LED control: ON/OFF/Blink modes from a paired phone; `LED_ble` broadcasts as `mohamed_ESP32_Terminal`.
- **`QR_Code_Wifi_Station_Mode/`, `QR_Code/`** — WiFi station-mode sketches that display a QR code for provisioning.
- **`MQTT_Weather_Logger/`** — full MQTT node: DHT22 → JSON → `test.mosquitto.org`, plus LED control via subscribed topics (`iot/formagerie/esp32/*`).
- **`DHT22_SSD1306/`** — DHT22 telemetry over MQTT (`lab7/node1/*` topics), NTP time sync, tri-color status LEDs, and a local web server.

### Displays & input
- **`SSD1306` / `Stickman`, `StickMan_Comp`, `Stickaman_Comp_Old`, `ssd1306_128x64_i2c`** — 128×64 OLED (Adafruit SSD1306, I2C `0x3C`) experiments including animated stick-figure frames.
- **`QR_code_Reader/`, `QR_reader/`** — GM67 QR scanner module over Hardware Serial2 (GPIO16/17 @ 9600 baud), printing scanned codes to Serial.
- **`Display_LED_*` (`ON_OFF`, `TEMP`, `TEMP_0`, `TEMP_00`, `TEMP_TEST`)** — LED indicator variants driven by display/sensor state.

### Web servers
- **`Server_Plain_Txt_Json_/`** — plain-text/JSON HTTP responses.
- **`Server_with_Dashboard_LED_ctr/`, `Server_with_Dashboard_LED_ctr_Blink/`** — `WebServer` on port 80 serving an embedded glassmorphism HTML dashboard with ON/OFF buttons hitting `/led/on|off` endpoints.

### Other
- **`Comp/`, `Cat_comp/`, `new/`** — miscellaneous sketches (names only; contents are standalone `.ino` files).
- **`Commande d'un convoyeur/`** — conveyor-command experiment (French folder name).

---

## 🚀 Installation

### Prerequisites
- Arduino IDE with the **esp32 board package** installed (Boards Manager)
- USB cable / serial monitor for the target ESP32 dev board

### Steps
1. Open the sketch folder of your choice (`File → Open`) — each contains a single `.ino` matching the folder name.
2. Select board: **ESP32 Dev Module** (or your specific variant) and the correct COM port.
3. Install any libraries the sketch imports when prompted (see Technologies).
4. Edit the credentials/pins at the top of each `.ino` (SSID/password, MQTT broker, pin numbers) before uploading.

---

## 📖 Usage

### Sensor → MQTT
- Flash `MQTT_Weather_Logger/main.ino`, set `ssid`/`password`/`mqtt_server`, and subscribe to `iot/formagerie/esp32/dht22` (telemetry) and `iot/formagerie/esp32/led_R` / `led_G` (commands: `on`/`1` = HIGH).

### LED dashboard
- Flash `Server_with_Dashboard_LED_ctr/`, note the IP printed on Serial, and open `http://<ip>` in a browser on the same network — the embedded page sends ON/OFF commands to `/led/on` and `/led/off`.

### QR scanner
- Wire the GM67 module TX→GPIO16, RX→GPIO17, flash `QR_code_Reader/`, and scan codes while watching the Serial Monitor (115200 baud).

---

## 🏗️ Architecture

```
ESP/
├── AP_Mode/                     # WiFi softAP demo
├── LED_ble/, ble/               # Bluetooth Classic LED control
├── MQTT_Weather_Logger/         # DHT22 → MQTT pub + LED command sub
├── DHT22_SSD1306/               # DHT22 + MQTT + NTP + web server + status LEDs
├── Display_LED_*/               # LED state display experiments (5 variants)
├── Stickman/, StickMan_Comp/, Stickaman_Comp_Old/, ssd1306_128x64_i2c/
│                               # SSD1306 OLED drawing/animation experiments
├── QR_Code*/, QR_code_Reader/, QR_reader/   # QR display & GM67 scanner sketches
├── Server_Plain_Txt_Json_/      # minimal HTTP JSON/text server
├── Server_with_Dashboard_LED_ctr*/,          # web dashboard + LED control (2 variants)
├── Comp/, Cat_comp/, new/, Commande d'un convoyeur/   # misc experiments
```

Each folder is self-contained: one `.ino` (+ occasionally extra assets). There is no shared library or common config — credentials and pins are hardcoded per sketch.

---

## 🛠️ Technologies Used

### Core
- **C++ (Arduino)** - all sketches
- **ESP32 Arduino core** - `WiFi.h`, `WiFiAP.h`, `WebServer.h`, `BluetoothSerial.h`

### Libraries observed in the sketches
- **PubSubClient** - MQTT client (`MQTT_Weather_Logger`, `DHT22_SSD1306`)
- **DHT sensor library** - `DHT.h` for DHT22 (`MQTT_Weather_Logger`, `DHT22_SSD1306`)
- **Adafruit GFX / Adafruit SSD1306** - OLED displays (`Stickman`, `ssd1306_128x64_i2c`, etc.)
- **ArduinoJson-style manual JSON** - payloads are built with `String` concatenation, not a JSON library

---

## ⚠️ Limitations

### Experimental nature
- **Sketches are experiments, not releases** — several folders are near-duplicates (`Display_LED_TEMP` / `_0` / `_00` / `_TEST`, `QR_Code` / `QR_Code_Wifi_Station_Mode` / `QR_code_Reader` / `QR_reader`, `Comp` / `Cat_comp` / `new`); the "latest" variant is not labeled.
- **Mixed comment languages** — French and English comments side by side; some sketches are sparsely documented.
- **No tests, no CI** — nothing here is verifiable without flashing real hardware.

### Credentials & configuration
- **Hardcoded credentials throughout** — placeholder WiFi SSIDs/passwords (`Wokwi-GUEST`, `MyWiFi`/`12345678`, `ESP32_Yessin`/`123456789`) and the public broker `test.mosquitto.org` are baked into the source; change them before use.
- **MQTT traffic is unencrypted** — port 1883, no TLS, no authentication on the public broker.

### Testing Limitations
- **What a clone can re-check**: sketches compile-check only if you have the ESP32 core + libraries; wiring/pinouts are documented only in comments.
- **What a clone cannot re-check**: actual radio behavior, sensor readings, and dashboard pages require the physical ESP32 and peripherals (DHT22, SSD1306, GM67, LEDs).

---

## 🔒 Privacy

These sketches run entirely on local hardware. When configured to use `test.mosquitto.org`, sensor readings (temperature/humidity) and LED commands transit a **public MQTT broker in plaintext** — do not send sensitive data. No telemetry or analytics are included in the code.

---

## 📜 License

ESP is proprietary software — see [LICENSE](LICENSE) for the full terms.

**Copyright © 2026 AliesterEroan. All rights reserved.**

This software is provided for personal, non-commercial use only. Commercial use, redistribution, modification, and sublicensing are prohibited without explicit written permission. The copyright holder may distribute copies through the project's official GitHub Releases page; third parties may not host, mirror, or redistribute this software.

For licensing inquiries, open an issue at <https://github.com/AliesterEroan/ESP32/issues>.

---

## 📧 Contact

- **GitHub**: [AliesterEroan/ESP32](https://github.com/AliesterEroan/ESP32)
- **Issues**: [Create an issue](https://github.com/AliesterEroan/ESP32/issues)

---

*Built with ❤️ by AliesterEroan*
