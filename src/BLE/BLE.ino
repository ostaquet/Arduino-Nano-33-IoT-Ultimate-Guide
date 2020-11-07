/*
  BLE experiments

  This example:
   - reads the acceleration values from the LSM6DS3 sensor
   - sends the position data to the serial

  The circuit:
  - Arduino Nano 33 IoT

  created 7 Nov 2020
  by Olivier Staquet

  This example code is in the public domain.
*/

#include <Arduino_LSM6DS3.h>

void setup() {
  // Initialize internal LED (for visual debugging)
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Initialize Serial connection
  Serial.begin(115200);
  // while(!Serial.available()) {
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   delay(500);
  //   digitalWrite(LED_BUILTIN, LOW);
  //   delay(500);
  // }

  // Initialize IMU
  if (!IMU.begin()) {
    // Failed to initialize IMU, blink the internal LED
    while (1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
  }
}

void loop() {
  float x, y, z;

  // Read gyroscope values
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
    delay(900);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Show gyroscope values on serial
  Serial.print("Position ");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(z);
}
