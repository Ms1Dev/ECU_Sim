# ECU_Sim

### Overview

I created this device to help with developing a Java Android application for a university project. The app connected to a Bluetooth OBD-II device and so this allowed for development without the need for a vehicle.

### Requirements

- Arduino Uno
- CAN-BUS shield V1.2 by DiyMore
- Seeed-Studio's Arduino CAN library https://github.com/Seeed-Studio/Seeed_Arduino_CAN

There are other components but they aren't required for communication with the OBD-II device.

### Implementation 

How the device responds to requests from the OBD was inspired by a post I found here: https://dev.to/devjameshay/basic-ecu-simulator-using-an-arduino-1064. The hardware setup is a bit different but the main CAN logic is similar. Only a small number of sensors (PIDs) have been simulated as that is all I needed for my project but it is quite easy to add more, see https://en.wikipedia.org/wiki/OBD-II_PIDs#Standard_PIDs for more info on OBD PIDs.

### Power supply

One thing to note about the OBD-II device is that it is 12v but the signal wires are 5v. I initially used a voltage booster off the 5v to power the OBD but the voltage booster eventually failed. The power for the OBD now comes straight off a 12v power adapter and a 5v voltage regulator steps it down for everything else. You might have guessed I'm not an electrical engineer by reading this, but it's still working and hasn't set on fire (yet) so I think this setup is ok.


![image](https://github.com/Ms1Dev/ECU_Sim/blob/master/PXL_20240216_121644758.MP.jpg)
