# CO2 Indoor Monitor (MH-Z19B)
A CO2 Monitor is a device that helps you understand the environmental Carbon Dioxide (CO2) levels in an office, room and  other indoor area.  

![PROJECT_PHOTO](https://github.com/edorosh/co2-indoor-monitor/blob/master/resources/front.jpg)

It first warns and then alarms in case of CO2 level reaches a nonacceptable level. It has 4 Digit 7-Segment Display Module, a LED illumination along with a Buzzer. Currently the device is powered by a USB source only.  

CO2 Levels are measured as PPM (Parts Per Million). The standard outdoor level is around 350ppm, and is the optimum level for freshness. However, it can get up to 600ppm indoor without any adverse affects. Once it gets past 600ppm people will start noticing adverse affects.

The LED is GREEN when CO2  < 700ppm. It switches to BLUE when the level is < 1200ppm and finally it changes to red for the higher levels.

# Upload Firmware
New to Arduino? Check [this official HOWTO](https://www.arduino.cc/en/main/howto). Before uploading the sketch check if you have all requried libraries insalled. You may want to copy all of them inside `libraries` manually into %Home%/Arduino/libraries or install them all via "Manage Libraries" option.

# Project Structure

| Folder      | Description                          |
| ----------  | ------------------------------------ |
| `firmware`  | Arduino Firmware                     |
| `libraries` | All required libraries               |
| `3d`        | STL and Step files for the enclosure |
| `resources` | Resources for the README file        |  

# List of used libraries
* [GyverButton](https://github.com/AlexGyver/GyverLibs/tree/master/GyverButton)
* [GyverTimer](https://github.com/AlexGyver/GyverLibs/tree/master/GyverTimer)
* [MH-Z19](https://github.com/WifWaf/MH-Z19)
* [TM1637](https://github.com/avishorp/TM1637)
* [Non Blocking rtttl](https://github.com/cefn/non-blocking-rtttl-arduino)

# Bill of Materials
* PCB Prototype Board 3x7cm
* Arduino Nano
* MH-Z19B
* Female PCB pins
* Passive Buzzer 5v (12mm)
* 2-way switch
* Connecting wires
* RGB LED with common Cathode
* 4 digit 7 Segment Display TM1637
* 220 Ohm Resistor x2
* Hex Spacer 2M 6mm x2 with screws x2

# 3D Model
STL files for the enclosue are inside `3d` folder. Here you may find [Fusion 360 sources](https://a360.co/3mZy4vN).
I printed the parts with PETG material, 30% infill and 0.2mm layer height. PLA works worse and it easily breaks. The LED part is filled up by a Hot Glue.  The Display is fixed by a Hot Glue as well. THe PCB board is fixed by 2 Hex Spacers.

![INSIDE_PHOTO](https://github.com/edorosh/co2-indoor-monitor/blob/master/resources/inside.jpg)
![BACK_PHOTO](https://github.com/edorosh/co2-indoor-monitor/blob/master/resources/back.jpg)

# License
MIT License. Not for a commercial usage.

# TODO
* add a circuit scheme
* think about using platform.io
* add settings description
* add feature: blikning red
* add feature: repeating the melody
