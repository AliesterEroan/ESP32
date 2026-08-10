# 🐱 ESP32 Animated Cat Counter

> Adorable cat animation with counting! 🎉

## ✨ Features

- 🐱 Animated cat character (eating & sleeping)
- 🔢 Count up (0-9) and count down (9-0)
- 🎆 Celebration animation with fireworks
- 😺 Happy cat face with "MEOW!" display
- 🎨 SSD1306 OLED display integration
- ⚡ Smooth frame animations

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

1. **Count Up Phase (0→9)**: Cat appears to be eating from bowl
2. **Celebration**: Happy cat face with fireworks and "MEOW!"
3. **Count Down Phase (9→0)**: Cat appears to be sleeping with "Zzz"
4. **Celebration**: Repeat happy cat animation
5. **Loop**: Cycle repeats continuously

## 🚀 Getting Started

1. Connect OLED display to ESP32 I2C pins (SDA=21, SCL=22)
2. Upload the sketch to your ESP32
3. Watch the adorable cat animation!

## 🎨 Animation Details

**Eating Animation:**
- Head moves up and down toward food bowl
- Ears angle during eating motion
- Cat body remains in sitting position

**Sleeping Animation:**
- Head rests low (sleeping position)
- Ears relaxed sideways
- Floating "Zzz" effects
- Closed eye line

**Celebration:**
- Happy cat face with ^ eyes
- "MEOW!" text display
- Fireworks effects on sides
- Whiskers and cute details

## 🎯 Typical Applications

- 🎮 Game interfaces
- 🎨 Display animations
- 🎓 Graphics programming
- 🖼️ Digital signage
- 📱 Educational demonstrations

## ⚠️ Notes

- Display uses I2C communication
- Animation runs continuously
- Uses Adafruit GFX library
- Each frame has 400-500ms delay

---

**Made with ❤️ by AliesterEroan**