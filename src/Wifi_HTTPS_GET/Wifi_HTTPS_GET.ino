/*
  Arduino WifiNINA - HTTP get over SSL

  This example connects to the network, try to connect to https://www.google.com 
  and blink the internal LED if we get the return code 200 and receive data

  Circuit:
  * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

  created 9 Nov 2019
  by Olivier Staquet
*/

#include "Connectivity.h"

void setup() {
  Serial.begin(115200);
  delay(5000);
  
  // Initialize the internal LED
  pinMode(13, OUTPUT);
  
  // Start the connectivity
  if (Connectivity.begin("your_network", "your_password", "8.8.8.8") != 0) {
    // If not OK, don't continue and blink the LED
    while (true) {
      digitalWrite(13, LOW);
      delay(100);
      digitalWrite(13, HIGH);
      delay(100);
    }
  }

  Connectivity.connect();
}

void loop() {
  uint8_t rc = Connectivity.get("www.google.com", "/", 5000);
  if(rc == 0) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  }
  delay(1000);
}
