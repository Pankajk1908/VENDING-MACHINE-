#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

const char* ssid = "OPPO A78 5G";
const char* password = "x4rw6umd";

IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  Serial.println("SPIFFS mounted successfully");

  // Connect to Wi-Fi
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  unsigned long startAttemptTime = millis();

  // Wait for connection or timeout (10 seconds)
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(100);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to WiFi");
    return;
  }

  // Define routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/styles/styles.css", HTTP_GET, handleCss);
  server.on("/scripts/scripts.js", HTTP_GET, handleJs);

  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(404, "text/plain", "File Not Found");
    Serial.println("index.html not found");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleCss() {
  File file = SPIFFS.open("/styles.css", "r");
  if (!file) {
    server.send(404, "text/plain", "File Not Found");
    Serial.println("styles.css not found");
    return;
  }
  server.streamFile(file, "text/css");
  file.close();
}

void handleJs() {
  File file = SPIFFS.open("/scripts.js", "r");
  if (!file) {
    server.send(404, "text/plain", "File Not Found");
    Serial.println("scripts.js not found");
    return;
  }
  server.streamFile(file, "application/javascript");
  file.close();
}
