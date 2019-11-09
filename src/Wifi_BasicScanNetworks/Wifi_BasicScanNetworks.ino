/*
  Arduino WifiNINA - Basic scan networks

  This example scans the network and blink the internal LED
  for one second if there is at least one network available.

  Circuit:
  * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

  created 9 Nov 2019
  by Olivier Staquet
*/


#include <WiFiNINA.h>

void setup() {
  // Initialize the internal LED
  pinMode(13, OUTPUT);
  
  // Check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    // If no module, don't continue and blink the LED
    while (true) {
      digitalWrite(13, LOW);
      delay(100);
      digitalWrite(13, HIGH);
      delay(100);
    }
  }
}

void loop() {
  // Scan for existing networks
  int numSsid = WiFi.scanNetworks();

  // If at least 1 network available, turn the LED on for 1 sec
  if(numSsid > 0) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  }
  
  delay(1000);
}
