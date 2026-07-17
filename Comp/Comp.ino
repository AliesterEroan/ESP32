#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// On ESP32, standard I2C pins are usually GPIO 21 (SDA) and GPIO 22 (SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // 1. Count from 0 to 9
  for (int i = 0; i <= 9; i++) {
    display.clearDisplay();
    
    // Set text size large for the counter number
    display.setTextSize(4);             
    display.setCursor(50, 15);            
    display.print(i);
    
    display.display();
    delay(1000); // Wait for 1 second before next number
  }

  // 2. Display the "Reset" screen with a happy emote
  display.clearDisplay();
  
  // Draw Happy Face Emote :-)
  display.setTextSize(3);
  display.setCursor(45, 10);
  display.print(":-)");
  
  // Draw "Reset" text
  display.setTextSize(2);
  display.setCursor(35, 45);
  display.print("Reset");
  
  display.display();
  
  // Wait 2 seconds on the reset screen before restarting the loop
  delay(2000); 
}