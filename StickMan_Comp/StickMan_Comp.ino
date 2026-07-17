#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Function to draw Frame 1 of the stickman (Arms & Legs Down) alongside the counter
void drawFrame1(int count) {
  display.clearDisplay();
  
  // Counter (Left Side)
  display.setTextSize(4);             
  display.setCursor(20, 15);            
  display.print(count);
  
  // Stickman (Right Side)
  display.drawCircle(94, 20, 8, SSD1306_WHITE);     // Head
  display.drawLine(94, 28, 94, 48, SSD1306_WHITE);   // Body
  display.drawLine(94, 34, 74, 44, SSD1306_WHITE);   // Left Arm (Down)
  display.drawLine(94, 34, 114, 44, SSD1306_WHITE);  // Right Arm (Down)
  display.drawLine(94, 48, 84, 62, SSD1306_WHITE);   // Left Leg
  display.drawLine(94, 48, 104, 62, SSD1306_WHITE);  // Right Leg
  
  display.display();
  delay(400);
}

// Function to draw Frame 2 of the stickman (Arms & Legs Up) alongside the counter
void drawFrame2(int count) {
  display.clearDisplay();
  
  // Counter (Left Side)
  display.setTextSize(4);             
  display.setCursor(20, 15);            
  display.print(count);
  
  // Stickman (Right Side)
  display.drawCircle(94, 20, 8, SSD1306_WHITE);     // Head
  display.drawLine(94, 28, 94, 48, SSD1306_WHITE);   // Body
  display.drawLine(94, 34, 74, 18, SSD1306_WHITE);   // Left Arm (Up)
  display.drawLine(94, 34, 114, 18, SSD1306_WHITE);  // Right Arm (Up)
  display.drawLine(94, 48, 74, 62, SSD1306_WHITE);   // Left Leg (Wide)
  display.drawLine(94, 48, 114, 62, SSD1306_WHITE);  // Right Leg (Wide)
  
  display.display();
  delay(400);
}

// Custom animation for fireworks expanding around the text
void playFireworksAnimation() {
  // Array of firework particle lines radiating outward
  // Pairs of relative (X1, Y1, X2, Y2) coordinates from a central point
  int fireworkOffsets[8][4] = {
    {0, -5, 0, -15},   // Top
    {5, -5, 12, -12},  // Top-Right
    {5, 0, 15, 0},     // Right
    {5, 5, 12, 12},    // Bottom-Right
    {0, 5, 0, 15},     // Bottom
    {-5, 5, -12, 12},  // Bottom-Left
    {-5, 0, -15, 0},   // Left
    {-5, -5, -12, -12} // Top-Left
  };

  // Run the fireworks loop 3 times
  for (int blast = 0; blast < 3; blast++) {
    // Phase 1: Fireworks expanding
    for (int r = 2; r < 14; r += 4) {
      display.clearDisplay();
      
      // Center Text
      display.setTextSize(1);
      display.setCursor(24, 28);
      display.print("I LOVE LEBANON");
      
      // Left firework center around (12, 32)
      display.drawCircle(12, 32, r/2, SSD1306_WHITE);
      // Right firework center around (115, 32)
      display.drawCircle(115, 32, r/2, SSD1306_WHITE);
      
      // Draw radiating bursts for both sides
      for (int i = 0; i < 8; i++) {
        // Left Burst lines
        display.drawLine(12 + (fireworkOffsets[i][0] * r / 5), 32 + (fireworkOffsets[i][1] * r / 5),
                         12 + (fireworkOffsets[i][2] * r / 5), 32 + (fireworkOffsets[i][3] * r / 5), SSD1306_WHITE);
        // Right Burst lines
        display.drawLine(115 + (fireworkOffsets[i][0] * r / 5), 32 + (fireworkOffsets[i][1] * r / 5),
                         115 + (fireworkOffsets[i][2] * r / 5), 32 + (fireworkOffsets[i][3] * r / 5), SSD1306_WHITE);
      }
      display.display();
      delay(150);
    }
    delay(200); // Hold peak of the blast briefly
  }
}

void setup() {
  Serial.begin(9600);
  delay(500);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // --- CYCLE 1: Count Up from 0 to 9 ---
  for (int i = 0; i <= 9; i++) {
    drawFrame1(i);
    drawFrame2(i);
  }

  // --- MIDDLE CELEBRATION: Fireworks & "I Love Lebanon" ---
  playFireworksAnimation();
  delay(1000); // Extra pause on the message before countdown

  // --- CYCLE 2: Count Down from 9 to 0 ---
  for (int i = 9; i >= 0; i--) {
    drawFrame1(i);
    drawFrame2(i);
  }
  
  delay(1000); // Quick pause at 0 before starting the whole cycle over again
}