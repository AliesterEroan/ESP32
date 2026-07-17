#include <HardwareSerial.h>
// Define the serial port for Nextion communication (e.g., Serial2 on ESP32)
HardwareSerial NextionSerial(2); 
const int ledPin = 2;
void setup() {
  Serial.begin(115200); // For debugging output
  NextionSerial.begin(9600, SERIAL_8N1, 16, 17); // RX2, TX2 for ESP32
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // Éteint la LED au démarrage
  sendNextionCommand("rest");
}
void sendNextionCommand(const char* command) {
  NextionSerial.print(command);
  NextionSerial.write(0xFF); // End of command bytes
  NextionSerial.write(0xFF);
  NextionSerial.write(0xFF);
  Serial.print("Sent: ");
  Serial.println(command);
}
long interval;
bool transmitADC;
int analogValue;
String comm;
void loop() {
  // 1. Lit ce que le Nextion envoie et le redirige vers le PC
  if (NextionSerial.available() > 0) {
    // Lit la chaîne de caractères envoyée par le Nextion
    String command = NextionSerial.readStringUntil('\n');
    command.trim(); // Supprime les espaces et retours à la ligne
    comm = command;
    // Affiche la commande reçue pour le débogage
    Serial.print("Received: ");
    Serial.println(command);
}
if(comm=="On"){
  sendNextionCommand("page1.t0.txt=\"Led On\"");
  digitalWrite(ledPin, LOW); // Éteint la LED au démarrage
  comm="";
}
if(comm=="Off"){
  sendNextionCommand("page1.t0.txt=\"Led Off\"");
  digitalWrite(ledPin, HIGH); // Éteint la LED au démarrage
  comm="";
}
}