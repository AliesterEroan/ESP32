#include <WiFi.h>
#include <WebServer.h>

#define RXD2 16
#define TXD2 17
#define LED_PIN 2 

WebServer server(80);
String qrData = "";
bool isConnected = false;

// --- MODERN GLASSMORPHISM HTML, CSS, AND JS ---
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 LED Control</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; font-family: '-apple-system', BlinkMacSystemFont, sans-serif; }
        body { background: linear-gradient(135deg, #0f172a 0%, #1e1b4b 100%); color: #f8fafc; min-height: 100vh; display: flex; justify-content: center; align-items: center; padding: 20px; }
        .glass-card { background: rgba(30, 41, 59, 0.45); backdrop-filter: blur(16px); -webkit-backdrop-filter: blur(16px); border: 1px solid rgba(255, 255, 255, 0.08); border-radius: 24px; padding: 40px 30px; width: 100%; max-width: 420px; box-shadow: 0 20px 40px rgba(0, 0, 0, 0.3); text-align: center; }
        h1 { font-size: 1.8rem; font-weight: 700; letter-spacing: -0.5px; background: linear-gradient(to right, #38bdf8, #818cf8); -webkit-background-clip: text; -webkit-text-fill-color: transparent; margin-bottom: 8px; }
        .status-badge { display: inline-flex; align-items: center; gap: 8px; background: rgba(56, 189, 248, 0.1); border: 1px solid rgba(56, 189, 248, 0.2); color: #38bdf8; padding: 6px 14px; border-radius: 9999px; font-size: 0.85rem; font-weight: 500; margin-bottom: 35px; }
        .pulse-dot { width: 8px; height: 8px; background-color: #38bdf8; border-radius: 50%; box-shadow: 0 0 0 0 rgba(56, 189, 248, 0.7); animation: pulse 1.6s infinite; }
        .control-label { font-size: 0.9rem; text-transform: uppercase; letter-spacing: 1px; color: #94a3b8; margin-bottom: 15px; }
        .btn-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 16px; margin-bottom: 30px; }
        .btn { position: relative; border: none; padding: 16px; font-size: 1rem; font-weight: 600; border-radius: 14px; cursor: pointer; color: #ffffff; transition: all 0.25s cubic-bezier(0.4, 0, 0.2, 1); overflow: hidden; }
        .btn-on { background: linear-gradient(135deg, #0ea5e9 0%, #2563eb 100%); box-shadow: 0 4px 12px rgba(37, 99, 235, 0.2); }
        .btn-on:hover { box-shadow: 0 0 24px rgba(14, 165, 233, 0.4); transform: translateY(-2px); }
        .btn-off { background: rgba(255, 255, 255, 0.05); border: 1px solid rgba(255, 255, 255, 0.1); color: #cbd5e1; }
        .btn-off:hover { background: rgba(255, 255, 255, 0.1); color: #ffffff; transform: translateY(-2px); }
        .btn:active { transform: translateY(1px); }
        .console-box { background: rgba(15, 23, 42, 0.6); border: 1px solid rgba(255, 255, 255, 0.05); border-radius: 12px; padding: 14px; font-family: 'Courier New', monospace; font-size: 0.85rem; color: #34d399; min-height: 48px; display: flex; align-items: center; justify-content: center; }
        @keyframes pulse { 0% { transform: scale(0.95); box-shadow: 0 0 0 0 rgba(56, 189, 248, 0.7); } 70% { transform: scale(1); box-shadow: 0 0 0 8px rgba(56, 189, 248, 0); } 100% { transform: scale(0.95); box-shadow: 0 0 0 0 rgba(56, 189, 248, 0); } }
    </style>
</head>
<body>
    <div class="glass-card">
        <h1>Server Hub</h1>
        <div class="status-badge"><div class="pulse-dot"></div><span>System Active</span></div>
        <div class="control-label">Hardware Link</div>
        <div class="btn-grid">
            <button class="btn btn-on" onclick="sendAction('on')">ON</button>
            <button class="btn btn-off" onclick="sendAction('off')">OFF</button>
        </div>
        <div class="control-label">Telemetry Log</div>
        <div class="console-box" id="console-out">Ready for commands...</div>
    </div>
    <script>
        function sendAction(state) {
            const consoleBox = document.getElementById('console-out');
            consoleBox.style.color = '#94a3b8'; consoleBox.innerText = ">> Sending packet...";
            fetch('/led/' + state)
                .then(response => response.text())
                .then(data => { consoleBox.style.color = '#34d399'; consoleBox.innerText = ">> " + data; })
                .catch(err => { consoleBox.style.color = '#f87171'; consoleBox.innerText = ">> Err: Core Timeout"; });
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
void handleLEDOn() { digitalWrite(LED_PIN, HIGH); Serial.println("[Web Log] Command received: LED ON"); server.send(200, "text/plain", "SUCCESS: LED turned ON"); }
void handleLEDOff() { digitalWrite(LED_PIN, LOW); Serial.println("[Web Log] Command received: LED OFF"); server.send(200, "text/plain", "SUCCESS: LED turned OFF"); }

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
  }
}