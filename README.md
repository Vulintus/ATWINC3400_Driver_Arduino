# Welcome to the repository for the Vulintus Arduino BLE library

This project is meant to make the ATWINC3400 wifi/ble module available for use within Arduino projects.

This read-me document serves as a guide on how to navigate the repository as well as how to contribute to the repository. It will be updated periodically as the repository changes.

## 1. Structure of the repository

This repository has a lot of components to it, and at first glance it be easy to become overwhelmed by it. The original API written by Atmel/Microchip to control the ATWINC3400 depended upon the Atmel Software Framework. I have literally ripped the Wifi/Bluetooth API out of the Atmel Software Framework and severed all the links to it, and then resolved the necessary links within the Arduino API.

The entire original wifi/ble API written by Atmel/Microchip is available to use within this library, if you would prefer to use their original API rather than an abstraction of it. If that is what you would like to do, the relevant files to include are:

| File Name | Description |
| --- | --- |
| driver/include/m2m_wifi.h | The main entry point to the Atmel wifi API |
| ble/atmel_ble_api/include/at_ble_api.h | The main entry point to the Atmel BLE API |
| ble/atmel_ble_api/include/m2m_ble.h | Another important file for initializing BLE functionality |

Having said that, if you are reading this it is likely that you want an API that is more "user-friendly" than the original Atmel APIs, and that is where the rest of this library comes in. 

The folks over at Arduino wrote the handy WiFi101 library which nicely abstracts the wifi functionality of the ATWINC1500 and makes it easier to use. I have forked the WiFi101 library and placed it within this library to provide the wifi functionality for the ATWINC3400 with the same set of API calls. I have also made a few minor modifications within the WiFi101 library simply to "hook it up" properly to the WINC3400 and this version of the Atmel API.

With regard to BLE functionality, the ATWINC1500 did not provide it, but the ATWINC3400 does. The folks over at Arduino also wrote a nice "user friendly" BLE API, but for a completely different BLE module, and it is not exactly "compatible", but I wanted to make an API that was just as user-friendly as the ArduinoBLE API. So the Vulintus Arduino BLE API is written in "the spirit of" the ArduinoBLE API, but the API is not 1-for-1 identical. It is possible that as the library develops, there may become more and more parity between the two.

Here is a basic summary of the repository structure and its important pieces:

| File or Folder Name | Description |
| --- | --- |
| ble | Atmel/Microchip ATWINC3400 API |
| bsp | Atmel/Microchip ATWINC3400 API |
| bus_wrapper | Atmel/Microchip ATWINC3400 API |
| common | Atmel/Microchip ATWINC3400 API |
| driver | Atmel/Microchip ATWINC3400 API |
| programmer | Atmel/Microchip ATWINC3400 API |
| socket | Atmel/Microchip ATWINC3400 API |
| spi_flash | Atmel/Microchip ATWINC3400 API |
| utility | Arduino WiFi101 API |
| vulintus_arduino_ble | Vulintus Arduino BLE API for the ATWINC3400 |
| vulintus_helper | Vulintus Arduino BLE API for the ATWINC3400 |
| winc3400_ble_api | Atmel/Microchip ATWINC3400 API |
| ArduinoBLE.h | Primary entry point for using the Vulintus Arduino BLE API |
| WiFi101.h | Priamry entry point for using the WiFi101 API |

## 2. Contributing to this repository

We welcome community contributions to this library. It is currently under active development, and it still has a long ways to go before it is complete! If you would like to contribute, please contact David Pruitt (david@vulintus.com).

