# Arduino Nano 33 IoT - Ultimate Guide
The purpose of this guide is to assemble the key information to use the Arduino Nano 33 IoT in your projects. At the writing of this guide, the Arduino Nano 33 IoT is quite new on the market and there was not plenty of information available on the internet.

I wrote this guide because I was a bit frustrated by the lack of information on the board and most of the insight here is coming from experiments. Some information is also coming from other websites, if it is the case, the resources are mentioned in the sections.

The topics covered in this guide are:
  *  Important things to remember
  *  Power supply
  *  Current consumption
  *  Sleep mode and idle mode
  *  Usage of Wifi module
  *  Usage of Bluetooth module (BLE)
  *  Usage of Inertial Measurement Unit (IMU)
  *  Usage of Serial communication

## Important things to remember
The [official quick start guide](https://www.arduino.cc/en/Guide/NANO33IoT) is available on the Arduino website.

The Arduino Nano 33 IoT **only supports 3.3V** for inputs and outputs (IO pins) and it is not 5V tolerant like most of the other Arduino boards. Connecting more than 3.3V on IO pins will damage the board.

The pinouts is **compatible with the classic Arduino Nano pinouts**. The only difference is that the 5V pin on the classic Arduino Nano is not connected and doesn't supply voltage.

The pins A4 and A5 have an internal pull up and are designed to be used as an I2C bus. So, **usage of A4 and A5 as analog inputs is not recommended**.

## How to power the Arduino Nano 33 IoT?
According to the box, the Arduino Nano 33 IoT can be powered by the USB connector (5V) or through the Vin pin (4.5V - 21V) while its operating voltage is 3.3V. However, it seems that the supply voltage depends on the usage. There is a [discussion on the Arduino forum about this topic](https://forum.arduino.cc/index.php?topic=624569.0).

See the results of the experiments below regarding the power supply.

*WIP*

## What is the consumption of the Arduino Nano 33 IoT?

## How to save power with the Arduino Nano 33 IoT?

## How to use the Wifi with the Arduino Nano 33 IoT?

## How to use the Bluetooth (BLE) with the Arduino Nano 33 IoT?

## How to use the Inertial Measurement Unit (IMU) with the Arduino Nano 33 IoT?
The IMU embedded in the Arduino Nano 33 IoT is the [LSM6DS3](https://www.st.com/resource/en/datasheet/lsm6ds3.pdf). It is composed by a 3-axis accelerometer and a 3-axis gyroscope. The LSM6DS3 on the Arduino Nano 33 IoT can be use easily through the I2C bus on the slave address 0x6A or through the [official Arduino LSM6DS3 library](https://github.com/arduino-libraries/Arduino_LSM6DS3).

To install the official library in the Arduino IDE, go in the menu *Tools -> Manage Libraries...* In the library manager, search for `LSM6DS3` and install the `Arduino_LSM6DS3` by `Arduino`.

![GitHub Logo](/images/library_mgr_LSM6DS3.png)

The usage is described on the [official Arduino website](https://www.arduino.cc/en/Reference/ArduinoLSM6DS3).

Simple programs are available with the library:
*  [Simple accelerometer](https://github.com/arduino-libraries/Arduino_LSM6DS3/blob/master/examples/SimpleAccelerometer/SimpleAccelerometer.ino)
*  [Simple gyroscope](https://github.com/arduino-libraries/Arduino_LSM6DS3/blob/master/examples/SimpleGyroscope/SimpleGyroscope.ino)

For the consumption and power supply testing, the program [Shake Detector](https://github.com/ostaquet/arduino-nano-33-iot-ultimate-guide/blob/master/src/IMU_ShakeDetector/IMU_ShakeDetector.ino) has been used.

## How to use serial communication? (Why there is no SoftwareSerial.h in the Arduino Nano 33 IoT?

