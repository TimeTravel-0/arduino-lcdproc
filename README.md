# arduino-lcdproc
small arduino sketch to interface with lcdproc and drive a hd44780 compatible display

![hardware front view](photo_2021-05-18_14-51-21.jpg?raw=true "front view")
![hardware back view](photo_2021-05-18_14-51-28.jpg?raw=true "back view")

To make this work the following parts are needed
- LCDproc itself creates/provides the content to be displayed --> config file provided
- LCDproc / LCDd is a deamon accepting data via TCP and forwarding it to a connected display --> config file provided
- Arduino sketch to connect LCDd to the actual HD44780 compatible display --> sketch provided

Hardware I used (use any HD44780 compatible display you like):
- display module from an old laser printer (fits in 5.25" bay), described here: http://elektronikvelemciler.blogspot.com/2011/08/cm2048r-2-lcd-ekrann-attiny2313-ile.html
- cheap Arduino nano clone with Mega328P

Software used:
- Arduino IDE 1.8.15
- liquid crystal LCD library (included with Arduino IDE): https://www.arduino.cc/en/Tutorial/LibraryExamples/LiquidCrystalSerialDisplay
- LCDproc http://lcdproc.omnipotent.net/

References:
- https://github.com/lcdproc/lcdproc/blob/master/server/drivers/hd44780-serial.h (escape code / which device fits best)
- http://lcdproc.sourceforge.net/docs/current-user.html#hd44780-lcdserializer
- http://manpages.ubuntu.com/manpages/trusty/man8/LCDd.8.html
- https://lcdproc.omnipotent.narkive.com/lnP7cKIQ/lcdproc-on-diy-usb-serial-lcd-on-mac-os-x-10-5-4
- https://github.com/arduino-libraries/LiquidCrystal/blob/master/src/LiquidCrystal.cpp
- https://manpages.debian.org/testing/lcdproc/LCDd.8.en.html
