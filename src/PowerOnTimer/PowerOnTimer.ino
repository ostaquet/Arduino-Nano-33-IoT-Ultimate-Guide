/****************************************************************************************
 * PowerOnTimer
 * ------------
 * Based on Arduino Nano IoT 33 and ChronoDot 2.1
 * By Olivier Staquet
 ***************************************************************************************/

// Libraries required
#include <Wire.h>
#include <DS3231.h>

// Global variables
DS3231 Clock;

/****************************************************************************************
 * Initialization
 ***************************************************************************************/
void setup() {
  // Wait 1 second (sometime, the wake-up is hard...)
  delay(1000);
  
  // Initialize LED
  pinMode(PIN_LED, OUTPUT);

  // On startup, blink 3 times fast...
  for(uint8_t i = 0; i < 3; i++) {
    digitalWrite(PIN_LED, HIGH);
    delay(100);
    digitalWrite(PIN_LED, LOW);
    delay(100);
  }

  // Start the I2C interface
  Wire.begin();

  // Alarm is not enabled! Should set alarm
  if(!Clock.checkAlarmEnabled(1))
  {
    Clock.setClockMode(false);
    // 0b1111 // each second
    // 0b1110 // Once per minute (when second matches)
    // 0b1100 // Once per hour (when minute and second matches)
    // 0b1000 // Once per day (when hour, minute and second matches)
    // 0b0000 // Once per month when date, hour, minute and second matches. Once per week if day of the week and A1Dy=true
    // Set alarm to happen every minute (change to your wanted interval)
    Clock.setA1Time(1, 1, 1, 0, 0b1110, false, false, false);
    Clock.turnOnAlarm(1);
  }

  // Empty the I2C buffer
  while(Wire.available()) {
    Wire.read();
  }
}

/****************************************************************************************
 * Main program
 ***************************************************************************************/
void loop() {
  // When waking-up, blink for 5 seconds
  for(uint8_t i = 0; i < 5; i++) {
    digitalWrite(PIN_LED, HIGH);
    delay(1000);
    digitalWrite(PIN_LED, LOW);
    delay(1000);
  }
  
  // Reset alarm to turn off the device
  Clock.checkIfAlarm(1);

  // Wait 10 seconds (if power down not wired)
  delay(10000);
}
