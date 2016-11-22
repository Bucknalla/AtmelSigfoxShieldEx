#Sigfox OTA 2016 Workshop

###Introduction

Example for Atmel Sigfox shield ATA8520-EK2-E.

This Arduino sketch sends power supply voltage measure and temperature measure
every 15 minutes (or when shield button is pressed), using Sigfox network.

This sketch uses the Atmel Sigfox shield library included.

###Keynote

[Keynote](https://github.io)


###Frame composition

This example only uses 3 bytes, out of the maximum 12 bytes that can be sent using Sigfox.  

Power supply voltage in coded on the 2 last bytes, in mV.  

Temperature is read as a float but then converted and sent as a one byte integer, in °C.

####Example

Frame sent : **000000000000000000190CA3**

* Power supply voltage
  * 00000000000000000019**0CA3**
  * 0CA3<sub>16</sub> == 3235<sub>10</sub>
  * Voltage is 3235 mV
* Temperature
  * 000000000000000000**19**0CA3
  * 19<sub>16</sub> == 25<sub>10</sub>
  * Temperature is 25°C

###Get Hardware

* [Arduino Uno](http://store.arduino.cc/index.php?main_page=product_info&cPath=11&products_id=195)
* [Atmel Shield](http://www.atmel.com/tools/atak55002-v2.aspx)

###License

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

###Credits

Copyright (c) 2015 Daniele Denaro and

* FuturaGroup srl (www.futurashop.it)
* Open-Electronics (www.open-electronics.org)
* Atmel Corporation.  

All right reserved.
