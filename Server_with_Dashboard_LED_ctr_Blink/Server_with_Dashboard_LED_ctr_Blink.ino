#include <WiFi.h>
#include <WebServer.h>

#define RXD2 16
#define TXD2 17
#define LED_PIN 2 

WebServer server(80);
String qrData = "";
bool isConnected = false;

// --- BLINKING VARIABLES (Non-blocking using millis) ---
bool isBlinking = false;
unsigned long blinkInterval = 500; // Default: 500ms
unsigned long previousMillis = 0;
bool ledState = LOW;

// --- MODERN GLASSMORPHISM HTML, CSS, AND JS ---
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Quantum Control</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; font-family: '-apple-system', BlinkMacSystemFont, sans-serif; }
        body { background: linear-gradient(135deg, #0f172a 0%, #1e1b4b 100%); color: #f8fafc; min-height: 100vh; display: flex; justify-content: center; align-items: center; padding: 20px; }
        .glass-card { background: rgba(30, 41, 59, 0.45); backdrop-filter: blur(16px); -webkit-backdrop-filter: blur(16px); border: 1px solid rgba(255, 255, 255, 0.08); border-radius: 24px; padding: 40px 30px; width: 100%; max-width: 420px; box-shadow: 0 20px 40px rgba(0, 0, 0, 0.3); text-align: center; }
        h1 { font-size: 1.8rem; font-weight: 700; letter-spacing: -0.5px; background: linear-gradient(to right, #38bdf8, #818cf8); -webkit-background-clip: text; -webkit-text-fill-color: transparent; margin-bottom: 8px; }
        .status-badge { display: inline-flex; align-items: center; gap: 8px; background: rgba(56, 189, 248, 0.1); border: 1px solid rgba(56, 189, 248, 0.2); color: #38bdf8; padding: 6px 14px; border-radius: 9999px; font-size: 0.85rem; font-weight: 500; margin-bottom: 35px; }
        .pulse-dot { width: 8px; height: 8px; background-color: #38bdf8; border-radius: 50%; box-shadow: 0 0 0 0 rgba(56, 189, 248, 0.7); animation: pulse 1.6s infinite; }
        .control-label { font-size: 0.9rem; text-transform: uppercase; letter-spacing: 1px; color: #94a3b8; margin-bottom: 12px; margin-top: 15px; }
        .btn-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 16px; margin-bottom: 15px; }
        .btn { position: relative; border: none; padding: 14px; font-size: 0.95rem; font-weight: 600; border-radius: 14px; cursor: pointer; color: #ffffff; transition: all 0.25s cubic-bezier(0.4, 0, 0.2, 1); }
        .btn-on { background: linear-gradient(135deg, #0ea5e9 0%, #2563eb 100%); box-shadow: 0 4px 12px rgba(37, 99, 235, 0.2); }
        .btn-on:hover { box-shadow: 0 0 24px rgba(14, 165, 233, 0.4); transform: translateY(-2px); }
        .btn-off { background: rgba(255, 255, 255, 0.05); border: 1px solid rgba(255, 255, 255, 0.1); color: #cbd5e1; }
        .btn-off:hover { background: rgba(255, 255, 255, 0.1); color: #ffffff; transform: translateY(-2px); }
        
        /* --- BLINK STYLING --- */
        .btn-blink { background: linear-gradient(135deg, #a855f7 0%, #7c3aed 100%); width: 100%; box-shadow: 0 4px 12px rgba(124, 58, 237, 0.2); margin-bottom: 20px; }
        .btn-blink:hover { box-shadow: 0 0 24px rgba(168, 85, 247, 0.4); transform: translateY(-2px); }
        .slider-container { background: rgba(15, 23, 42, 0.3); border: 1px solid rgba(255, 255, 255, 0.05); padding: 16px; border-radius: 16px; margin-bottom: 25px; }
        .slider-header { display: flex; justify-content: space-between; font-size: 0.85rem; color: #cbd5e1; margin-bottom: 10px; }
        .slider { -webkit-appearance: none; width: 100%; height: 6px; background: rgba(255, 255, 255, 0.1); border-radius: 9999px; outline: none; }
        .slider::-webkit-slider-thumb { -webkit-appearance: none; appearance: none; width: 18px; height: 18px; background: #818cf8; border-radius: 50%; cursor: pointer; transition: transform 0.1s; }
        .slider::-webkit-slider-thumb:hover { transform: scale(1.2); background: #38bdf8; }

        .console-box { background: rgba(15, 23, 42, 0.6); border: 1px solid rgba(255, 255, 255, 0.05); border-radius: 12px; padding: 14px; font-family: 'Courier New', monospace; font-size: 0.85rem; color: #34d399; min-height: 48px; display: flex; align-items: center; justify-content: center; }
        @keyframes pulse { 0% { transform: scale(0.95); box-shadow: 0 0 0 0 rgba(56, 189, 248, 0.7); } 70% { transform: scale(1); box-shadow: 0 0 0 8px rgba(56, 189, 248, 0); } 100% { transform: scale(0.95); box-shadow: 0 0 0 0 rgba(56, 189, 248, 0); } }
    </style>
</head>
<body>
    <div class="glass-card">
        <h1>Node Server Hub</h1>
        <div class="status-badge"><div class="pulse-dot"></div><span>System Active</span></div>
        
        <div class="control-label">Static Link</div>
        <div class="btn-grid">
            <button class="btn btn-on" onclick="sendAction('/led/on')">ON</button>
            <button class="btn btn-off" onclick="sendAction('/led/off')">OFF</button>
        </div>

        <div class="control-label">Dynamic Frequency</div>
        <button class="btn btn-blink" onclick="sendAction('/led/blink')">TOGGLE BLINK MODE</button>
        
        <div class="slider-container">
            <div class="slider-header">
                <span>Blink Interval</span>
                <span id="speed-val">500 ms</span>
            </div>
            <input type="range" min="50" max="2000" value="500" class="slider" id="speed-slider" oninput="updateSpeed(this.value)">
        </div>
        
        <div class="control-label">Telemetry Log</div>
        <div class="console-box" id="console-out">Ready for commands...</div>
    </div>

    <script>
        function sendAction(endpoint) {
            const consoleBox = document.getElementById('console-out');
            consoleBox.style.color = '#94a3b8'; consoleBox.innerText = ">> Sending packet...";
            fetch(endpoint)
                .then(response => response.text())
                .then(data => { consoleBox.style.color = '#34d399'; consoleBox.innerText = ">> " + data; })
                .catch(err => { consoleBox.style.color = '#f87171'; consoleBox.innerText = ">> Err: Core Timeout"; });
        }

        function updateSpeed(value) {
            document.getElementById('speed-val').innerText = value + " ms";
            // Quietly stream the speed changes to the server as you drag the slider
            fetch('/led/speed?val=' + value)
                .then(response => response.text())
                .then(data => {
                    document.getElementById('console-out').style.color = '#a855f7';
                    document.getElementById('console-out').innerText = ">> Frequency: " + value + "ms";
                });
        }
    </script>
</body>
</html>
)rawliteral";

// --- NEW FEATURE: DIGITAL WELCOME MONITOR ---
void printWelcomeDashboard(String ipAddress) {
  Serial.println("\n\n==================================================");
  Serial.println("   🌐  ESP32 WEB SERVER INITIALIZED SUCCESSFULLY   ");
  Serial.println("==================================================");
  Serial.println(" Status:       ONLINE & LISTENING");
  Serial.print(" IP Address:   "); Serial.println(ipAddress);
  Serial.println("--------------------------------------------------");
  Serial.println(" 👉 HOW TO ACCESS YOUR DASHBOARD:");
  Serial.println(" 1. Ensure your phone/PC is on the SAME Wi-Fi network.");
  Serial.print(" 2. Open your browser and type or click this link:\n    http://");
  Serial.println(ipAddress);
  Serial.println("--------------------------------------------------");
  Serial.println(" ⚠️  TROUBLESHOOTING PRO-TIPS:");
  Serial.println(" • If the page doesn't load, make sure your browser");
  Serial.println("   isn't forcing 'https://'. It must be 'http://'.");
  Serial.println(" • Turn off any active VPNs on your phone or PC.");
  Serial.println("==================================================\n");
}

// --- WEB SERVER ENDPOINTS ---
void handleRoot() { server.send(200, "text/html", INDEX_HTML); }

void handleLEDOn() { 
  isBlinking = false; 
  digitalWrite(LED_PIN, HIGH); 
  server.send(200, "text/plain", "SUCCESS: Static Solid ON"); 
}

void handleLEDOff() { 
  isBlinking = false; 
  digitalWrite(LED_PIN, LOW); 
  server.send(200, "text/plain", "SUCCESS: Static Solid OFF"); 
}

void handleLEDBlink() {
  isBlinking = !isBlinking; // Reverse whatever state it's in
  String msg = isBlinking ? "SUCCESS: Blink Mode ACTIVE" : "SUCCESS: Blink Mode DISABLED";
  server.send(200, "text/plain", msg);
}

void handleLEDSpeed() {
  // Checks if the browser attached a speed value (?val=X) in the link URL string
  if (server.hasArg("val")) {
    String valString = server.arg("val");
    blinkInterval = valString.toInt(); // Turn text "500" into number 500
    server.send(200, "text/plain", "Interval updated");
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

// --- NETWORK UTILITIES ---
void parseAndConnect(String rawData) {
  Serial.println("\n[System] Parsing QR Code Data...");
  int ssidStart = rawData.indexOf("S:") + 2;
  int ssidEnd = rawData.indexOf(";", ssidStart);
  int passStart = rawData.indexOf("P:") + 2;
  int passEnd = rawData.indexOf(";", passStart);
  
  if (ssidStart > 1 && ssidEnd > ssidStart) {
    String ssid = rawData.substring(ssidStart, ssidEnd);
    String password = (passStart > 1 && passEnd > passStart) ? rawData.substring(passStart, passEnd) : "";
    
    Serial.print("[System] Attempting Connection to: "); Serial.println(ssid);
    WiFi.begin(ssid.c_str(), password.c_str());
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
      delay(500); Serial.print("."); attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
      server.on("/", handleRoot);
      server.on("/led/on", handleLEDOn);   
      server.on("/led/off", handleLEDOff); 
      server.begin();
      isConnected = true;
      
      // Fire our custom dashboard printout
      printWelcomeDashboard(WiFi.localIP().toString());
    } else {
      Serial.println("\n❌ [Error] Connection timeout. Please check credentials and scan again.");
    }
  } else {
    Serial.println("\n❌ [Error] Unknown QR format. Please scan a standard Wi-Fi network share QR code.");
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); 
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); 
  
  Serial.println("\n=== SYSTEM BOOT COMPLETED ===");
  Serial.println("📷 GM67 Scanner Module: READY");
  Serial.println("👉 Please present your phone's Wi-Fi sharing QR code...");
}

void loop() {
  if (!isConnected) {
    while (Serial2.available()) {
      char c = Serial2.read();
      if (c == '\r' || c == '\n') {
        if (qrData.length() > 0) { parseAndConnect(qrData); qrData = ""; }
      } else { qrData += c; }
      delay(2);
    }
  } else {
    server.handleClient();
     // --- NON-BLOCKING BLINK ALGORITHM ---
    if (isBlinking) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= blinkInterval) {
        previousMillis = currentMillis; // Remember the exact timestamp of this toggle
        ledState = !ledState;           // Invert the light state (HIGH to LOW or vice versa)
        digitalWrite(LED_PIN, ledState);
        
      }
  }
}