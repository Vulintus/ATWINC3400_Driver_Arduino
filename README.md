# Welcome to the repository for the Vulintus ATWINC3400 driver for the Arduino core
This project is meant to make the ATWINC3400 wifi/ble module available for use within Arduino projects.

This read-me document serves as a guide on how to navigate the repository as well as how to contribute to the repository. It will be updated periodically as the repository changes.

## 1. Structure of the repository

This repository has a lot of components to it, and at first glance it be easy to become overwhelmed by it. The original API written by Atmel/Microchip to control the ATWINC3400 depended upon the Atmel Software Framework. I have reworked the Wifi/Bluetooth API so that it now works within Arduino projects. This should work for any Arduino project that uses a SAMD microcontroller.

This library is inspired by / based upon the WiFi101 library (written by Arduino, link: https://github.com/arduino-libraries/WiFi101) and the ArduinoBLE library (also written by Arduino, link: https://github.com/arduino-libraries/ArduinoBLE), so if you are familiar with those libraries you will feel right at home.

## 2. Contributing to this repository

We welcome community contributions to this library. It is currently under active development, and it still has some significant work to be completed. If you would like to contribute, please contact David Pruitt (david@vulintus.com).

