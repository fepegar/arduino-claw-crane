# The Claw Crane

Collaboration with artist [Estefanía B. Flores](https://www.instagram.com/estefantastic) for her master's thesis at
[Goldsmiths, University of London](https://www.gold.ac.uk/).

Old claw crane controlled with an [Arduino UNO](https://store.arduino.cc/arduino-uno-rev3) microcontroller board.

![Schematic](breadboard.png)

## Claw solenoid

V1 is the voltage supplied to the claw, whose resistance R1 is about 4.5 Ω.
The claw stays closed after supplying 12 V for some milliseconds, so I decided
to use a resistor in series so less than 12 V are provided to the push solenoid
inside the claw.

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

<!-- ![Screenshot](./screenshots/claw-simulation.png)
[Link](https://crcit.net/c/800fdfb51e4041a59e4ed74fbcc340c6) -->

<!-- A value of  Ω for R2 implies V1 =  V, which seems reasonable. -->

## Links of interest

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
- [Adafruit-BMP085-Library](https://github.com/adafruit/Adafruit-BMP085-Library)
