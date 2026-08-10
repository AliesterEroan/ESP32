# 🏃 ESP32 Animated Stickman

> Bring your OLED display to life with animations! 🎬

## ✨ Features

- 🎨 SSD1306 OLED display integration
- 🏃 Animated stickman character
- 🎭 Smooth frame-by-frame animation
- 👆 Arms and legs movement
- ⚡ Lightweight graphics rendering

## 🛠️ Hardware Requirements

- ESP32 development board
- SSD1306 128x64 OLED display (I2C)
- Jumper wires
- USB cable for programming

## 🔧 Configuration

### Display Settings
```cpp
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C  // I2C address
```

## 📋 How It Works

1. **Setup Phase**: Initialize OLED display
2. **Animation Loop**: Alternate between two animation frames
3. **Frame 1**: Stickman with arms and legs DOWN
4. **Frame 2**: Stickman with arms and legs UP
5. **Timing**: 400ms delay between frames

## 🚀 Getting Started

1. Connect OLED display to ESP32 I2C pins (SDA=21, SCL=22)
2. Upload the sketch to your ESP32
3. Watch the animated stickman on your display!

## 🎨 Animation Details

**Frame 1 (Arms Down):**
- Head at (64, 20)
- Body line vertical
- Arms pointing down
- Legs in normal position

**Frame 2 (Arms Up):**
- Head stays same
- Body line vertical
- Arms raised up in celebration
- Legs spread wider

## 🎯 Typical Applications

- 🎮 Game development
- 🎨 Display animations
- 🎓 Graphics programming
- 🖼️ Digital signage
- 📱 User interface elements

## ⚠️ Notes

- Display uses I2C communication
- Animation runs continuously
- Frame rate: ~1.25 FPS
- Uses Adafruit GFX library

---

**Made with ❤️ by AliesterEroan**