/*

- Joystick VRx, VRy and SW to A3, A4, TODO.

Arduino:
- Pin 4 to pull-up resistor 10k to white (xLimit1)
- Pin 5 to pull-up resistor 10k to red (xLimit0)
- Pin 6 to pull-up resistor 10k to purple (yLimitDown)
- Pin 7 to pull-up resistor 10k to orange (yLimitUp)

*/

#include "motor.h"
#include "joystick.h"

#define TO_MOTORS 0
#define FROM_MOTORS 1
#define DOWN 0
#define UP 1

const int xLimitPin0 = 4;
const int xLimitPin1 = 5;

const int yLimitPinDown = 6;
const int yLimitPinUp = 7;

const int joystickPinX = A3;
const int joystickPinY = A4;

Motor motorX(
  ConstantsMotorA::directionPin,
  ConstantsMotorA::pwmPin,
  ConstantsMotorA::brakePin,
  ConstantsMotorA::currentPin,
  xLimitPin0,
  xLimitPin1
);

Motor motorY(
  ConstantsMotorB::directionPin,
  ConstantsMotorB::pwmPin,
  ConstantsMotorB::brakePin,
  ConstantsMotorB::currentPin,
  yLimitPinDown,
  yLimitPinUp
);

Joystick joystick(motorX, motorY, joystickPinX, joystickPinY);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

boolean success;

void loop() {
  joystick.readAndMove();
}


void stopAll() {
  motorX.stop();
  motorY.stop();
}
