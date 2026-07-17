#include <HardwareSerial.h> // Inclut la bibliothèque pour gérer la communication série matérielle
#include <DHT.h>            // Inclut la bibliothèque pour le capteur de température et d'humidité DHT

// ---------------- Définition des Broches (Pins) ----------------
#define DHTPIN 23           // Déclare que la broche DATA du capteur DHT22 est connectée au GPIO 23
#define DHTTYPE DHT22       // Spécifie le type de capteur utilisé (DHT22)
#define LED_PIN 2           // Déclare que la LED interne de l'ESP32 est sur le GPIO 2

// ---------------- Initialisation du Capteur ----------------
DHT dht(DHTPIN, DHTTYPE);   // Crée l'objet "dht" avec la broche et le type configurés

// ---------------- Communication Série avec l'Écran ----------------
HardwareSerial NextionSerial(2); // Initialise le port série matériel numéro 2 de l'ESP32 (UART2 : RX=16, TX=17)

// ---------------- Variables de Temps et de Stockage ----------------
unsigned long lastUpdate = 0;    // Stocke le temps du dernier rafraîchissement des capteurs (en millisecondes)
const long interval = 1000;      // Définit l'intervalle de mise à jour des données à 1000 ms (1 seconde)
String comm = "";                // Crée une chaîne de caractères vide pour stocker les commandes reçues de l'écran

float consigne = 24.0;  // Cette variable stocke la limite choisie avec le Slider (par défaut 24.0)

void setup() {
  Serial.begin(115200);        // Ouvre le port série USB du PC à 115200 bauds pour afficher les messages de debug
  NextionSerial.begin(9600, SERIAL_8N1, 16, 17); // Démarre la liaison série avec le Nextion à 9600 bauds (RX=16, TX=17)
  
  pinMode(LED_PIN, OUTPUT);    // Configure la broche de la LED interne comme une sortie numérique
  digitalWrite(LED_PIN, HIGH); // Éteint la LED interne au démarrage (Logique inversée : HIGH = Éteint)
  
  dht.begin();                 // Initialise et démarre le capteur DHT22
  
  // --- Synchronisation de l'Écran au Démarrage ---
  sendNextionCommand("rest");      // Envoie une commande de réinitialisation à l'écran Nextion
  delay(500);                      // Attend 500 millisecondes pour laisser le temps à l'écran de redémarrer
  sendNextionCommand("page2.h0.val=24"); // Force le curseur du slider (h0) à se placer sur la valeur 24 sur la page 2
  sendNextionCommand("page2.t4.txt=\"24\""); // Force la zone de texte (t4) à afficher "24" sur la page 2
}

// Fonction personnalisée pour envoyer des commandes textuelles au Nextion
void sendNextionCommand(const char* command) {
  NextionSerial.print(command);  // Envoie le texte de la commande via le port série UART2
  NextionSerial.write(0xFF);     // Envoie le premier octet de fin obligatoire pour le Nextion
  NextionSerial.write(0xFF);     // Envoie le deuxième octet de fin obligatoire
  NextionSerial.write(0xFF);     // Envoie le troisième octet de fin obligatoire
  Serial.print("Sent: ");        // Affiche le mot "Sent: " sur le moniteur série du PC
  Serial.println(command);       // Affiche la commande envoyée sur le moniteur série du PC
}

void loop() {
 // 1. Lecture des données provenant de l'écran Nextion
  if (NextionSerial.available() > 0) { // Vérifie si des octets sont en attente dans le buffer série de l'écran
    String command = NextionSerial.readStringUntil('\n'); // Lit la chaîne de caractères reçue jusqu'au saut de ligne
    command.trim();                    // Supprime les espaces vides ou caractères invisibles au début et à la fin
    comm = command;                    // Copie le résultat nettoyé dans notre variable globale "comm"
    
    Serial.print("Brut reçu du Nextion : ["); 
    Serial.print(command);
    Serial.println("]");
  }

  // 2. Traitement de la valeur du Slider (Recherche une commande qui commence par "Set:")
  if (comm.startsWith("Set:")) {       // Vérifie si le texte reçu commence par les 4 caractères "Set:"
    String valStr = comm.substring(4); // Extrait uniquement la partie numérique située après "Set:"
    valStr.trim();                     // Nettoie les espaces restants autour du nombre
    
    Serial.print("Texte extrait après Set: : [");
    Serial.print(valStr);
    Serial.println("]");

    if (valStr.length() > 0) {
      consigne = valStr.toFloat();     // Convertit enfin le texte propre en nombre float
      Serial.print("--> Consigne convertie avec SUCCÈS : ");
      Serial.print(consigne);
      Serial.println(" C");
    }
    
    comm = ""; // Vide la variable de commande pour indiquer qu'elle a été traitée
  }

  // 3. Gestion Manuelle de la LED via les Boutons (Optionnel, au cas où tu cliques sur On/Off)
  if (comm == "On") {              // Si l'écran a envoyé exactement le message "On"
    digitalWrite(LED_PIN, HIGH);    // Allume la LED directement
    sendNextionCommand("page1.t0.txt=\"Led On\"");
    comm = "";                     
  }
  if (comm == "Off") {             // Si l'écran a envoyé exactement le message "Off"
    digitalWrite(LED_PIN, LOW);   // Éteint la LED directement
    sendNextionCommand("page1.t0.txt=\"Led Off\"");
    comm = "";                     
  }

  // 4. Lecture du Capteur + Logique de Limiteur AUTOMATIQUE (Toutes les 1 seconde)
  unsigned long currentMillis = millis(); // Récupère le temps actuel écoulé
  if (currentMillis - lastUpdate >= interval) { // Vérifie si 1 seconde s'est écoulée
    lastUpdate = currentMillis;       // Sauvegarde le temps actuel pour le prochain cycle

    float temperature = dht.readTemperature(); // Lit la température ambiante actuelle du capteur DHT22
    float humidity = dht.readHumidity();       // Lit le taux d'humidité actuel du capteur DHT22

    if (isnan(temperature) || isnan(humidity)) { // Si le capteur ne répond pas correctement
      Serial.println("DHT read error!"); 
      return;                            
    }

    // --- LOGIQUE DU LIMITEUR THERMOSTAT ---
    if (temperature > consigne) { 
      // Si la pièce est PLUS CHAUDE que le nombre choisi sur le slider :
      digitalWrite(LED_PIN, LOW);         // ALLUME la LED (Logique inversée : LOW = Allumé)
      sendNextionCommand("page1.t0.txt=\"Led On\""); // Met à jour le texte sur la page de contrôle
    } 
    else { 
      // Si la température baisse et devient INFÉRIEURE ou ÉGALE à la consigne :
      digitalWrite(LED_PIN, HIGH);        // ÉTEINT la LED (Logique inversée : HIGH = Éteint)
      sendNextionCommand("page1.t0.txt=\"Led Off\""); // Met à jour le texte sur la page de contrôle
    }

    // 5. Envoi des valeurs mesurées vers la page 2 (page2)
    String cmdTemp = "page2.t2.txt=\"" + String(temperature, 1) + " C\"";
    sendNextionCommand(cmdTemp.c_str()); // Envoie la température réelle à t2

    String cmdHum = "page2.t3.txt=\"" + String(humidity, 1) + " %\"";
    sendNextionCommand(cmdHum.c_str()); // Envoie l'humidité réelle à t3
  }
}