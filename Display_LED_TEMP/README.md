# 🌡️ ESP32 Nextion Temperature Control System

> Smart thermostat with touch screen interface! 🎛️

## ✨ Features

- 🌡️ DHT22 temperature & humidity sensing
- 📱 Nextion touch screen integration
- 🎛️ Thermostat with adjustable setpoint
- 💡 Automatic LED control based on temperature
- 📊 Real-time data display
- 🎨 Custom slider for temperature setting

## 🛠️ Hardware Requirements

- ESP32 development board
- Nextion display (any model)
- DHT22 temperature/humidity sensor
- LED with resistor
- Jumper wires

## 🔧 Configuration

### Hardware Pins
```cpp
#define DHTPIN 23           // DHT22 data pin
#define DHTTYPE DHT22       // Sensor type
#define LED_PIN 2           // LED control pin
```

### Serial Communication
```cpp
HardwareSerial NextionSerial(2);  // UART2 for Nextion
NextionSerial.begin(9600, SERIAL_8N1, 16, 17);  // RX=16, TX=17
```

### Temperature Settings
```cpp
float consigne = 24.0;  // Default thermostat setpoint
```

## 📋 How It Works

1. **Setup Phase**: Initialize display, sensor, and LED
2. **Slider Control**: User adjusts temperature setpoint via slider
3. **Sensor Reading**: DHT22 reads current temperature every second
4. **Thermostat Logic**: 
   - If temp > setpoint → LED ON (cooling needed)
   - If temp ≤ setpoint → LED OFF (temperature OK)
5. **Data Display**: Real-time temp and humidity shown on display
6. **Status Update**: LED status text updates automatically

## 🚀 Getting Started

1. Connect Nextion display to ESP32 (RX=16, TX=17)
2. Wire DHT22 to GPIO 23
3. Wire up LED to GPIO 2
4. Create Nextion interface with slider (h0) and text fields
5. Upload the sketch to your ESP32
6. Adjust temperature setpoint via slider

## 📱 Nextion Interface Elements

**Page 1 (Control):**
- Text field (t0): Shows "Led On" or "Led Off"

**Page 2 (Monitoring):**
- Slider (h0): Temperature setpoint adjustment
- Text field (t4): Current setpoint value
- Text field (t2): Current temperature
- Text field (t3): Current humidity

## 🎯 Typical Applications

- 🏠 Smart home thermostats
- 🌡️ Environmental control
- 🏭 Industrial temperature monitoring
- 🎓 Educational projects
- 📊 Data visualization

## ⚠️ Notes

- LED uses inverted logic (HIGH = OFF, LOW = ON)
- Slider sends commands in format "Set:XX"
- Update interval: 1 second
- Nextion commands end with 0xFF 0xFF 0xFF

---

**Made with ❤️ by AliesterEroan**