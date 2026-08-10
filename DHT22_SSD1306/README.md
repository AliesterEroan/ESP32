# 🌡️ ESP32 DHT22 Weather Station + MQTT

> Complete IoT weather monitoring system! 🌤️

## ✨ Features

- 🌡️ Temperature & humidity monitoring (DHT22)
- 📊 Real-time web dashboard with live data
- 📡 MQTT integration for remote monitoring
- 🎨 Color-coded LED status indicators
- ⏰ NTP time synchronization
- 🌐 Web-based LED control interface

## 🛠️ Hardware Requirements

- ESP32 development board
- DHT22 temperature/humidity sensor
- 3x LEDs (Green, Yellow, Red) with resistors
- USB cable for programming and power

## 🔧 Configuration

### Wi-Fi Settings
```cpp
const char* ssid     = "MyWiFi";
const char* password = "12345678";
```

### MQTT Settings
```cpp
const char* mqtt_server = "test.mosquitto.org";
```

### Hardware Pins
```cpp
#define DHTPIN 4       // DHT22 data pin
#define LED_GREEN 5    // Green LED
#define LED_YELLOW 23  // Yellow LED
#define LED_RED 3      // Red LED
```

## 📋 How It Works

1. **Sensor Reading**: DHT22 measures temperature and humidity every 2 seconds
2. **MQTT Publishing**: Data is sent to MQTT topics for remote monitoring
3. **Web Dashboard**: Access via browser to see live data and control LEDs
4. **Time Sync**: NTP server provides accurate timestamps
5. **Remote Control**: MQTT messages can control LEDs remotely

## 🚀 Getting Started

1. Wire up the DHT22 sensor and LEDs
2. Update Wi-Fi credentials in the code
3. Upload the sketch to your ESP32
4. Open Serial Monitor at 115200 baud
5. Access the web dashboard using the displayed IP address

## 📱 Web Dashboard Features

- 🌡️ Live temperature display
- 💧 Live humidity display
- ⏰ Capture timestamp
- 🎛️ LED toggle buttons (Green/Yellow/Red)
- 📊 Auto-refresh every 2 seconds

## 🎯 MQTT Topics

```
lab7/node1/temperature    → Temperature readings
lab7/node1/humidity       → Humidity readings
lab7/node1/Led_G          → Green LED control
lab7/node1/Led_Y          → Yellow LED control
lab7/node1/Led_R          → Red LED control
```

## 🎯 Typical Applications

- 🏠 Home automation
- 🌡️ Environmental monitoring
- 🏭 Industrial IoT
- 📊 Data logging systems
- 🎓 Educational projects

## ⚠️ Notes

- MQTT broker: test.mosquitto.org (public)
- Adjust NTP offset for your timezone
- Web server runs on port 80
- LEDs respond to both web buttons and MQTT commands

---

**Made with ❤️ by AliesterEroan**