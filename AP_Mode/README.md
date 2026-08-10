# 📡 ESP32 Access Point Mode

> Transform your ESP32 into a Wi-Fi hotspot! 🔥

## ✨ Features

- 🌐 Creates a custom Wi-Fi access point
- 👥 Tracks connected clients in real-time
- 📊 Serial monitor displays connection status
- ⚡ Simple and lightweight implementation

## 🛠️ Hardware Requirements

- ESP32 development board
- USB cable for programming

## 🔧 Configuration

### Wi-Fi Settings
```cpp
const char *ssid = "ESP32_Yessin";      // Your AP name
const char *password = "123456789";    // Your AP password (min 8 chars)
```

## 📋 How It Works

1. **Setup Phase**: ESP32 creates a Wi-Fi access point with specified credentials
2. **Monitoring**: Continuously checks for connected stations
3. **Reporting**: Serial monitor displays current client count every 2 seconds

## 🚀 Getting Started

1. Upload the sketch to your ESP32
2. Open Serial Monitor at 115200 baud
3. Connect your device to the "ESP32_Yessin" network
4. Watch the client count update in real-time!

## 📱 Usage Example

```
Clients : 0
Clients : 1
Clients : 2
```

## 🎯 Typical Applications

- 🏕️ Temporary network setup
- 📊 Device connection monitoring
- 🔧 Network testing and debugging
- 🎓 Educational demonstrations

## ⚠️ Notes

- Password must be at least 8 characters long
- ESP32 can handle multiple simultaneous connections
- Serial monitor must be open to see client updates

---

**Made with ❤️ by AliesterEroan**