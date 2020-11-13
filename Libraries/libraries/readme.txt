For information on installing libraries, see: http://www.arduino.cc/en/Guide/Libraries

= WiFi and Bluetooth Low Energy (BLE) library for the ATWINC3400 module

This library implements a network driver for devices based
on the ATMEL WINC3400 WiFi and BLE module.

There are many components to this library. The driver was written
by Atmel/Microchip. The WiFi101 library that abstracts the network
driver and makes it easier to use was written by Arduino LLC. 

The WiFi101 library was originally written for usage with the ATWINC1500.
This version has been forked and modified by Vulintus, Inc for usage
with the ATWINC3400.

The Vulintus Arduino BLE library is written in "the spirit of" the 
ArduinoBLE library. Some source files are direct derivatives of the
ArduinoBLE library, while other files consist of completely new code
by Vulintus Inc. While the BLE API is currently not a direct copy of the
ArduinoBLE API, it does attempt to create an abstraction layer that 
renders the underlying Atmel/Microchip BLE stack easier to use.

The Vulintus Arduino BLE library is still under development. Community
contributions are welcomed. Please contact David Pruitt (david@vulintus.com)
to become involved with this project.

For more information about the WiFi101 library please visit
https://www.arduino.cc/en/Reference/WiFi101

For more information about the original ArduinoBLE library please visit
https://www.arduino.cc/en/Reference/ArduinoBLE

== License ==

Copyright (c) Vulintus, Inc. All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
