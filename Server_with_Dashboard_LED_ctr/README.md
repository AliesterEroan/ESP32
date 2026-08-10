# 🌐 ESP32 Web Server with Glassmorphism Dashboard

> Modern web-controlled LED system with beautiful UI! ✨

## ✨ Features

- 🎨 Modern glassmorphism web interface
- 📷 QR code Wi-Fi provisioning
- 🌐 Web server with real-time control
- 💡 LED control via web interface
- 📊 Telemetry logging
- 🎯 GM67 scanner integration

## 🛠️ Hardware Requirements

- ESP32 development board
- GM67 QR code scanner module
- LED with resistor
- Jumper wires

## 🔧 Configuration

### Hardware Pins
```cpp
#define RXD2 16     // GM67 TX pin
#define TXD2 17     // GM67 RX pin
#define LED_PIN 2   // LED control pin
```

## 📋 How It Works

1. **Setup Phase**: Initialize GM67 scanner and LED
2. **QR Provisioning**: Scan Wi-Fi QR code to connect
3. **Web Server**: Starts modern web interface on successful connection
4. **LED Control**: Web buttons send commands to control LED
5. **Telemetry**: Real-time feedback on web interface

## 🚀 Getting Started

1. Connect GM67 scanner to ESP32
2. Wire up LED to GPIO 2
3. Upload the sketch to your ESP32
4. Open Serial Monitor at 115200 baud
5. Scan your phone's Wi-Fi sharing QR code
6. Access the web dashboard using the displayed IP

## 🎨 Web Interface Features

- 🔮 Glassmorphism design with blur effects
- 🎨 Gradient backgrounds and modern styling
- 💚 ON/OFF buttons with hover effects
- 📊 Real-time telemetry console
- 📱 Responsive design for mobile devices
- ⚡ Smooth animations and transitions

## 📱 Dashboard URL

After successful Wi-Fi connection:
```
http://<ESP32_IP_ADDRESS>
```

## 🎯 Typical Applications

- 🏠 Smart home control
- 🎮 Remote device management
- 📊 IoT dashboards
- 🎨 Web interface development
- 🎓 Educational projects

## ⚠️ Notes

- Scan standard Wi-Fi sharing QR codes
- Use HTTP (not HTTPS) to access dashboard
- Disable VPN if connection fails
- Web server runs on port 80

---

**Made with ❤️ by AliesterEroan**