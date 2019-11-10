# Arduino Nano 33 IoT - Ultimate Guide
The purpose of this guide is to assemble the key information to use the Arduino Nano 33 IoT in your projects. At the writing of this guide, the Arduino Nano 33 IoT is quite new on the market and there was not plenty of information available on the internet.

I wrote this guide because I was a bit frustrated by the lack of information on the board and most of the insight here is coming from experiments. Some information is also coming from other websites, if it is the case, the resources are mentioned in the sections.

The topics covered in this guide are:
  *  Important things to remember
  *  Power supply and current consumption
  *  Sleep mode and idle mode
  *  Usage of Wifi module
  *  Usage of Bluetooth module (BLE)
  *  Usage of Inertial Measurement Unit (IMU)
  *  Usage of Serial communication
  *  Usage of I2C bus

## Important things to remember
The [official quick start guide](https://www.arduino.cc/en/Guide/NANO33IoT) is available on the Arduino website.

The Arduino Nano 33 IoT **only supports 3.3V** for inputs and outputs (IO pins) and it is not 5V tolerant like most of the other Arduino boards. Connecting more than 3.3V on IO pins will damage the board.

The pinouts is **compatible with the classic Arduino Nano pinouts**. Notice that the classic 5V pin is not wired by default and doesn't provide any power if you don't connect the VUSB jumper.

The pins A4 and A5 have an internal pull up and are designed to be used as an I2C bus. So, **usage of A4 and A5 as analog inputs is not recommended**.

## How to power the Arduino Nano 33 IoT?
According to the box, the Arduino Nano 33 IoT can be powered by the USB connector (5V) or through the Vin pin (4.5V - 21V) while its operating voltage is 3.3V. However, it seems that the supply voltage depends on the usage. There is a [discussion on the Arduino forum about this topic](https://forum.arduino.cc/index.php?topic=624569.0).

See the results of the experiments below regarding the power supply and the peak current consumption per voltage.

*WIP*

The programs below have been used to test the power consumption of the embedded modules:
*  **BareMinimum**: Just do nothing, included in Built-in Examples of Arduino IDE.
*  **Blink**: Blink the internal LED, included in Built-in Examples of Arduino IDE.
*  **IMU_ShakeDetector**: Use the IMU to detect acceleration and light on the internal LED ([source code](https://github.com/ostaquet/arduino-nano-33-iot-ultimate-guide/blob/master/src/IMU_ShakeDetector/IMU_ShakeDetector.ino))
*  **Wifi_BasicScanNetworks**: Use the Wifi to scan networks and light on the internal LED if there are networks available ([source code](https://github.com/ostaquet/arduino-nano-33-iot-ultimate-guide/blob/master/src/Wifi_BasicScanNetworks/Wifi_BasicScanNetworks.ino))
*  **Wifi_HTTPS_GET**: Use the Wifi to get the www.google.com page with SSL enabled and light on the internal LED if everything goes fine ([source code](https://github.com/ostaquet/arduino-nano-33-iot-ultimate-guide/blob/master/src/Wifi_HTTPS_GET/Wifi_HTTPS_GET.ino))

## How to enable the 5V pin on the Arduino Nano 33 IoT?
The Arduino Nano 33 IoT has a 5V pin which is not wired by default. If you need 5V for your project and you supply power through USB, you can connect the VUSB jumper to enable 5V power supply on the VUSB pin.

To to that, you just have to solder the VUSB jumper on the board.

![How to solder VUSB jumper on Arduino Nano 33 IoT](/images/Arduino_Nano_33_IoT_VUSB_jumper.jpg)

Notice that you cannot supply power to the board through this pin, it is only to have a handy 5V for your external components powered by the USB. If you don't power the board through the USB jack, you will stay with 0V on this pin.

## How to save power with the Arduino Nano 33 IoT?

## How to use the Wifi with the Arduino Nano 33 IoT?
The Wifi module embedded on the Arduino Nano 33 IoT is the popular [NINA W102](https://www.u-blox.com/sites/default/files/NINA-W10_DataSheet_%28UBX-17065507%29.pdf) ESP32 based module. It provides support of Wifi 802.11 b/g/n in the 2.4 GHz band and Bluetooth v4.2 (Bluetooth BR/EDR and Bluetooth Low Energy BLE). The module is fully compatible with the [official WiFiNINA library](https://www.arduino.cc/en/Reference/WiFiNINA).

To install the official library in the Arduino IDE, go in the menu *Tools -> Manage Libraries...* In the library manager, search for `WifiNINA` and install the `WiFiNINA` by `Arduino`.

![How to install WifiNINA with the library manager](/images/library_mgr_WifiNINA.png)

Useful ressources:
*  [Official documentation of the WiFiNINA library](https://www.arduino.cc/en/Reference/WiFiNINA)
*  [Datasheet of the NINA W102](https://www.u-blox.com/sites/default/files/NINA-W10_DataSheet_%28UBX-17065507%29.pdf)

## How to use the Bluetooth (BLE) with the Arduino Nano 33 IoT?

## How to use the Inertial Measurement Unit (IMU) with the Arduino Nano 33 IoT?
The IMU embedded in the Arduino Nano 33 IoT is the [LSM6DS3](https://www.st.com/resource/en/datasheet/lsm6ds3.pdf). It is composed by a 3-axis accelerometer and a 3-axis gyroscope. The LSM6DS3 on the Arduino Nano 33 IoT can be use easily through the I2C bus on the slave address 0x6A or through the [official Arduino LSM6DS3 library](https://github.com/arduino-libraries/Arduino_LSM6DS3).

To install the official library in the Arduino IDE, go in the menu *Tools -> Manage Libraries...* In the library manager, search for `LSM6DS3` and install the `Arduino_LSM6DS3` by `Arduino`.

![How to install LSM6DS3 with the library manager](/images/library_mgr_LSM6DS3.png)

The usage is described on the [official Arduino website](https://www.arduino.cc/en/Reference/ArduinoLSM6DS3).

Simple programs are available with the library:
*  [Simple accelerometer](https://github.com/arduino-libraries/Arduino_LSM6DS3/blob/master/examples/SimpleAccelerometer/SimpleAccelerometer.ino)
*  [Simple gyroscope](https://github.com/arduino-libraries/Arduino_LSM6DS3/blob/master/examples/SimpleGyroscope/SimpleGyroscope.ino)

Useful ressources:
*  [Official documentation of the Arduino LSM6DS3 library](https://www.arduino.cc/en/Reference/ArduinoLSM6DS3)
*  [Datasheet of the ST LSM6DS3](https://www.st.com/resource/en/datasheet/lsm6ds3.pdf)

## How to use serial communication? (Why there is no SoftwareSerial.h in the Arduino Nano 33 IoT?)

## How to use the I2C bus with the Arduino Nano 33 IoT?
