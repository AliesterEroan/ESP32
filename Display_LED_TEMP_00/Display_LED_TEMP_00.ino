#include <HardwareSerial.h>
#include <DHT.h>

// ---------------- Pins ----------------
#define DHTPIN 23
#define DHTTYPE DHT22
#define LED_PIN 2       // Indicator LED (Active-Low)

// ---------------- Sensors ----------------
DHT dht(DHTPIN, DHTTYPE);

// ---------------- Serial Communication ----------------
HardwareSerial NextionSerial(2); // RX2 (GPIO 16), TX2 (GPIO 17)

// ---------------- Timing & Variables ----------------
unsigned long lastUpdate = 0;
const long interval = 1000;    
String comm = "";

void setup() {
  Serial.begin(115200);        
  NextionSerial.begin(9600, SERIAL_8N1, 16, 17); 
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Off initially
  
  dht.begin();
  sendNextionCommand("rest");
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
  // 1. Listen for LED control button presses from Nextion
  if (NextionSerial.available() > 0) {
    String command = NextionSerial.readStringUntil('\n');
    command.trim(); 
    comm = command;
    
    Serial.print("Received: ");
    Serial.println(command);
  }

  // 2. LED Control Logic
  if (comm == "On") {
    digitalWrite(LED_PIN, HIGH);   // Turn LED On
    sendNextionCommand("page1.t0.txt=\"Led On\""); // Update status on page1
    comm = "";
  }
  if (comm == "Off") {
    digitalWrite(LED_PIN, LOW);  // Turn LED Off
    sendNextionCommand("page1.t0.txt=\"Led Off\""); // Update status on page1
    comm = "";
  }

  // 3. Periodic Temperature & Humidity Updates
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdate >= interval) {
    lastUpdate = currentMillis;

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Catch sensor reading errors
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("DHT read error!");
      return;
    }

    // Direct page targeting format: pagename.component.txt
    String cmdTemp = "page2.t2.txt=\"" + String(temperature, 1) + " C\"";
    sendNextionCommand(cmdTemp.c_str());

    String cmdHum = "page2.t3.txt=\"" + String(humidity, 1) + " %\"";
    sendNextionCommand(cmdHum.c_str());
  }
}