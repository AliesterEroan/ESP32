#include "BluetoothSerial.h"

// Check if Bluetooth is properly enabled in the config
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it.
#endif

BluetoothSerial ESP_BT; // Object for Bluetooth Stream

// Define the LED pin (Built-in LED is usually GPIO 2 on most ESP32 dev boards)
const int LED_PIN = 2; 

// Variables to manage the current mode (0 = OFF, 1 = ON, 2 = BLINK)
int currentMode = 0; 

// Variables for non-blocking blink timing
unsigned long previousMillis = 0;
const long blinkInterval = 500; // Blink interval in milliseconds
int ledState = LOW;

void setup() {
  // Start the hardware serial communication for the PC Terminal
  Serial.begin(115200);
  
  // Start the Bluetooth device with your custom broadcast name
  ESP_BT.begin("mohamed_ESP32_Terminal"); 
  
  // Configure the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  
  Serial.println("Bluetooth Device is Ready to Pair!");
}

void loop() {
  // 1. Read from Phone (Bluetooth) and handle LED modes
  if (ESP_BT.available()) {
    char incomingChar = ESP_BT.read();
    
    // Print to PC Serial monitor for debugging
    Serial.print("Received via BT: ");
    Serial.println(incomingChar);
    
    // Check incoming characters to switch modes
    if (incomingChar == '0') {
      currentMode = 0;
      ESP_BT.println("Mode: 0 (OFF)");
    } else if (incomingChar == '1') {
      currentMode = 1;
      ESP_BT.println("Mode: 1 (ON)");
    } else if (incomingChar == '2') {
      currentMode = 2;
      ESP_BT.println("Mode: 2 (BLINK)");
    }
  }
  
  // 2. Read from PC Terminal (Serial) and send to Phone (Bluetooth)
  if (Serial.available()) {
    char outgoingChar = Serial.read();
    ESP_BT.write(outgoingChar);
  }

  // 3. Execute the LED state machine
  switch (currentMode) {
    case 0:
      digitalWrite(LED_PIN, LOW);
      break;

    case 1:
      digitalWrite(LED_PIN, HIGH);
      break;

    case 2:
      // Non-blocking blink execution
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= blinkInterval) {
        previousMillis = currentMillis; // Save the last toggle time

        // Toggle state
        ledState = (ledState == LOW) ? HIGH : LOW;
        digitalWrite(LED_PIN, ledState);
      }
      break;
  }
}