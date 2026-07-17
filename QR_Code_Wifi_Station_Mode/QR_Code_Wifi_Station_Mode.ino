#include <WiFi.h>

// Pins for the GM67 Scanner (UART2)
#define RX2_PIN 16
#define TX2_PIN 17

String inputData = "";

void setup() {
  Serial.begin(115200);
  delay(10);
  
  // Start GM67 Scanner Communication at 9600 Baud
  Serial2.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);

  Serial.println("\n==============================================");
  Serial.println("ESP32 Router QR Code Provisioning System");
  Serial.println("==============================================");
  Serial.println("Ready! Scan the Wi-Fi Share QR Code from your phone.");
  Serial.println("==============================================\n");
}

void loop() {
  // Read incoming characters from the GM67 Scanner
  while (Serial2.available() > 0) {
    char c = Serial2.read();
    
    // Check for end-of-string characters (carriage return or newline)
    if (c == '\r' || c == '\n') {
      if (inputData.length() > 0) {
        processScannedData(inputData);
        inputData = ""; // Reset string buffer for the next scan
      }
    } else {
      inputData += c; // Build the string character by character
    }
  }
}

// Function to handle, identify, and extract credentials from the data string
void processScannedData(String data) {
  data.trim();
  Serial.print("Raw Scan Content: ");
  Serial.println(data);

  // Check if it's a standard smartphone Wi-Fi QR format (Starts with WIFI:)
  if (data.startsWith("WIFI:") || data.startsWith("wifi:")) {
    String ssid = extractWiFiParameter(data, "S:");
    String password = extractWiFiParameter(data, "P:");

    if (ssid.length() > 0) {
      Serial.println("\n----------------------------------------------");
      Serial.println("📱 Smartphone Wi-Fi QR Code Detected!");
      Serial.print("Extracted SSID: "); Serial.println(ssid);
      Serial.print("Extracted PASS: "); Serial.println(password.length() > 0 ? password : "[Open Network]");
      Serial.println("----------------------------------------------");

      connectToWiFi(ssid, password);
    } else {
      Serial.println("❌ Error: Could not extract a valid SSID from the QR code.");
    }
  } 
  // Backward compatibility: If you type or scan a simple "SSID,PASSWORD" configuration
  else if (data.indexOf(',') != -1) {
    int commaIndex = data.indexOf(',');
    String ssid = data.substring(0, commaIndex);
    String password = data.substring(commaIndex + 1);
    ssid.trim();
    password.trim();
    connectToWiFi(ssid, password);
  } 
  else {
    Serial.println("❌ Unknown QR format. Present a standard Wi-Fi configuration QR code.");
  }
}

// Helper function to extract specific tokens (like S: or P:) from inside the QR string
String extractWiFiParameter(String data, String parameter) {
  int paramIndex = data.indexOf(parameter);
  if (paramIndex == -1) return ""; // Parameter not found (e.g. an open network has no P:)

  // Start reading right after the identifier (e.g., right after "S:")
  int startIndex = paramIndex + parameter.length();
  
  // Find the closing semicolon that terminates this specific parameter
  int endIndex = data.indexOf(';', startIndex);
  if (endIndex == -1) return "";

  return data.substring(startIndex, endIndex);
}

// Function to handle the Wi-Fi connection phase and display the IP address
void connectToWiFi(String ssid, String pass) {
  Serial.println("Disconnecting from old networks...");
  WiFi.disconnect();
  delay(500);

  Serial.print("Connecting to network");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pass.c_str());

  // Wait for connection with a 15-second timeout limit
  int timeoutCounter = 0;
  while (WiFi.status() != WL_CONNECTED && timeoutCounter < 30) {
    delay(500);
    Serial.print(".");
    timeoutCounter++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n\n🎉 Success! Network established.");
    Serial.println("==============================================");
    Serial.print("Assigned ESP32 IP Address: ");
    Serial.println(WiFi.localIP()); // Prints the local IP address on your screen
    Serial.print("Signal Strength (RSSI):    ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    Serial.println("==============================================\n");
  } else {
    Serial.println("\n❌ Connection Failed! Timeout reached. Check router proximity.");
  }
}