#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  delay(500);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;);
  }
  
  display.clearDisplay();
}

void loop() {
  // --- FRAME 1: Stickman with arms and legs DOWN ---
  display.clearDisplay();
  
  display.drawCircle(64, 20, 8, SSD1306_WHITE); // Head (X=64, Y=20, Radius=8)
  display.drawLine(64, 28, 64, 48, SSD1306_WHITE); // Spine/Body
  
  display.drawLine(64, 34, 44, 44, SSD1306_WHITE); // Left Arm (Down)
  display.drawLine(64, 34, 84, 44, SSD1306_WHITE); // Right Arm (Down)
  
  display.drawLine(64, 48, 54, 62, SSD1306_WHITE); // Left Leg
  display.drawLine(64, 48, 74, 62, SSD1306_WHITE); // Right Leg
  
  display.display();
  delay(400); // Wait nearly half a second


  // --- FRAME 2: Stickman with arms and legs UP ---
  display.clearDisplay();
  
  display.drawCircle(64, 20, 8, SSD1306_WHITE); // Head stays the same
  display.drawLine(64, 28, 64, 48, SSD1306_WHITE); // Body stays the same
  
  display.drawLine(64, 34, 44, 18, SSD1306_WHITE); // Left Arm (Up!)
  display.drawLine(64, 34, 84, 18, SSD1306_WHITE); // Right Arm (Up!)
  
  display.drawLine(64, 48, 44, 62, SSD1306_WHITE); // Left Leg (Wider split)
  display.drawLine(64, 48, 84, 62, SSD1306_WHITE); // Right Leg (Wider split)
  
  display.display();
  delay(400); // Wait another half second
}