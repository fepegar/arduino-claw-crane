/*

  Joystick:
  - VRx to A3
  - VRy to A4
  - SW to 10

  Infrared receiver:
  - Y to 2

  Crane:
  - Motor x: orange-white, green
  - Pin 4 to pull-up resistor 10k to red (xLimit0)
  - Pin 5 to pull-up resistor 10k to white (xLimit1)

  - Motor y: orange-black, pink
  - Pin 6 to pull-up resistor 10k to purple (yLimitDown)
  - Pin 7 to pull-up resistor 10k to orange (yLimitUp)

*/

#include "motor.h"
#include "joystick.h"
#include "claw.h"
#include <IRremote.h>

#define MANUAL 0
#define AUTO 1

const int mode = MANUAL;

const int xLimitPin0 = 4;
const int xLimitPin1 = 5;

const int yLimitPinDown = 6;
const int yLimitPinUp = 7;

const int joystickPinX = A3;
const int joystickPinY = A4;
const int joystickPinPush = A5;

const int clawPin = 10;

Motor motorX(
  'X',
  ConstantsMotorB::directionPin,
  ConstantsMotorB::pwmPin,
  ConstantsMotorB::brakePin,
  ConstantsMotorB::currentPin,
  xLimitPin0,
  xLimitPin1
);

Motor motorY(
  'Y',
  ConstantsMotorA::directionPin,
  ConstantsMotorA::pwmPin,
  ConstantsMotorA::brakePin,
  ConstantsMotorA::currentPin,
  yLimitPinDown,
  yLimitPinUp
);

Joystick joystick(joystickPinX, joystickPinY, joystickPinPush);

Claw claw(clawPin);

float speedX;
float speedY;
boolean buttonPressed = false;


void setup() {
  Serial.begin(9600);
}

void loop() {
  int timeClaw = 5000;
  if (mode == AUTO) {
    motorX.moveAuto();
    motorY.moveAuto();
    claw.moveAuto();
  } else if (mode == MANUAL) {
    readJoystick();
    update();
  }
}


void readJoystick() {
  speedX = joystick.readX();
  speedY = joystick.readY();
  buttonPressed = joystick.readButton();
}


void update() {
  Serial.println(speedX);
  motorX.setSpeed(speedX);
  motorY.setSpeed(speedY);
  claw.setEnabled(buttonPressed);
}


void stopAll() {
  motorX.stop();
  motorY.stop();
  claw.release();
}
