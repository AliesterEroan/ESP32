#include "BluetoothSerial.h"

// Check if Bluetooth is properly enabled in the config
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it.
#endif

BluetoothSerial ESP_BT; // Object for Bluetooth Stream

void setup() {
  // Start the hardware serial communication for the PC Terminal
  Serial.begin(115200);
  
  // Start the Bluetooth device with the broadcast name "ESP32_Terminal"
  ESP_BT.begin("mohamed_ESP32_Terminal"); 
  
  Serial.println("Bluetooth Device is Ready to Pair!");
}

void loop() {
  // 1. Read from Phone (Bluetooth) and send to PC Terminal (Serial)
  if (ESP_BT.available()) {
    char incomingChar = ESP_BT.read();
    Serial.write(incomingChar);
  }
  
  // 2. Read from PC Terminal (Serial) and send to Phone (Bluetooth)
  if (Serial.available()) {
    char outgoingChar = Serial.read();
    ESP_BT.write(outgoingChar);
  }
}