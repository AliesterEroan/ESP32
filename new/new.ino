#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// --- Configuration ---
const char* ssid     = "HotSpot1000";
const char* password = "12345678";
const char* mqtt_server = "test.mosquitto.org"; // e.g., "192.168.1.100" or a cloud broker
const int mqtt_port   = 1883;

// --- Pin Definitions ---
#define DHTPIN 4
#define DHTTYPE DHT22

const int LED_R_PIN = 12; // Change to your actual Red LED pin
const int LED_G_PIN = 14; // Change to your actual Green LED pin

// --- MQTT Topics ---
const char* topic_dht   = "iot/formagerie/esp32/dht22";
const char* topic_led_r = "iot/formagerie/esp32/led_R";
const char* topic_led_g = "iot/formagerie/esp32/led_G";

// --- Object Initializations ---
DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

// --- Timing Variables ---
unsigned long lastMsgTime = 0;
const unsigned long interval = 5000; // Publish every 5 seconds

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a unique client ID based on ESP32 MAC address
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Force an immediate status publish on connection/reconnection
      publishLedStatus();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void publishLedStatus() {
  // Read current physical state of the pins (0 for LOW, 1 for HIGH)
  String statusR = String(digitalRead(LED_R_PIN));
  String statusG = String(digitalRead(LED_G_PIN));

  client.publish(topic_led_r, statusR.c_str());
  client.publish(topic_led_g, statusG.c_str());
}

void setup() {
  Serial.begin(115200);
  
  // Initialize Pins
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  
  dht.begin();
  setup_wifi();
  
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsgTime > interval) {
    lastMsgTime = now;

    // 1. Read and Publish DHT22 Data
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      // Format payload as JSON string for easy parsing later
      String dhtPayload = "{\"temperature\":" + String(t, 2) + ",\"humidity\":" + String(h, 2) + "}";
      client.publish(topic_dht, dhtPayload.c_str());
      Serial.print("Published DHT: ");
      Serial.println(dhtPayload);
    }

    // 2. Publish LED States
    publishLedStatus();
    Serial.println("Published LED states.");
  }
}