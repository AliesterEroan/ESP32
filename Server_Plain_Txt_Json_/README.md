# 🌐 ESP32 Web Server with JSON API

> Complete web server with HTML dashboard and JSON endpoints! 📊

## ✨ Features

- 🌡️ DHT22 temperature & humidity sensing
- 🎨 HTML web dashboard with controls
- 📡 JSON API endpoint for applications
- 💡 RGB LED control (Red, Green, Blue)
- 📊 Real-time sensor data display
- 🔗 URL-based LED control

## 🛠️ Hardware Requirements

- ESP32 development board
- DHT22 temperature/humidity sensor
- 3x LEDs (Red, Green, Blue) with resistors
- USB cable for programming and power

## 🔧 Configuration

### Wi-Fi Settings
```cpp
const char *ssid = "TTBOX-G4VVXQ";
const char *password = "YABYCLV6GW";
```

### Hardware Pins
```cpp
#define DHTPIN 4        // DHT22 data pin
#define DHTTYPE DHT22
#define LED_RED 12      // Red LED
#define LED_GREEN 13    // Green LED
#define LED_BLUE 14     // Blue LED
```

## 📋 How It Works

1. **Wi-Fi Connection**: Connects to configured network
2. **Web Server**: Starts HTTP server on port 80
3. **Sensor Reading**: Reads DHT22 temperature and humidity
4. **LED Control**: URL parameters control LED states
5. **HTML Dashboard**: Web interface shows data and controls
6. **JSON API**: Structured data for applications

## 🚀 Getting Started

1. Wire up DHT22 sensor and RGB LEDs
2. Update Wi-Fi credentials in the code
3. Upload the sketch to your ESP32
4. Open Serial Monitor at 115200 baud
5. Access web dashboard using displayed IP

## 📱 Web Interface

**HTML Dashboard (http://<IP>/):**
- 🌡️ Temperature display
- 💧 Humidity display
- 🔴 Red LED control (on/off)
- 🟢 Green LED control (on/off)
- 🔵 Blue LED control (on/off)
- 🔗 Link to JSON endpoint

**JSON API (http://<IP>/data):**
```json
{
  "temperature": 24.5,
  "humidity": 60.2,
  "led_status": {
    "red": "on",
    "green": "off",
    "blue": "on"
  }
}
```

## 🎯 URL Control Examples

**Turn Red LED ON:**
```
http://<IP>/?red=on
```

**Turn Green LED OFF:**
```
http://<IP>/?green=off
```

**Control Multiple LEDs:**
```
http://<IP>/?red=on&blue=on
```

## 🎯 Typical Applications

- 🏠 Smart home control
- 📊 IoT data logging
- 🎮 API development
- 🌐 Web interface projects
- 🎓 Educational demonstrations

## ⚠️ Notes

- Web server runs on port 80
- JSON endpoint: /data
- URL parameters control LEDs
- Auto-refresh required for live data

---

**Made with ❤️ by AliesterEroan**