/*

Joystick:
- VRx to A3
- VRy to A4
- SW to [TODO]

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

#define TO_MOTORS -1
#define FROM_MOTORS 1
#define DOWN -1
#define UP 1

const int xLimitPin0 = 4;
const int xLimitPin1 = 5;

const int yLimitPinDown = 6;
const int yLimitPinUp = 7;

const int joystickPinX = A3;
const int joystickPinY = A4;
const int joystickPinPush = A5;

const int clawPin = 10;

Motor motorX(
  'B',
  ConstantsMotorB::directionPin,
  ConstantsMotorB::pwmPin,
  ConstantsMotorB::brakePin,
  ConstantsMotorB::currentPin,
  xLimitPin0,
  xLimitPin1
);

Motor motorY(
  'A',
  ConstantsMotorA::directionPin,
  ConstantsMotorA::pwmPin,
  ConstantsMotorA::brakePin,
  ConstantsMotorA::currentPin,
  yLimitPinDown,
  yLimitPinUp
);

Joystick joystick(joystickPinX, joystickPinY, joystickPinPush);

Claw claw(clawPin);


int directionX;
int directionY;
boolean buttonPressed;


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Read
  directionX = joystick.readX();
  directionY = joystick.readY();
  buttonPressed = joystick.readButton();

  // Move
  motorX.move(directionX, 1);
  motorY.move(directionY, 1);
  claw.setEnabled(buttonPressed);
}


void stopAll() {
  motorX.stop();
  motorY.stop();
  claw.setEnabled(false);
}
