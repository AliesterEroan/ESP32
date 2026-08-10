# 🖥️ ESP32 Nextion Display LED Control

> Control LEDs via touch screen display! 📱

## ✨ Features

- 📱 Nextion touch screen integration
- 💡 LED control via display buttons
- 🔄 Serial communication with display
- 📊 Real-time status feedback
- 🎨 Customizable display interface

## 🛠️ Hardware Requirements

- ESP32 development board
- Nextion display (any model)
- LED with resistor
- Jumper wires

## 🔧 Configuration

### Serial Communication
```cpp
HardwareSerial NextionSerial(2);  // UART2 for Nextion
NextionSerial.begin(9600, SERIAL_8N1, 16, 17);  // RX=16, TX=17
```

### LED Pin
```cpp
const int ledPin = 2;  // LED control pin
```

## 📋 How It Works

1. **Setup Phase**: Initialize Nextion display and LED
2. **Display Commands**: Send reset command to display
3. **User Interaction**: User taps "On" or "Off" buttons on display
4. **Command Processing**: ESP32 receives and processes display commands
5. **LED Control**: LED state changes based on button press
6. **Status Update**: Display text updates to show current state

## 🚀 Getting Started

1. Connect Nextion display to ESP32 (RX=16, TX=17)
2. Wire up LED to GPIO 2
3. Create Nextion interface with buttons sending "On" and "Off"
4. Upload the sketch to your ESP32
5. Tap buttons on display to control LED

## 📱 Nextion Commands

**LED ON:**
```
Page button sends: "On"
ESP32 responds: "page1.t0.txt=\"Led On\""
```

**LED OFF:**
```
Page button sends: "Off"
ESP32 responds: "page1.t0.txt=\"Led Off\""
```

## 🎯 Typical Applications

- 🏠 Smart home control panels
- 🎮 Industrial control interfaces
- 📊 Dashboard systems
- 🎨 Interactive displays
- 🎓 Educational projects

## ⚠️ Notes

- Nextion operates at 9600 baud
- Commands must end with 0xFF 0xFF 0xFF
- LED uses inverted logic (HIGH = OFF, LOW = ON)
- Display must be configured with appropriate buttons

---

**Made with ❤️ by AliesterEroan**