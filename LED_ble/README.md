# 🎧 ESP32 Bluetooth LED Controller

> Control LED modes via Bluetooth! 🔵

## ✨ Features

- 🔵 Classic Bluetooth (SPP) communication
- 💡 Multiple LED modes (OFF, ON, BLINK)
- 📱 Phone-to-ESP32 control
- 💻 PC terminal integration
- ⚡ Non-blocking blink implementation
- 🔄 Bidirectional communication

## 🛠️ Hardware Requirements

- ESP32 development board
- Bluetooth-enabled device (phone/tablet)
- LED with resistor
- USB cable for programming

## 🔧 Configuration

### Bluetooth Settings
```cpp
ESP_BT.begin("mohamed_ESP32_Terminal");  // Device name
```

### LED Pin
```cpp
const int LED_PIN = 2;  // Built-in LED
```

### Control Modes
```cpp
'0' → OFF mode
'1' → ON mode
'2' → BLINK mode
```

## 📋 How It Works

1. **Setup Phase**: Initialize Bluetooth and LED
2. **Pairing**: Connect device to "mohamed_ESP32_Terminal"
3. **Mode Selection**: Send '0', '1', or '2' via Bluetooth
4. **LED Control**: ESP32 executes selected mode
5. **Feedback**: Status message sent back to device
6. **PC Bridge**: Serial monitor shows all Bluetooth activity

## 🚀 Getting Started

1. Upload the sketch to your ESP32
2. Open Serial Monitor at 115200 baud
3. Pair your device with "mohamed_ESP32_Terminal"
4. Use a Bluetooth terminal app
5. Send control characters: '0', '1', or '2'

## 📱 Control Commands

**Turn LED OFF:**
```
Send: '0'
Response: "Mode: 0 (OFF)"
```

**Turn LED ON:**
```
Send: '1'
Response: "Mode: 1 (ON)"
```

**Blink LED:**
```
Send: '2'
Response: "Mode: 2 (BLINK)"
```

## ⚡ Blink Details

- **Interval**: 500ms (0.5 seconds)
- **Implementation**: Non-blocking (uses millis())
- **State**: Toggles between HIGH and LOW

## 🎯 Typical Applications

- 🎮 Remote control systems
- 💡 Smart lighting
- 🎧 Wireless device control
- 🎓 Educational projects
- 📱 IoT prototypes

## ⚠️ Notes

- Bluetooth must be enabled in ESP32 config
- Default baud rate: 115200
- LED on GPIO 2 (built-in)
- Blink mode is non-blocking

---

**Made with ❤️ by AliesterEroan**