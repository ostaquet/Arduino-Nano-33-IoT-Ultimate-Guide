/*
  BLE experiments

  This example:
   - reads the acceleration values from the LSM6DS3 sensor
   - show the position data to the serial
   - sends the data on BLE
   - expose the LED status on the BLE

  The circuit:
  - Arduino Nano 33 IoT

  created 7 Nov 2020
  by Olivier Staquet

  This example code is in the public domain.
*/

#include <Arduino_LSM6DS3.h>
#include <ArduinoBLE.h>

// Define custom BLE service for position (read-only)
BLEService posService("95ff7bf8-aa6f-4671-82d9-22a8931c5387");
BLEFloatCharacteristic posX("95ff7bf8-aa6f-4671-82d9-22a8931c5387", BLERead);
BLEFloatCharacteristic posY("f49caa00-17f8-4e92-b5fd-d27137ca4515", BLERead);
BLEFloatCharacteristic posZ("84f9b003-6d14-44d7-8db1-d574d29c10c3", BLERead);

// Define custom BLE service for LED management (read/write)
BLEService ledService("daaac223-ea6d-411f-8d8e-32bfb46d4bad");
BLEByteCharacteristic led("40369706-e126-4563-b7ae-3a34b45b3ab8", BLERead | BLEWrite);

void setup() {
  // Initialize internal LED (for visual debugging)
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // Initialize Serial connection
  Serial.begin(115200);

  // Initialize IMU
  if (!IMU.begin()) {
    // Failed to initialize IMU, blink the internal LED
    Serial.println("Failed initializing IMU");
    while (1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
  }

  // Initialize BLE
  if(!BLE.begin()) {
    // Failed to initialize BLE, blink the internal LED
    Serial.println("Failed initializing BLE");
    while (1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
  }

  // Set advertised local name and services UUID
  BLE.setDeviceName("Arduino Nano 33 IoT");
  BLE.setLocalName("BLE Experiment");

  posService.addCharacteristic(posX);
  posService.addCharacteristic(posY);
  posService.addCharacteristic(posZ);
  BLE.addService(posService);

  ledService.addCharacteristic(led);
  BLE.addService(ledService);

  // Set default values for characteristics
  posX.writeValue((float)0.0);
  posY.writeValue((float)0.0);
  posZ.writeValue((float)0.0);
  led.writeValue(0);

  // Start advertising
  BLE.advertise();
}

void loop() {
  // Listen for BLE
  BLEDevice central = BLE.central();

  // If a central is connected
  if(central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
  }

  // While central is still connected...
  while(central.connected()) {
    float x, y, z;
    byte ledValue = 0x0;

    // Read gyroscope values
    if (IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(x, y, z);
    }

    // Display gyroscope values on serial
    Serial.print("Position ");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(z);
    Serial.print("LED is ");
    Serial.println(ledValue);

    // Write values on BLE
    posX.writeValue(x);
    posY.writeValue(y);
    posZ.writeValue(z);
    led.readValue(ledValue);

    // Read values on BLE
    if(ledValue == 0x0) {
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
    }

    delay(1000);
  }

  // when the central disconnects, print it out:
  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
  delay(1000);
}
