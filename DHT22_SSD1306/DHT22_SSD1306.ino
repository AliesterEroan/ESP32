#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>
#include "DHT.h"
#include "time.h"

// --- Configuration ---
const char* ssid     = "MyWiFi";
const char* password = "12345678";
const char* mqtt_server = "test.mosquitto.org";

// --- Hardware Pin Definitions ---
#define DHTPIN 4       // Connect DHT22 data pin here
#define DHTTYPE DHT22
#define LED_GREEN 5
#define LED_YELLOW 23
#define LED_RED 3

// --- MQTT Topics ---
const char* topic_temp = "lab7/node1/temperature";
const char* topic_hum  = "lab7/node1/humidity";
const char* topic_ledg = "lab7/node1/Led_G";
const char* topic_ledy = "lab7/node1/Led_Y";
const char* topic_ledr = "lab7/node1/Led_R";

// --- NTP Time Server Settings ---
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;       // Adjust according to your timezone (e.g., 3600 = UTC+1)
const int   daylightOffset_sec = 0;

// Global Instances
DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient mqttClient(espClient);
WebServer server(80);

// Global State Variables
float temp = 0.0;
float hum = 0.0;
String captureTime = "N/A";
unsigned long lastUpdate = 0;

// Helper function to fetch current local time string
String getLocalTimeString() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return "Time Sync Error";
  }
  char timeStringBuff[50];
  strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(timeStringBuff);
}

// --- MQTT Incoming Message Callback (Allows Control via MQTT) ---
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  String strTopic = String(topic);
  Serial.printf("MQTT Command Received [%s]: %s\n", topic, message.c_str());
  
  // Control logic based on incoming MQTT payload ("ON" or "OFF")
  if (strTopic == topic_ledg) {
    digitalWrite(LED_GREEN, (message == "ON") ? HIGH : LOW);
  } else if (strTopic == topic_ledy) {
    digitalWrite(LED_YELLOW, (message == "ON") ? HIGH : LOW);
  } else if (strTopic == topic_ledr) {
    digitalWrite(LED_RED, (message == "ON") ? HIGH : LOW);
  }
}

// --- Web Server Page ---
void handleRoot() {
  // Toggle processing via local Web Interface
  if (server.hasArg("toggle")) {
    String targetLed = server.arg("toggle");
    if (targetLed == "green") {
      digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
      mqttClient.publish(topic_ledg, digitalRead(LED_GREEN) ? "ON" : "OFF");
    } else if (targetLed == "yellow") {
      digitalWrite(LED_YELLOW, !digitalRead(LED_YELLOW));
      mqttClient.publish(topic_ledy, digitalRead(LED_YELLOW) ? "ON" : "OFF");
    } else if (targetLed == "red") {
      digitalWrite(LED_RED, !digitalRead(LED_RED));
      mqttClient.publish(topic_ledr, digitalRead(LED_RED) ? "ON" : "OFF");
    }
    server.sendHeader("Location", "/");
    server.send(303);
    return;
  }

  // HTML Presentation Layer
  String html = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>ESP32 Lab Control</title>";
  html += "<style>body{font-family:Arial; text-align:center; margin-top:50px; background-color:#f4f4f9;}";
  html += ".btn{display:inline-block; padding:10px 20px; margin:10px; font-size:16px; color:white; text-decoration:none; border-radius:5px;}";
  html += ".btn-g{background-color:#4CAF50;} .btn-y{background-color:#FFC107; color:black;} .btn-r{background-color:#f44336;}";
  html += ".card{background:white; padding:20px; margin:20px auto; width:300px; border-radius:10px; box-shadow:0 4px 8px rgba(0,0,0,0.1);}</style>";
  html += "<script>setInterval(function(){ location.reload(); }, 2000);</script>"; 
  html += "</head><body>";
  
  html += "<h2>ESP32 Dashboard & Control</h2>";
  html += "<div class='card'>";
  html += "<h3>Sensor Data</h3>";
  html += "<p><b>Temperature:</b> " + String(temp) + " &deg;C</p>";
  html += "<p><b>Humidity:</b> " + String(hum) + " %</p>";
  html += "<p style='font-size:12px; color:gray;'>Captured at: " + captureTime + "</p>";
  html += "</div>";

  html += "<div class='card'><h3>LED Controls</h3>";
  html += "<p>Green Status: " + String(digitalRead(LED_GREEN) ? "<b>ON</b>" : "OFF") + "</p>";
  html += "<a href='/?toggle=green' class='btn btn-g'>Toggle Green</a>";
  html += "<p>Yellow Status: " + String(digitalRead(LED_YELLOW) ? "<b>ON</b>" : "OFF") + "</p>";
  html += "<a href='/?toggle=yellow' class='btn btn-y'>Toggle Yellow</a>";
  html += "<p>Red Status: " + String(digitalRead(LED_RED) ? "<b>ON</b>" : "OFF") + "</p>";
  html += "<a href='/?toggle=red' class='btn btn-r'>Toggle Red</a>";
  html += "</div>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

// --- MQTT Connection Handler ---
void reconnectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-" + String(random(0, 0xffff), HEX);
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("connected");
      
      // CRITICAL: Subscribe to the LED topics so the ESP32 listens for remote control commands
      mqttClient.subscribe(topic_ledg);
      mqttClient.subscribe(topic_ledy);
      mqttClient.subscribe(topic_ledr);
      Serial.println("Subscribed to LED control topics.");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 3 seconds");
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  dht.begin();

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Waiting for NTP time sync...");
  struct tm timeinfo;
  while(!getLocalTime(&timeinfo)){
     delay(500);
     Serial.print(".");
  }
  Serial.println("\nTime Synchronized!");

  // Setup MQTT server configuration and assign the incoming callback function
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(mqttCallback);

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP Web Server started.");
}

void loop() {
  server.handleClient();
  
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  mqttClient.loop();

  // Non-blocking telemetry capture interval (every 2 seconds)
  unsigned long now = millis();
  if (now - lastUpdate >= 2000) {
    lastUpdate = now;

    float newH = dht.readHumidity();
    float newT = dht.readTemperature();

    if (!isnan(newH) && !isnan(newT)) {
      temp = newT;
      hum = newH;
      captureTime = getLocalTimeString();

      char tempStr[8];
      char humStr[8];
      dtostrf(temp, 1, 2, tempStr);
      dtostrf(hum, 1, 2, humStr);

      mqttClient.publish(topic_temp, tempStr);
      mqttClient.publish(topic_hum, humStr);

      Serial.printf("[%s] Published -> Temp: %s C, Hum: %s %%\n", captureTime.c_str(), tempStr, humStr);
    } else {
      Serial.println("Error: Failed reading metrics from DHT22!");
    }
  }
}