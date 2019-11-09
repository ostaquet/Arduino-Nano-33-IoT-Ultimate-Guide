/*
  Arduino LSM6DS3 - Shake Detector

  This example reads the acceleration values from the LSM6DS3
  sensor and turn on the LED D13 when there is a shake of the 
  device.

  The circuit:
  - Arduino Uno WiFi Rev 2 or Arduino Nano 33 IoT

  created 9 Nov 2019
  by Olivier Staquet

  This example code is in the public domain.
*/

#include <Arduino_LSM6DS3.h>

void setup() {
  // Initialize Serial for log
  Serial.begin(115600);
  while (!Serial);

  // Initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // Initialize embedded LED
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delay(50);
}

void loop() {
  float x, y, z;

  // Read acceleration values
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    delay(5);
  }

  // If the shake is more than 3G, light on the LED for 1 second
  if(abs(x) > 3 || abs(y) > 3 || abs(z) > 3) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  }
}
