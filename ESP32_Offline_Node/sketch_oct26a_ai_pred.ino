#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include "model.h"

const int LED_PIN = 4;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
Eloquent::ML::Port::RandomForest classifier; 

unsigned long lastFaultTime = 0;
bool faultActive = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  
  if(!accel.begin()) {
    Serial.println("No ADXL345 sensor detected. Check wiring!");
    while(1);
  }
  Serial.println("Offline AI Node Booted Successfully!");
}

void loop() {
  sensors_event_t event; 
  
  // 1. Safely check if the sensor is responding
  if (!accel.getEvent(&event)) {
    Serial.println("Sensor read failed, retrying...");
    delay(500);
    return;
  }

  float sim_temp = 40.0; 
  float sim_current = 10.0;
  float dynamic_z = event.acceleration.z - 9.81;

  // 2. Deadzone filter: Ignore tiny resting jitters to prevent false faults
  if (abs(event.acceleration.x) < 0.15 && abs(event.acceleration.y) < 0.15 && abs(dynamic_z) < 0.15) {
    if (!faultActive) {
      digitalWrite(LED_PIN, LOW); // Ensure LED stays off when resting
    }
    delay(100);
    return; // Skip AI prediction when resting quietly
  }

  // 3. Pack features WITH the required 15.0 scaling factor for the model
  float features[5] = {
    event.acceleration.x * 15.0, 
    event.acceleration.y * 15.0, 
    dynamic_z * 15.0, 
    sim_temp, 
    sim_current
  };
  
  // 4. Run the TinyML prediction locally
  int prediction = classifier.predict(features);

  // Print live data to Serial Monitor for debugging
  Serial.print("X: "); Serial.print(event.acceleration.x);
  Serial.print(" | Y: "); Serial.print(event.acceleration.y);
  Serial.print(" | Pred: "); Serial.println(prediction);

  // 5. Timer logic for the 2-second LED hold
  if (prediction == 1) { 
    lastFaultTime = millis(); 
    faultActive = true;       
    Serial.println("🚨 FAULT TRIGGERED");
  }

  // Clear the fault state after 2 seconds of no new faults
  if (faultActive && (millis() - lastFaultTime >= 2000)) {
    faultActive = false; 
  }

  // 6. Trigger physical LED based on AI state
  if (faultActive) { 
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  
  delay(100);
}