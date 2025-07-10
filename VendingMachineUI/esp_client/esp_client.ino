#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include <ArduinoJson.h>

const char* ssid = "pankaj_wifi";
const char* password = "x4rw6umd";

AsyncWebServer server(80);

// // Servo objects
// Servo servos[12];
// const int servoPins[12] = {23, 22, 21, 19, 18, 5, 4, 2, 15, 13, 12, 14};

// // Updated item names corresponding to each servo
// const char* itemNames[12] = {
//   "Arduino Uno", "NodeMCU- esp32", "Arduino nano", "Servo Motor", "DC motor",
//   "Bluetooth module", "Motor driver (L293D)", "Mini breadboard", "Ultrasonic sensors", "LCD  screen",
//   "Raspberry pi", "IR module"
// };
// Servo objects
Servo servos[8];
const int servoPins[8] = {23, 22, 21, 19, 18, 5, 12, 14};

// Updated item names corresponding to each servo
const char* itemNames[12] = {
  "Arduino Uno", "NodeMCU- esp32", "Arduino nano", "Servo Motor", "DC motor",
  "Bluetooth module", "Raspberry pi", "IR module"
};

void setup() {
  Serial.begin(115200);

  // Initialize the servos
  // for (int i = 0; i < 12; i++) {
  //   servos[i].attach(servoPins[i]);
  // }
   for (int i = 0; i < 8; i++) {
    servos[i].attach(servoPins[i]);
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  // Define the endpoint to handle POST requests
  server.on("/submit", HTTP_POST, [](AsyncWebServerRequest *request){
    if (request->hasParam("gmail", true) && request->hasParam("cart", true)) {
      String gmail = request->getParam("gmail", true)->value();
      String cart = request->getParam("cart", true)->value();

      Serial.println("Gmail: " + gmail);
      Serial.println("Cart: " + cart);

      // Process the cart data
      processCartData(cart);

      request->send(200, "text/plain", "Data received successfully");
    } else {
      request->send(400, "text/plain", "Missing parameters");
    }
  });

  // Start the server
  server.begin();
}

void loop() {
  // Put your main code here, to run repeatedly
}

void processCartData(String cart) {
  // Create a JSON document to parse the cart data
  DynamicJsonDocument doc(1024);

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, cart);

  if (error) {
    Serial.println("Failed to parse JSON");
    return;
  }

  // Process each item in the cart
  for (JsonObject item : doc.as<JsonArray>()) {
    String itemName = item["item"].as<String>();
    int quantity = item["quantity"];

    Serial.print("Item: ");
    Serial.println(itemName);
    Serial.print("Quantity: ");
    Serial.println(quantity);

    // Control the servo for the item
    controlServoForItem(itemName);
  }
}

void controlServoForItem(String itemName) {
  int servoIndex = -1;

  // Find the servo corresponding to the item name
  // for (int i = 0; i < 12; i++) {
  //   if (itemName.equalsIgnoreCase(itemNames[i])) {
  //     servoIndex = i;
  //     break;
  //   }
  // }
  for (int i = 0; i < 8; i++) {
    if (itemName.equalsIgnoreCase(itemNames[i])) {
      servoIndex = i;
      break;
    }
  }

  if (servoIndex != -1) {
    servos[servoIndex].attach(servoPins[servoIndex]);
    Serial.print("Controlling servo for ");
    Serial.println(itemName);
    int i;
    // Rotate the servo
    // servos[servoIndex].writeMicroseconds(1000); // Adjust if necessary for your servo
    // delay(500);
    // servos[servoIndex].writeMicroseconds(1500); 
    // delay(800);
    // servos[servoIndex].writeMicroseconds(3500); 
    // delay(450);
    for (i=180;i>0;i-=1){
      servos[servoIndex].write(360);
      delay(15); 
    }

    delay(1000);  // Wait to observe the movement
  
    servos[servoIndex].detach();  // Detach the servo to stop its movement
  
  //    delay(100);
  //  servos[servoIndex].attach(servoPins[servoIndex]);
  //     servos[servoIndex].write(0);
  //     delay(100); // Small delay before next half rotation
  //     servos[servoIndex].detach();  // Detach the servo to stop its movement
   
    Serial.println("Servo control complete for " + itemName);
  } else {
    Serial.println("Invalid item name: " + itemName);
  }
}