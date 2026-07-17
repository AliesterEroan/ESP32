#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

// Pin Definitions
#define DHTPIN 4
#define DHTTYPE DHT22

#define LED_RED 12
#define LED_GREEN 13
#define LED_BLUE 14

// Wi-Fi Credentials
const char *ssid = "TTBOX-G4VVXQ";
const char *password = "YABYCLV6GW";

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

// Helper function to read sensors and handle LED arguments
void processDataAndControls() {
  if (server.hasArg("red")) {
    String state = server.arg("red");
    digitalWrite(LED_RED, (state == "on") ? HIGH : LOW);
    Serial.println("[CONTROL] Red LED set to: " + state);
  }
  
  if (server.hasArg("green")) {
    String state = server.arg("green");
    digitalWrite(LED_GREEN, (state == "on") ? HIGH : LOW);
    Serial.println("[CONTROL] Green LED set to: " + state);
  }
  
  if (server.hasArg("blue")) {
    String state = server.arg("blue");
    digitalWrite(LED_BLUE, (state == "on") ? HIGH : LOW);
    Serial.println("[CONTROL] Blue LED set to: " + state);
  }
}

// 1. Endpoint for normal Text/Hyperlink View ( http://<your-ip>/ )
void handleRoot() {
  processDataAndControls(); // Update LEDs if arguments were passed

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) { t = 0.0; h = 0.0; }

  String redStatus = (digitalRead(LED_RED) == HIGH) ? "ON" : "OFF";
  String greenStatus = (digitalRead(LED_GREEN) == HIGH) ? "ON" : "OFF";
  String blueStatus = (digitalRead(LED_BLUE) == HIGH) ? "ON" : "OFF";

  String html = "<!DOCTYPE html><html><head><title>ESP32 Control</title></head><body>";
  html += "<h2>Environment Readings</h2>";
  html += "Current Temperature is: <b>" + String(t, 1) + " C</b>. Click <a href=\"/\">here</a> to refresh.<br>";
  html += "Current Humidity is: <b>" + String(h, 1) + " %</b>. Click <a href=\"/\">here</a> to refresh.<br>";
  html += "View raw data in <a href=\"/data\">JSON format here</a>.<br>";
  html += "<hr>";
  
  html += "<h2>RGB LED Controls</h2>";
  html += "Red LED (Pin 12) is currently <b>" + redStatus + "</b>.<br>";
  html += "Click <a href=\"/?red=on\">here</a> to turn the Red LED on pin 12 on.<br>";
  html += "Click <a href=\"/?red=off\">here</a> to turn the Red LED on pin 12 off.<br><br>";
  
  html += "Green LED (Pin 13) is currently <b>" + greenStatus + "</b>.<br>";
  html += "Click <a href=\"/?green=on\">here</a> to turn the Green LED on pin 13 on.<br>";
  html += "Click <a href=\"/?green=off\">here</a> to turn the Green LED on pin 13 off.<br><br>";
  
  html += "Blue LED (Pin 14) is currently <b>" + blueStatus + "</b>.<br>";
  html += "Click <a href=\"/?blue=on\">here</a> to turn the Blue LED on pin 14 on.<br>";
  html += "Click <a href=\"/?blue=off\">here</a> to turn the Blue LED on pin 14 off.<br>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

// 2. Endpoint for JSON View ( http://<your-ip>/data )
void handleJSON() {
  processDataAndControls(); // You can also pass control arguments directly to the JSON endpoint!

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) { t = 0.0; h = 0.0; }

  String redState = (digitalRead(LED_RED) == HIGH) ? "on" : "off";
  String greenState = (digitalRead(LED_GREEN) == HIGH) ? "on" : "off";
  String blueState = (digitalRead(LED_BLUE) == HIGH) ? "on" : "off";

  // Constructing the JSON string manually to keep it lightweight
  String json = "{";
  json += "\"temperature\":" + String(t, 1) + ",";
  json += "\"humidity\":" + String(h, 1) + ",";
  json += "\"led_status\":{";
  json += "\"red\":\"" + redState + "\",";
  json += "\"green\":\"" + greenState + "\",";
  json += "\"blue\":\"" + blueState + "\"";
  json += "}";
  json += "}";

  // Send with "application/json" content type headers so apps know how to read it
  server.send(200, "application/json", json);
}

void setup() {
  Serial.begin(115200);
  delay(1000); 
  
  Serial.println("\n==============================================");
  Serial.println("SYSTEM BOOT: Initializing ESP32 Smart Hub...");
  Serial.println("==============================================");

  dht.begin();
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);

  Serial.print("[WIFI] Connecting to: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\n\n==============================================");
  Serial.println("[SUCCESS] Wi-Fi Connected!");
  Serial.print("Assigned IP Address:  "); Serial.println(WiFi.localIP());
  Serial.println("==============================================");
  
  // Define our routes
  server.on("/", handleRoot);       // HTML View
  server.on("/data", handleJSON);   // JSON View
  
  server.begin();
  Serial.println("[SERVER] HTTP Web Server started.");
  Serial.print("[URL] HTML Dashboard: http://"); Serial.println(WiFi.localIP());
  Serial.print("[URL] JSON Endpoint:  http://"); Serial.print(WiFi.localIP()); Serial.println("/data");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    server.handleClient();
  }
}