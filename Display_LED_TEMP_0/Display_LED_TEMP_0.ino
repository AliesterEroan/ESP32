#include <HardwareSerial.h>
#include <DHT.h>

// ---------------- Pins ----------------
#define DHTPIN 23
#define DHTTYPE DHT22
#define LED_PIN 2       // Internal ESP32 LED 

// ---------------- Sensors ----------------
DHT dht(DHTPIN, DHTTYPE);

// ---------------- Serial Communication ----------------
HardwareSerial NextionSerial(2); // RX2 (GPIO 16), TX2 (GPIO 17)

// ---------------- Timing & Variables ----------------
unsigned long lastUpdate = 0;
const long interval = 1000;    
String comm = "";

float consigne = 24.0;  // Default target temperature setpoint (0 to 50)
bool manualMode = false; // Tracks if a manual button was pressed to stop auto-overwrite

void setup() {
  Serial.begin(115200);        
  NextionSerial.begin(9600, SERIAL_8N1, 16, 17); 
  
  pinMode(LED_PIN, OUTPUT);
  
  dht.begin();
  
  // Reset screen and force-sync the Nextion slider components
  sendNextionCommand("rest");
  delay(500); 
  sendNextionCommand("page2.h0.val=24");
  sendNextionCommand("page2.t4.txt=\"24\"");
}

void sendNextionCommand(const char* command) {
  NextionSerial.print(command);
  NextionSerial.write(0xFF); 
  NextionSerial.write(0xFF);
  NextionSerial.write(0xFF);
  Serial.print("Sent: ");
  Serial.println(command);
}

void loop() {
  // 1. Process data coming from the Nextion Display
  if (NextionSerial.available() > 0) {
    String command = NextionSerial.readStringUntil('\n');
    command.trim(); 
    comm = command;
    
    Serial.print("Received: ");
    Serial.println(command);
  }

  // 2. Parse the Slider values
  if (comm.startsWith("Set:")) {
    String valStr = comm.substring(4); 
    consigne = valStr.toFloat();
    manualMode = false; // Moving the slider re-enables automatic thermostat mode
    
    Serial.print("New Setpoint (Consigne): ");
    Serial.print(consigne);
    Serial.println(" C");
    
    comm = ""; 
  }

  // 3. Manual ON/OFF Button Overrides
  if (comm == "On") {
    digitalWrite(LED_PIN, HIGH);   // Turn LED ON (Active-Low)
    sendNextionCommand("page1.t0.txt=\"Led On\"");
    manualMode = true;            // Lock into manual mode so auto loop doesn't overwrite it
    comm = "";
  }
  if (comm == "Off") {
    digitalWrite(LED_PIN, LOW);  // Turn LED OFF (Active-Low)
    sendNextionCommand("page1.t0.txt=\"Led Off\"");
    manualMode = true;            // Lock into manual mode so auto loop doesn't overwrite it
    comm = "";
  }

  // 4. Periodic Temperature/Humidity Collection & Thermostat Logic
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdate >= interval) {
    lastUpdate = currentMillis;

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("DHT read error!");
      return;
    }

    // --- AUTOMATIC CONTROL LOGIC ---
    // Only automatically adjust the LED if the user hasn't pressed manual ON/OFF buttons
    if (!manualMode) {
      if (temperature > consigne) {
        digitalWrite(LED_PIN, LOW);  // Turn LED ON (Active-Low)
        sendNextionCommand("page1.t0.txt=\"Led On\"");
      } 
      else {
        digitalWrite(LED_PIN, HIGH); // Turn LED OFF (Active-Low)
        sendNextionCommand("page1.t0.txt=\"Led Off\"");
      }
    }

    // 5. Update Nextion display sensor objects directly on page2
    String cmdTemp = "page2.t2.txt=\"" + String(temperature, 1) + " C\"";
    sendNextionCommand(cmdTemp.c_str());

    String cmdHum = "page2.t3.txt=\"" + String(humidity, 1) + " %\"";
    sendNextionCommand(cmdHum.c_str());
  }
}