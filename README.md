# The Claw Crane

Collaboration with artist [Estefanía B. Flores](https://www.instagram.com/estefantastic) for her master's thesis at
[Goldsmiths, University of London](https://www.gold.ac.uk/).

Old claw crane controlled with an [Arduino UNO](https://store.arduino.cc/arduino-uno-rev3) microcontroller board.

![Schematic](breadboard.png)

## Motors

There are three DC motors, but we will only use two.

They seem to be [12V Crouzet DC brush geared motors (828610)](https://soda.crouzet.com/pn/?i=82861009).

![DC motor](https://media.crouzet.com/catalog/_photos_low-resolution/jpg/PH_82861015.jpg)

I used an [Arduino motor shield](https://store.arduino.cc/arduino-motor-shield-rev3)
to control them.

![Arduino motor shield](https://store-cdn.arduino.cc/uni/catalog/product/cache/1/image/1000x750/f8876a31b63532bbba4e781c30024a0a/A/0/A000079_front_2.jpg)

## Claw solenoid

V1 is the voltage supplied to the claw, whose resistance R1 is about 4.5 Ω.
The claw stays closed after supplying 12 V for some milliseconds, therefore I decided
to use a dropping resistor so that push solenoid
inside the claw is enabled with less than 12 V.

![Circuit](./screenshots/claw-circuit.svg)

where

<!-- $$
V_{cc} = 12 V, R_1 = 4.5 \Omega
$$ -->

<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=V_%7Bcc%7D%20%3D%2012%20V%2C%20R_1%20%3D%204.5%20%5COmega"></div>

Below is a derivation of V1 as a function of R2.

<!-- $$
V_1 = V_{cc} - V_2
$$ -->

<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=V_1%20%3D%20V_%7Bcc%7D%20-%20V_2"></div>

<!-- $$
V_2 = I R_2
$$ -->

<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=V_2%20%3D%20I%20R_2"></div>

<!-- $$
I = \frac{V_{cc}}{R_1 + R_2}
$$ -->

<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=I%20%3D%20%5Cfrac%7BV_%7Bcc%7D%7D%7BR_1%20%2B%20R_2%7D"></div>

<!-- $$
V_2 = V_{cc} \frac{R_2}{R_1 + R_2}
$$ -->

<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=V_2%20%3D%20V_%7Bcc%7D%20%5Cfrac%7BR_2%7D%7BR_1%20%2B%20R_2%7D"></div>

<!-- $$
V_1 = V_{cc} (1 - \frac{R_2}{R_1 + R_2})
$$ -->

<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=V_1%20%3D%20V_%7Bcc%7D%20(1%20-%20%5Cfrac%7BR_2%7D%7BR_1%20%2B%20R_2%7D)"></div>

![Screenshot](./screenshots/r2.png)
[Link](https://www.desmos.com/calculator/cf1kxeozzn)

The horizontal axis is R2 (in ohms). The vertical axis is V1 (in volts).

To control the claw, I used a relay module. More specifically, I used a
[SunFounder 2-Channel DC 5V Relay Module with Optocoupler Low Level Trigger Expansion Board](https://www.sunfounder.com/products/2channel-relay-module).

![Relay module](https://cdn.shopify.com/s/files/1/0474/7729/3217/products/TS0010-01.jpg?v=1599722937)

I decided to leave the jumper between Vcc and JD-Vcc in place (i.e., the current
for the relay solenoid is supplied through the Arduino pin). Ideally, though,
this voltage would come from an external power supply (good explanation
[in this video](https://youtu.be/d9evR-K6FAY)).

## Manual control

For testing, I used the joystick that comes with the Elegoo starter kit.
It seems to be a [KY-023](https://www.cricklewoodelectronics.com/Dual-axis-joystick-module-for-Arduino-KY-023.html?gclid=Cj0KCQjwh_eFBhDZARIsALHjIKda6-hFnS6d_X1JHB1WaObJxghC3TNj5pJ42rqzo3oEvcHOkOQUueAaAp14EALw_wcB).

![Joystick](https://www.cricklewoodelectronics.com/images/D/KY023.jpg)

More info:

- [Components101.com](https://components101.com/modules/joystick-module)
- [Arduinomodules.info](https://arduinomodules.info/ky-023-joystick-dual-axis-module/)

I use the potentiometers to control the two motors, and the push button to close
the claw.

## Links of interest

### Claw cranes

- [Holland Computers, Inc. – Crane Kit Manual – Part Number RA-CRANE-KIT](https://www.hollandcomputers.com/data/Gaming/Crane%20Kit%20Manual%20RA-CRANE-KIT-2019.pdf)
- [BBTSON MICROPROCESSOR CRANE](http://ohwow-arcade.com/Assets/Game_Manuals/BIG%20CHOICE.PDF)
- [Coast to Coast Entertainment – Stage 1 Crane Controller – D9803D4 Instructions](https://coasttocoastcranes.com/Manuals/Double%20Feature%20Manual.pdf)
- [Grayhound Electronics – The Crane Operators Manual](https://www.arcade-museum.com/manuals-vending/Grayhound_Crane_Schematics.pdf)
- [Grayhound crane dip switch settings](https://www.arcade-museum.com/manuals-vending/GrayhoundSkillCrane.pdf)
- [ArcadeControls.com – "greyhound crane claw problem"](http://forum.arcadecontrols.com/index.php?topic=111859.0)
- [Hackaday.io – Toy Claw Machine](https://hackaday.io/project/215-toy-claw-machine)
- [Fixing an 80's Drew's Tiger Paw Plush Crane Claw Machine With Schematics](https://www.youtube.com/watch?v=LLF4t5Sr2Ww)
- [Arcade Claw Machine/ Prize Game with Arduino](http://www.retrobuiltgames.com/the-build-page/arduino-claw-machine/)
- [Powering a crane/claw](https://electronics.stackexchange.com/questions/471259/powering-a-crane-claw)
- [Claw machines are rigged — here's why it's so hard to grab that stuffed animal](https://www.vox.com/2015/4/3/8339999/claw-machines-rigged)
- [Arduino Claw Machine](https://www.instructables.com/Arduino-Claw-Machine/)

### Arduino

- [DroneBot Workshop](https://www.youtube.com/channel/UCzml9bXoEM0itbcE96CB03w)
- [Paul McWhorter](https://www.youtube.com/channel/UCfYfK0tzHZTpNFrc_NDKfTA)
- [Robojax](https://www.youtube.com/channel/UCkcBSig_Iu4ZnAIeCeG1TVg)
- [Library tutorial](https://www.arduino.cc/en/Hacking/libraryTutorial)
- [Adafruit-BMP085-Library](https://github.com/adafruit/Adafruit-BMP085-Library)
- [API style guide](https://www.arduino.cc/en/Reference/APIStyleGuide)
