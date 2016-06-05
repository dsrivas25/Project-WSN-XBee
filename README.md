# Design and Implementation of an Open-Source Wireless Sensor Network Development Platform
Designed a library to provide interfaces to WSN peripherals which enables user to set XBee Series 1 as well as Series 2 parameters and create, send and receive data packets.

#Background
There is a growing need for a variety of Wireless Sensor Network (WSN) development platforms.
Development platforms allow researchers to quickly implement sensor data collection. Most platforms add little support for interfacing with a variety of sensors. TinyOS, an operating system designed for sensor networks, operates on a variety of different hardware platforms. It is very difficult to add sensors that are not on supported sensor boards using TinyOS. Also the support for developing new drivers is limited.

#Motivation
Stiquimote is being designed to avoid the limitations presented by the TinyOS platform. Digi's XBee radio modules are very popular. An XBee module would be used to send and receive data between a beacon and an independently traversing robot almost instantaneously.

#Hardware
The ATmega2560 used in the project is capable of controling multiple sensors. The board is approx. 2 cm x 3 cm. ICSP header pins were placed to upload C code with an AVR programmer. An FTDI chip was attached to the Mini USB for serial communication. The position of the XBee faces the antenna away from the rest of the board, allowing the use of any type of antenna.

#Software
Developed a software library to provide simple interfaces to peripherals. This C library is used to construct and send packages, receive packages and change XBee settings. It supports both series 1 and series 2 XBee modules. The debugging problems were simplified with the use of avr-gcc and XBee.

#Conclusion
The Stiquimote provides easy project development for wireless sensor networks. The platform is easily modified to suit application needs and makes adding custom sensor quick and efficient.
