# 📱 ESP32 QR Code LED Controller

> Scan QR codes to control hardware! 🎯

## ✨ Features

- 📷 GM67 QR code scanner integration
- 💡 LED control via QR commands
- ⚡ Real-time scan processing
- 🔤 Simple command parsing (ON/OFF)
- 📊 Serial monitor feedback

## 🛠️ Hardware Requirements

- ESP32 development board
- GM67 QR code scanner module
- LED with resistor
- Jumper wires

## 🔧 Configuration

### Serial Communication
```cpp
#define RXD2 16     // GM67 TX pin
#define TXD2 17     // GM67 RX pin
#define GM67_BAUD 9600

#define LED_PIN 2   // LED control pin
```

### Supported Commands
```cpp
const String ON_COMMAND  = "ON";   // Turns LED ON
const String OFF_COMMAND = "OFF";  // Turns LED OFF
```

## 📋 How It Works

1. **Setup Phase**: Initialize GM67 scanner and LED
2. **Scanning**: Continuously listens for QR code scans
3. **Processing**: Parses scanned data and extracts commands
4. **Action**: Controls LED based on recognized commands
5. **Feedback**: Serial monitor shows scan results and actions

## 🚀 Getting Started

1. Connect GM67 scanner to ESP32 (RX/TX pins)
2. Wire up LED to GPIO 2
3. Upload the sketch to your ESP32
4. Open Serial Monitor at 115200 baud
5. Scan QR codes containing "ON" or "OFF"

## 📱 Usage Example

**Scan "ON" QR Code:**
```
[SCANNED]: ON
>>> LED TURNED ON <<<
```

**Scan "OFF" QR Code:**
```
[SCANNED]: OFF
>>> LED TURNED OFF <<<
```

**Unknown QR Code:**
```
[SCANNED]: XYZ123
Unknown QR code. No action taken.
```

## 🎯 Typical Applications

- 🏷️ Inventory control systems
- 🔐 Access control
- 🎮 Interactive installations
- 📦 Package tracking
- 🎓 Educational demonstrations

## ⚠️ Notes

- GM67 operates at 9600 baud
- Ensure proper grounding of scanner
- LED uses standard HIGH/LOW logic
- Unknown QR codes are ignored

---

**Made with ❤️ by AliesterEroan**