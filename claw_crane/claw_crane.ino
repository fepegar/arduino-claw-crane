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

#define TO_MOTORS -1
#define FROM_MOTORS 1
#define DOWN -1
#define UP 1
#define STOP 0

#define REMOTE_UP 0x18
#define REMOTE_LEFT 0x8
#define REMOTE_CENTER 0x1C
#define REMOTE_RIGHT 0x5A
#define REMOTE_DOWN 0x52

const int xLimitPin0 = 4;
const int xLimitPin1 = 5;

const int yLimitPinDown = 6;
const int yLimitPinUp = 7;

const int joystickPinX = A3;
const int joystickPinY = A4;
const int joystickPinPush = A5;

const int clawPin = 10;

const int remotePin = 2;

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
  motorX.moveAuto();
  motorY.moveAuto();
  //readJoystick();
  //update();
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
  claw.setEnabled(false);
}
