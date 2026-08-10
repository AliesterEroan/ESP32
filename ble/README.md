# 📶 ESP32 Bluetooth Terminal

> Wireless communication made simple! 🎧

## ✨ Features

- 🔵 Classic Bluetooth (SPP) communication
- 📱 Full-duplex serial communication
- 💻 Bidirectional data transfer (PC ↔ Phone)
- 🔄 Real-time terminal bridge

## 🛠️ Hardware Requirements

- ESP32 development board
- Bluetooth-enabled device (phone/tablet/PC)
- USB cable for programming

## 🔧 Configuration

### Bluetooth Settings
```cpp
ESP_BT.begin("mohamed_ESP32_Terminal");  // Device name visible when pairing
```

## 📋 How It Works

1. **Setup Phase**: ESP32 starts Bluetooth with custom device name
2. **Pairing**: Connect your device to "mohamed_ESP32_Terminal"
3. **Communication Bridge**: 
   - Data from Bluetooth → Serial Monitor (PC)
   - Data from Serial Monitor → Bluetooth (Phone)

## 🚀 Getting Started

1. Upload the sketch to your ESP32
2. Open Serial Monitor at 115200 baud
3. Enable Bluetooth on your phone/PC
4. Scan and pair with "mohamed_ESP32_Terminal"
5. Use a serial terminal app on your device
6. Start communicating!

## 📱 Usage Example

**From Phone to PC:**
```
Type on phone → Appears on Serial Monitor
```

**From PC to Phone:**
```
Type on Serial Monitor → Appears on phone terminal
```

## 🎯 Typical Applications

- 📡 Wireless debugging
- 🎮 Remote control systems
- 💬 Simple chat interfaces
- 🔧 Device configuration

## ⚠️ Notes

- Make sure Bluetooth is enabled in ESP32 configuration
- Default baud rate: 115200
- No authentication required (simple pairing)

---

**Made with ❤️ by AliesterEroan**