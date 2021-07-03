/****************************************************************************************
 * PowerOnTimer
 * ------------
 * Based on Arduino Nano IoT 33 and ChronoDot 2.1
 * By Olivier Staquet
 ***************************************************************************************/

// Libraries required
#include <Wire.h>
#include <DS3231.h>
#include <SPI.h>
#include <WiFiNINA.h>

// Global variables
DS3231 Clock;

/****************************************************************************************
 * Initialization
 ***************************************************************************************/
void setup() {
  // Warm-up
  delay(1000);

  // Prepare UI
  pinMode(LED_BUILTIN, OUTPUT);

  // Start the I2C interface
  Wire.begin();

  // Initialize the RTC clock
  // Disable alarm
  Clock.turnOffAlarm(2);
  // Disable oscialltor
  Clock.enableOscillator(false, false, 0);
  // Disable 32kHz output
  Clock.enable32kHz(false);
  // Set in 24-hour mode
  Clock.setClockMode(false);

  // Blink to show startup time
  for(uint8_t i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }

  // Prepare the next execution (defined by the day, hour, minute, second) + interval
  // Interval:
  //   0b1111 // each second
  //   0b1110 // Once per minute (when second matches)
  //   0b1100 // Once per hour (when minute and second matches)
  //   0b1000 // Once per day (when hour, minute and second matches)
  //   0b0000 // Once per month when date, hour, minute and second matches. Once per week if day of the week and A1Dy=true
  
  // Set alarm to happen every minute (change to your wanted interval)
  // Every time the seconds match 4 (every minute at the 4th second, the system wakes up)
  Clock.setA1Time(1, 2, 3, 4, 0b1110, false, false, false);
  Clock.turnOnAlarm(1);

  // Empty the I2C buffer
  while(Wire.available()) {
    Wire.read();
  }
}

/****************************************************************************************
 * Main program
 ***************************************************************************************/
void loop() {
  // Start doing something...

  // Blink the LED
  for(uint8_t i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }

  // Scan Wifi networks (drain a lot of current for stability testing)
  WiFi.scanNetworks();

  // Blink the LED
  for(uint8_t i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }

  // End doing something
  
  // Reset alarm is the last instruction of the program
  // When we reset the alarm, the power is shutdown for the system
  Clock.checkIfAlarm(1);

  // We never arrive here because the alarm is cleared
  // on the RTC which cause the shutdown of the circuit
  while(1);
}
