#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Helper function for the food bowl and base sitting body
void drawBaseCatAndBowl() {
  // Food Bowl (Centered around X=105, Y=56)
  display.drawRect(100, 52, 12, 6, SSD1306_WHITE); 
  display.drawPixel(105, 54, SSD1306_WHITE); 

  // Cat Body (Sitting profile on the right side)
  display.drawRoundRect(74, 38, 20, 20, 4, SSD1306_WHITE); 
  display.drawLine(78, 58, 78, 62, SSD1306_WHITE);         // Back Leg
  display.drawLine(90, 58, 90, 62, SSD1306_WHITE);         // Front Leg
  
  // Tail (Curled up behind)
  display.drawLine(74, 50, 68, 46, SSD1306_WHITE);
  display.drawLine(68, 46, 68, 40, SSD1306_WHITE);
}

// ==========================================
// EATING ANIMATION FRAMES (Counting UP)
// ==========================================

void drawCatEating1(int count) {
  display.clearDisplay();
  
  display.setTextSize(4);             
  display.setCursor(20, 15);            
  display.print(count);
  
  drawBaseCatAndBowl();
  
  // Head UP 
  display.drawCircle(92, 30, 6, SSD1306_WHITE); 
  display.drawLine(92, 36, 92, 38, SSD1306_WHITE); 
  
  // Ears Up
  display.drawLine(88, 26, 86, 21, SSD1306_WHITE); 
  display.drawLine(86, 21, 90, 25, SSD1306_WHITE);
  display.drawLine(94, 25, 96, 21, SSD1306_WHITE);
  display.drawLine(96, 21, 96, 26, SSD1306_WHITE);

  display.display();
  delay(400); 
}

void drawCatEating2(int count) {
  display.clearDisplay();
  
  display.setTextSize(4);             
  display.setCursor(20, 15);            
  display.print(count);
  
  drawBaseCatAndBowl();
  
  // Head DOWN into bowl
  display.drawCircle(97, 44, 6, SSD1306_WHITE); 
  
  // Ears Angled Back
  display.drawLine(92, 42, 88, 39, SSD1306_WHITE);
  display.drawLine(88, 39, 93, 40, SSD1306_WHITE);
  display.drawLine(98, 39, 96, 35, SSD1306_WHITE);
  display.drawLine(96, 35, 100, 40, SSD1306_WHITE);

  display.display();
  delay(400); 
}

// ==========================================
// SLEEPING ANIMATION FRAMES (Counting DOWN)
// ==========================================

void drawCatSleeping(int count, bool toggleZ) {
  display.clearDisplay();
  
  display.setTextSize(4);             
  display.setCursor(20, 15);            
  display.print(count);
  
  drawBaseCatAndBowl();
  
  // Head resting down low
  display.drawCircle(95, 44, 6, SSD1306_WHITE); 
  
  // Sleeping ears (relaxed sideways)
  display.drawLine(90, 41, 85, 42, SSD1306_WHITE);
  display.drawLine(99, 40, 104, 41, SSD1306_WHITE);
  
  // Closed eye line (-)
  display.drawLine(94, 44, 97, 44, SSD1306_WHITE);

  // Floating "Zzz" effect
  display.setTextSize(1);
  if (toggleZ) {
    display.setCursor(88, 22);
    display.print("z");
    display.setCursor(95, 14);
    display.print("Z");
  } else {
    display.setCursor(91, 18);
    display.print("z");
  }

  display.display();
  delay(500); 
}

// ==========================================
// CELEBRATION: Happy Cat Face + MEOW + Fireworks
// ==========================================
void playFireworksAnimation() {
  int fireworkOffsets[8][4] = {
    {0, -5, 0, -15}, {5, -5, 12, -12}, {5, 0, 15, 0}, {5, 5, 12, 12},
    {0, 5, 0, 15}, {-5, 5, -12, 12}, {-5, 0, -15, 0}, {-5, -5, -12, -12}
  };

  for (int blast = 0; blast < 3; blast++) {
    for (int r = 2; r < 14; r += 4) {
      display.clearDisplay();
      
      // --- DRAW HAPPY CAT FACE (Center: X=64, Y=28) ---
      display.drawCircle(64, 28, 12, SSD1306_WHITE); // Main Face Circle
      
      // Left Ear
      display.drawLine(54, 20, 50, 10, SSD1306_WHITE);
      display.drawLine(50, 10, 60, 17, SSD1306_WHITE);
      // Right Ear
      display.drawLine(74, 20, 78, 10, SSD1306_WHITE);
      display.drawLine(78, 10, 68, 17, SSD1306_WHITE);
      
      // Happy Eyes (^)
      display.drawLine(56, 25, 59, 22, SSD1306_WHITE); // Left eye ^
      display.drawLine(59, 22, 62, 25, SSD1306_WHITE);
      display.drawLine(66, 25, 69, 22, SSD1306_WHITE); // Right eye ^
      display.drawLine(69, 22, 72, 25, SSD1306_WHITE);
      
      // Nose and Mouth
      display.drawPixel(64, 29, SSD1306_WHITE);         // Button nose
      display.drawLine(64, 29, 64, 32, SSD1306_WHITE);   // Mouth line down
      display.drawLine(64, 32, 61, 34, SSD1306_WHITE);   // Mouth curve left
      display.drawLine(64, 32, 67, 34, SSD1306_WHITE);   // Mouth curve right
      
      // Whiskers
      display.drawLine(50, 28, 40, 26, SSD1306_WHITE);  // Left whiskers
      display.drawLine(50, 30, 38, 31, SSD1306_WHITE);
      display.drawLine(78, 28, 88, 26, SSD1306_WHITE);  // Right whiskers
      display.drawLine(78, 30, 90, 31, SSD1306_WHITE);

      // --- TEXT: "MEOW!" (Below the head) ---
      display.setTextSize(2);
      display.setCursor(40, 48);
      display.print("MEOW!");
      
      // --- BACKGROUND FIREWORKS (On the edges) ---
      // Left side firework (Center X=12, Y=32)
      display.drawCircle(12, 32, r/2, SSD1306_WHITE);
      // Right side firework (Center X=115, Y=32)
      display.drawCircle(115, 32, r/2, SSD1306_WHITE);
      
      for (int i = 0; i < 8; i++) {
        display.drawLine(12 + (fireworkOffsets[i][0] * r / 5), 32 + (fireworkOffsets[i][1] * r / 5),
                         12 + (fireworkOffsets[i][2] * r / 5), 32 + (fireworkOffsets[i][3] * r / 5), SSD1306_WHITE);
        display.drawLine(115 + (fireworkOffsets[i][0] * r / 5), 32 + (fireworkOffsets[i][1] * r / 5),
                         115 + (fireworkOffsets[i][2] * r / 5), 32 + (fireworkOffsets[i][3] * r / 5), SSD1306_WHITE);
      }
      
      display.display();
      delay(150);
    }
    delay(200); 
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
  // --- 1. COUNT UP (0 -> 9): Cat is Eating ---
  for (int i = 0; i <= 9; i++) {
    drawCatEating1(i); 
    drawCatEating2(i); 
  }

  // --- CELEBRATION: MEOW + Fireworks ---
  playFireworksAnimation();
  delay(1000); 

  // --- 2. COUNT DOWN (9 -> 0): Cat is Sleeping ---
  for (int i = 9; i >= 0; i--) {
    drawCatSleeping(i, true);  
    drawCatSleeping(i, false); 
  }
  
  // --- CELEBRATION: MEOW + Fireworks ---
  playFireworksAnimation();
  delay(1000); 
}