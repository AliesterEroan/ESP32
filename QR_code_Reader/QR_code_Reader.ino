/*
 * ESP32 + GM67 QR Code Reader
 * Reads QR data and prints it strictly to the Serial Monitor
 */

#define RXD2 16  // Connect to GM67 TX
#define TXD2 17  // Connect to GM67 RX
#define GM67_BAUD 9600 

void setup() {
  // Initialize USB Serial for PC monitor
  Serial.begin(115200);
  
  // Initialize Hardware Serial 2 for GM67
  Serial2.begin(GM67_BAUD, SERIAL_8N1, RXD2, TXD2);
  
  Serial.println("--- Scanner Active: Awaiting QR Code ---");
}

void loop() {
  // Check if GM67 is sending data
  if (Serial2.available() > 0) {
    String qrData = "";
    
    // Read the incoming characters
    while (Serial2.available() > 0) {
      char c = Serial2.read();
      
      // Strip out line breaks so formatting stays clean
      if (c != '\r' && c != '\n') {
        qrData += c;
      }
      delay(2); // Short buffer delay
    }
    
    // Clean up empty spaces and print the output
    qrData.trim();
    if (qrData.length() > 0) {
      Serial.print("QR Code Detected: ");
      Serial.println(qrData);
    }
  }
}