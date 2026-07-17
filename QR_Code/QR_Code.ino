/*
 * ESP32 + GM67 QR Code Scanner (Fixed Timing)
 */

#define RXD2 16
#define TXD2 17
#define GM67_BAUD 9600 

#define LED_PIN 2 

const String ON_COMMAND  = "ON";
const String OFF_COMMAND = "OFF";

void setup() {
  Serial.begin(115200);
  
  // Initialize HardwareSerial 2
  Serial2.begin(GM67_BAUD, SERIAL_8N1, RXD2, TXD2);
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); 
  
  Serial.println("--- GM67 QR LED Controller Ready ---");
  Serial.println("Waiting for scan...");
}

void loop() {
  if (Serial2.available() > 0) {
    // Read the serial buffer until the Carriage Return character
    String qrData = Serial2.readStringUntil('\r');
    
    // Clean up the string (removes hidden spaces, newlines, tabs)
    qrData.trim(); 
    
    // If the string isn't empty after trimming, process it
    if (qrData.length() > 0) {
      Serial.print("[SCANNED]: ");
      Serial.println(qrData);
      
      if (qrData == ON_COMMAND) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println(">>> LED TURNED ON <<<");
      } 
      else if (qrData == OFF_COMMAND) {
        digitalWrite(LED_PIN, LOW);
        Serial.println(">>> LED TURNED OFF <<<");
      } 
      else {
        Serial.println("Unknown QR code. No action taken.");
      }
    }
  }
}