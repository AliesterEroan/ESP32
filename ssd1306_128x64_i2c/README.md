# 🎨 ESP32 SSD1306 Graphics Examples

> Comprehensive OLED display graphics demonstrations! 🖼️

## ✨ Features

- 🎨 Complete graphics library examples
- 📐 Shapes: Lines, rectangles, circles, triangles
- 🔤 Text rendering and fonts
- 🔄 Scrolling text animation
- 🖼️ Bitmap image display
- ⚡ Animated bitmap examples
- 🎭 Display inversion effects

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

## 📋 Graphics Examples Included

1. **testdrawline()** - Line drawing demonstrations
2. **testdrawrect()** - Rectangle outlines
3. **testfillrect()** - Filled rectangles
4. **testdrawcircle()** - Circle outlines
5. **testfillcircle()** - Filled circles
6. **testdrawroundrect()** - Rounded rectangle outlines
7. **testfillroundrect()** - Filled rounded rectangles
8. **testdrawtriangle()** - Triangle outlines
9. **testfilltriangle()** - Filled triangles
10. **testdrawchar()** - Character display
11. **testdrawstyles()** - Stylized text
12. **testscrolltext()** - Scrolling text
13. **testdrawbitmap()** - Bitmap images
14. **testanimate()** - Animated bitmaps

## 🚀 Getting Started

1. Connect OLED display to ESP32 I2C pins (SDA=21, SCL=22)
2. Upload the sketch to your ESP32
3. Watch the complete graphics demonstration!

## 🎨 What You'll See

The demo runs through all graphics functions sequentially:
- Lines drawing in all directions
- Nested rectangles
- Expanding/collapsing circles
- Various triangles
- Text in different sizes
- Scrolling marquee text
- Bitmap logo animation
- Display inversion effects

## 🎯 Typical Applications

- 🎨 Graphics programming learning
- 🖼️ Display capability testing
- 🎮 Game development
- 📊 Data visualization
- 🎓 Educational demonstrations
- 🎨 UI/UX prototyping

## ⚠️ Notes

- Based on Adafruit SSD1306 library
- Display uses I2C communication
- Examples run once in setup()
- No continuous loop animation
- Includes Adafruit splash screen

## 📚 Library Credits

This example is based on the Adafruit SSD1306 library:
- Written by Limor Fried/Ladyada for Adafruit Industries
- BSD license
- Supports Adafruit monochrome OLEDs

---

**Made with ❤️ by AliesterEroan**