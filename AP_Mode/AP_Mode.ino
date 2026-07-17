#include <WiFi.h>
#include <NetworkClient.h>
#include <WiFiAP.h>
const char *ssid = "ESP32_Yessin";
const char *password = "123456789";
void setup() {
 WiFi.softAP(ssid, password);
 Serial.begin(115200);
}

void loop() {
int clients = WiFi.softAPgetStationNum();
Serial.printf("Clients : %d\n", clients);
delay(2000);
}
