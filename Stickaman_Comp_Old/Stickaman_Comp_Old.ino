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
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // --- Loop from 0 to 9 ---
  for (int i = 0; i <= 9; i++) {
    
    // ===================================================
    // ANIMATION FRAME 1: Stickman arms & legs DOWN
    // ===================================================
    display.clearDisplay();
    
    // Draw Counter (Left Side)
    display.setTextSize(4);             
    display.setCursor(20, 15);            
    display.print(i);
    
    // Draw Stickman (Shifted Right: X centered around 94 instead of 64)
    display.drawCircle(94, 20, 8, SSD1306_WHITE);     // Head
    display.drawLine(94, 28, 94, 48, SSD1306_WHITE);   // Spine/Body
    
    display.drawLine(94, 34, 74, 44, SSD1306_WHITE);   // Left Arm (Down)
    display.drawLine(94, 34, 114, 44, SSD1306_WHITE);  // Right Arm (Down)
    
    display.drawLine(94, 48, 84, 62, SSD1306_WHITE);   // Left Leg
    display.drawLine(94, 48, 104, 62, SSD1306_WHITE);  // Right Leg
    
    display.display();
    delay(400); 


    // ===================================================
    // ANIMATION FRAME 2: Stickman arms & legs UP
    // ===================================================
    display.clearDisplay();
    
    // Keep Counter visible on Frame 2
    display.setTextSize(4);             
    display.setCursor(20, 15);            
    display.print(i);
    
    // Draw Stickman (Shifted Right: X centered around 94)
    display.drawCircle(94, 20, 8, SSD1306_WHITE);     // Head
    display.drawLine(94, 28, 94, 48, SSD1306_WHITE);   // Body
    
    display.drawLine(94, 34, 74, 18, SSD1306_WHITE);   // Left Arm (Up!)
    display.drawLine(94, 34, 114, 18, SSD1306_WHITE);  // Right Arm (Up!)
    
    display.drawLine(94, 48, 74, 62, SSD1306_WHITE);   // Left Leg (Wider split)
    display.drawLine(94, 48, 114, 62, SSD1306_WHITE);  // Right Leg (Wider split)
    
    display.display();
    delay(400); 
    
    // After Frame 2 finishes, the 'for' loop increments 'i' and updates the number
  }

  // ===================================================
  // HAPPY EMOTE RESET SCREEN (Triggers after 9)
  // ===================================================
  display.clearDisplay();
  
  // Happy Face
  display.setTextSize(3);
  display.setCursor(45, 10);
  display.print(":-)");
  
  // Reset text
  display.setTextSize(2);
  display.setCursor(35, 45);
  display.print("Reset");
  
  display.display();
  delay(2000); // Hold the happy face for 2 seconds before looping back to 0
}