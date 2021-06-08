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

const int useRemote = false;

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

int directionX = STOP;
int directionY = STOP;
boolean buttonPressed = false;
boolean closeClaw = false;


void setup() {
  Serial.begin(9600);
  if (useRemote) {
    IrReceiver.begin(remotePin, false);
  }
}

void loop() {
  read();
  move();
}


void read() {
  if (useRemote) {
    readRemote();
  } else {
    readJoystick();
  }
}


void readJoystick() {
  directionX = joystick.readX();
  directionY = joystick.readY();
  buttonPressed = joystick.readButton();
  closeClaw = buttonPressed;
}


void readRemote() {
  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    Serial.println();
    IrReceiver.printIRResultMinimal(&Serial);
    Serial.println();
    IrReceiver.resume();

    switch (IrReceiver.decodedIRData.command) {
      case REMOTE_UP:
        Serial.println("Remote up");
        directionY = 1;
        break;
      case REMOTE_DOWN:
        Serial.println("Remote down");
        directionY = -1;
        break;
      case REMOTE_LEFT:
        Serial.println("Remote left");
        directionX = 1;
        break;
      case REMOTE_RIGHT:
        Serial.println("Remote right");
        directionX = -1;
        break;
      case REMOTE_CENTER:
        Serial.println("Remote center");
        closeClaw = true;
        break;
      default:
        Serial.println("Remote something else");
        directionX = 0;
        directionY = 0;
        closeClaw = false;
    }
  } else {
    directionX = 0;
    directionY = 0;
    closeClaw = false;
  }
}


void move() {
  motorX.move(directionX, 0.5);
  motorY.move(directionY, 0.99);
  claw.setEnabled(closeClaw);
}


void stopAll() {
  motorX.stop();
  motorY.stop();
  claw.setEnabled(false);
}
