# 🏃 ESP32 Stickman Counter with Celebration

> Animated stickman counting with patriotic celebration! 🎉

## ✨ Features

- 🏃 Animated stickman character
- 🔢 Count up (0-9) and count down (9-0)
- 🎆 Fireworks celebration animation
- 🇱🇧 "I LOVE LEBANON" message display
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

1. **Count Up Phase (0→9)**: Animated stickman with counter
2. **Celebration**: Fireworks with "I LOVE LEBANON" message
3. **Count Down Phase (9→0)**: Animated stickman counting down
4. **Loop**: Cycle repeats continuously

## 🚀 Getting Started

1. Connect OLED display to ESP32 I2C pins (SDA=21, SCL=22)
2. Upload the sketch to your ESP32
3. Watch the animated stickman counter!

## 🎨 Animation Details

**Counting Phase:**
- Counter displayed on left side (large numbers)
- Animated stickman on right side
- Frame 1: Arms and legs DOWN
- Frame 2: Arms and legs UP
- 400ms delay between frames

**Celebration Phase:**
- "I LOVE LEBANON" text centered
- Fireworks on left and right sides
- 3 explosion cycles
- Expanding circles and radiating lines

## 🎯 Display Layout

**Counting Screen:**
```
[0-9]    [Stickman]
Counter  Animation
```

**Celebration Screen:**
```
  🎆        🎆
 I LOVE
  LEBANON
  🎆        🎆
```

## 🎯 Typical Applications

- 🎮 Game interfaces
- 🎨 Display animations
- 🎓 Graphics programming
- 🖼️ Digital signage
- 🎉 Celebration displays
- 🇱🇧 Patriotic demonstrations

## ⚠️ Notes

- Display uses I2C communication
- Animation runs continuously
- Uses Adafruit GFX library
- Each frame has 400ms delay
- Celebration shows 3 firework cycles

---

**Made with ❤️ by AliesterEroan**