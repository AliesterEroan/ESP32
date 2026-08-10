# 🌡️ ESP32 MQTT Weather Logger

> IoT temperature and humidity monitoring with MQTT! 📡

## ✨ Features

- 🌡️ DHT22 temperature & humidity sensing
- 📡 MQTT client for data publishing
- 💡 LED status monitoring via MQTT
- 📊 JSON data format for easy parsing
- 🔄 Auto-reconnection on connection loss
- ⏰ 5-second publishing interval

## 🛠️ Hardware Requirements

- ESP32 development board
- DHT22 temperature/humidity sensor
- 2x LEDs (Red & Green) with resistors
- USB cable for programming and power

## 🔧 Configuration

### Wi-Fi Settings
```cpp
const char* ssid     = "HotSpot1000";
const char* password = "12345678";
```

### MQTT Settings
```cpp
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port   = 1883;
```

### Hardware Pins
```cpp
#define DHTPIN 4
#define DHTTYPE DHT22
const int LED_R_PIN = 12;  // Red LED
const int LED_G_PIN = 14;  // Green LED
```

## 📋 How It Works

1. **Wi-Fi Connection**: Connects to configured network
2. **MQTT Connection**: Connects to MQTT broker with unique client ID
3. **Sensor Reading**: Reads DHT22 temperature and humidity
4. **Data Publishing**: Sends JSON-formatted data to MQTT topics
5. **LED Status**: Publishes current LED states to MQTT
6. **Auto-Reconnect**: Automatically reconnects if connection lost

## 🚀 Getting Started

1. Wire up DHT22 sensor and LEDs
2. Update Wi-Fi credentials in the code
3. Upload the sketch to your ESP32
4. Open Serial Monitor at 115200 baud
5. Monitor MQTT topics for live data

## 🎯 MQTT Topics

```
iot/formagerie/esp32/dht22    → JSON: {"temperature":24.50,"humidity":60.20}
iot/formagerie/esp32/led_R     → Red LED state (0/1)
iot/formagerie/esp32/led_G     → Green LED state (0/1)
```

## 📱 Data Format

**DHT22 Payload (JSON):**
```json
{
  "temperature": 24.50,
  "humidity": 60.20
}
```

**LED States:**
```
0 → LED OFF
1 → LED ON
```

## 🎯 Typical Applications

- 🏠 Home automation
- 🌡️ Environmental monitoring
- 📊 Data logging systems
- 🏭 Industrial IoT
- 🎓 Educational projects

## ⚠️ Notes

- MQTT broker: test.mosquitto.org (public)
- Publishing interval: 5 seconds
- JSON format for easy parsing
- Auto-reconnect enabled

---

**Made with ❤️ by AliesterEroan**