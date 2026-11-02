#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// --- UPDATE THESE THREE LINES ---
const char* ssid = "moto";
const char* password = "pass12345";
const char* mqtt_server = "10.122.197.108"; // e.g., "192.168.1.15"

const int LED_PIN = 4;
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup_wifi() {
  delay(10);
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected successfully!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32_Predictive_Node")) {
      Serial.println("Connected to Broker!");
      client.subscribe("machine/alarms");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  if (String(topic) == "machine/alarms") {
    if (message == "SHUTDOWN") {
      digitalWrite(LED_PIN, HIGH); // Turn LED ON
      Serial.println("🚨 FAULT DETECTED: LED ON");
    } 
    else if (message == "NORMAL") {
      digitalWrite(LED_PIN, LOW); // Turn LED OFF
      Serial.println("✅ SYSTEM HEALTHY: LED OFF");
    }
  }
}
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  if(!accel.begin()) {
    Serial.println("No ADXL345 sensor detected.");
    while(1);
  }
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); 
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  sensors_event_t event; 
  accel.getEvent(&event);

  float sim_temp = 40.0 + ((float)random(0, 50) / 10.0); 
  float sim_current = 10.0 + ((float)random(0, 20) / 10.0);

  // Format exactly like the old serial data: X:val,Y:val,Z:val
// Subtract gravity (9.81) so a flat sensor outputs ~0
float dynamic_z = event.acceleration.z - 9.81;

String payload = "X:" + String(event.acceleration.x) + 
                 ",Y:" + String(event.acceleration.y) + 
                 ",Z:" + String(dynamic_z) +
                 ",Temp:" + String(sim_temp) +
                 ",Current:" + String(sim_current);

                
  // Broadcast the data to the "sensor/vibration" topic
  client.publish("sensor/vibration", payload.c_str());
  
  delay(100);
}