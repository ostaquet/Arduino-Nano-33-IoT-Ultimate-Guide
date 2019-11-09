# Arduino Nano 33 IoT - Ultimate guide
The purpose of this guide is to assemble the key information to use the Arduino Nano 33 IoT in your projects. At the writing of this guide, the Arduino Nano 33 IoT is quite new on the market and there were not plenty of information available on the internet.

I wrote this guide because I was a bit frustrated by the lack of information on the board and most of the insight here are coming from experiments. Some information are also coming from other websites, if it is the case, the ressources are mentionned in the sections.

The topics covered in this guide are:
  *  Important things to remember
  *  How to power the board?
  *  What about the consumption of the board?
  *  How to set the board in sleep mode to save power?
  *  How to use the Wifi?
  *  How to use the Bluetooth (BLE)?
  *  How to use the IMU?
  *  How to use *Software Serial*? (a.k.a. Why there is no `SoftwareSerial.h` on the Arduino Nano 33 IoT?)

## Important things to remember
The Arduino Nano 33 IoT **only supports 3.3V** for inputs and outputs (IO pins) and it is not 5V tolerant like most of the other Arduino boards. Connecting more than 3.3V on IO pins will damage the board.

The pinouts is **compatible with the classic Arduino Nano pinouts**. The only difference is that the 5V pin on the classic Arduino Nano is not connected and doesn't supply voltage.

The pins A4 and A5 have an internal pull up and are designed to be used as an I2C bus. So, **usage of A4 and A5 as analog inputs is not recommended**.

## How to power the Arduino Nano 33 IoT?
