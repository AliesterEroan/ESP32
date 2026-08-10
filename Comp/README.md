# 🔢 ESP32 Simple Counter with Reset

> Basic counter with a happy reset! 😊

## ✨ Features

- 🔢 Count from 0 to 9
- 😊 Happy face emoticon on reset
- 🎨 SSD1306 OLED display integration
- ⚡ Simple and clean implementation
- 🔄 Automatic loop with reset screen

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

1. **Counting Phase**: Display numbers 0 through 9 sequentially
2. **Timing**: Each number displays for 1 second
3. **Reset Phase**: Show happy face with "Reset" text
4. **Pause**: Reset screen displays for 2 seconds
5. **Loop**: Cycle repeats automatically

## 🚀 Getting Started

1. Connect OLED display to ESP32 I2C pins (SDA=21, SCL=22)
2. Upload the sketch to your ESP32
3. Watch the counter and reset animation!

## 🎨 Display Details

**Counting Phase:**
- Large number centered on screen
- Text size: 4x
- Cursor position: (50, 15)

**Reset Screen:**
- Happy face emoticon ":-)"
- Text size: 3x for emoticon
- "Reset" text below
- 2-second pause before restart

## 🎯 Typical Applications

- 🎮 Simple counters
- 🎨 Display programming basics
- 🎓 Educational projects
- 🖼️ Digital signage
- 📱 User interface examples

## ⚠️ Notes

- Display uses I2C communication
- Loop runs continuously
- 1-second delay per number
- Uses Adafruit GFX library

---

**Made with ❤️ by AliesterEroan**