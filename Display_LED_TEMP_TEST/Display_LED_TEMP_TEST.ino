#include <HardwareSerial.h> // Bibliothèque communication série mta3 el Nextion

// ---------------- Pins ----------------
#define LED_PIN 2           // Built-in LED mta3 el ESP32 (GPIO 2)

// ---------------- Communication Série ----------------
HardwareSerial NextionSerial(2); // UART2 (RX=16, TX=17) mta3 el Nextion

// ---------------- Variables ----------------
String comm = "";           // String bech nkhaznou fih el kelma li tji mel Nextion

void setup() {
  Serial.begin(115200);        // Port série USB mta3 el PC (Debug)
  NextionSerial.begin(9600, SERIAL_8N1, 16, 17); // Liaison série mta3 el Nextion
  
  pinMode(LED_PIN, OUTPUT);    // N-raj3ou el pin mta3 el LED en tant que sortie
  digitalWrite(LED_PIN, HIGH); // Éteint la LED au démarrage (Active-Low: HIGH = Off)
  
  // --- Synchronisation mta3 el Nextion fil au démarrage ---
  NextionSerial.print("rest");      
  NextionSerial.write(0xFF);     
  NextionSerial.write(0xFF);     
  NextionSerial.write(0xFF);     
}

// Fonction pour envoyer les changements de texte au Nextion
void sendNextionCommand(const char* command) {
  NextionSerial.print(command);  
  NextionSerial.write(0xFF);     
  NextionSerial.write(0xFF);     
  NextionSerial.write(0xFF);     
}

void loop() {
  // 1. Na3mlou lecture mta3 el donner li jaya mel Nextion
  if (NextionSerial.available() > 0) { 
    String command = NextionSerial.readStringUntil('\n'); // Naqrou el koudh 7atta el saut de ligne
    command.trim();                    // N-na77ou el espaces el zaydina
    comm = command;                    // N-7ottouha fi variable "comm"
    
    Serial.print("Brut reçu : ["); 
    Serial.print(command);
    Serial.println("]");
  }

  // 2. Control mta3 el LED bel Boutons (Ken 3la page1)
  if (comm == "On") {              // Ki enzel 3la bouton ON
    digitalWrite(LED_PIN, LOW);    // ALLUME la LED (Active-Low: LOW = On)
    sendNextionCommand("page1.t0.txt=\"Led On\""); // Mettre à jour el page1 uniquement
    Serial.println("-> LED Allumée !");
    comm = "";                     // N-fragh el variable
  }
  
  if (comm == "Off") {             // Ki enzel 3la bouton OFF
    digitalWrite(LED_PIN, HIGH);   // ÉTEINT la LED (Active-Low: HIGH = Off)
    sendNextionCommand("page1.t0.txt=\"Led Off\""); // Mettre à jour el page1 uniquement
    Serial.println("-> LED Éteinte !");
    comm = "";                     // N-fragh el variable
  }
}