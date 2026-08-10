# 📱 ESP32 QR Code Wi-Fi Provisioning

> Scan QR codes to connect to Wi-Fi networks! 🌐

## ✨ Features

- 📷 GM67 QR code scanner integration
- 🌐 Automatic Wi-Fi connection via QR codes
- 📱 Smartphone Wi-Fi sharing support
- 🔧 Simple SSID,PASSWORD format fallback
- 📊 Connection status and signal strength
- ⚡ Real-time feedback via serial monitor

## 🛠️ Hardware Requirements

- ESP32 development board
- GM67 QR code scanner module
- Jumper wires
- USB cable for programming

## 🔧 Configuration

### Serial Communication
```cpp
#define RX2_PIN 16     // GM67 TX pin
#define TX2_PIN 17     // GM67 RX pin
Serial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
```

## 📋 How It Works

1. **Setup Phase**: Initialize GM67 scanner
2. **QR Scanning**: Scan Wi-Fi sharing QR code from phone
3. **Data Parsing**: Extract SSID and password from QR data
4. **Wi-Fi Connection**: Connect to extracted credentials
5. **Status Display**: Show connection result and IP address
6. **Signal Info**: Display RSSI signal strength

## 🚀 Getting Started

1. Connect GM67 scanner to ESP32 (RX=16, TX=17)
2. Upload the sketch to your ESP32
3. Open Serial Monitor at 115200 baud
4. Generate Wi-Fi sharing QR code on your phone
5. Scan the QR code with GM67
6. Watch connection status in serial monitor

## 📱 Supported QR Formats

**Smartphone Wi-Fi Sharing:**
```
WIFI:S:MyNetwork;P:MyPassword;T:WPA;;
```

**Simple Format:**
```
MyNetwork,MyPassword
```

## 🎯 Connection Process

**Successful Connection:**
```
🎉 Success! Network established.
Assigned ESP32 IP Address: 192.168.1.100
Signal Strength (RSSI):    -45 dBm
```

**Failed Connection:**
```
❌ Connection Failed! Timeout reached. Check router proximity.
```

## 🎯 Typical Applications

- 🏠 Easy device provisioning
- 📱 Mobile device integration
- 🎓 Educational demonstrations
- 🔧 Network setup automation
- 🏭 Industrial IoT deployment

## ⚠️ Notes

- GM67 operates at 9600 baud
- 15-second connection timeout
- Supports both encrypted and open networks
- Standard smartphone Wi-Fi QR format supported

---

**Made with ❤️ by AliesterEroan**