#include "Arduino.h"
#include "motor.h"
#include "joystick.h"


Joystick::Joystick(Motor motorX, Motor motorY, int pinX, int pinY) {
  _motorX = motorX;
  _motorY = motorY;

  pinMode(pinX, INPUT);
  _pinX = pinX;

  pinMode(pinY, INPUT);
  _pinY = pinY;
};

void readAndMove() {
  moveX();
  moveY();
}

void moveX() {
  const float speed = 0.5;
  _move(_pinX, _motorX, speed);
}

void moveY() {
  const float speed = 1;
  _move(_pinY, _motorY, speed);
}

boolean _move(int pin, Motor motor, float speed) {
  // Speed is binary for the moment (all or nothing)
  const int midSignal = 1024 / 2;
  int signal = analogRead(pin);
  if (signal > 400 && signal < 600) {
    motor.stop();
    return false;
  } else {
    int direction;
    if (signal > midSignal) {
      direction = 0;
    } else if (signal < midSignal) {
      direction = 1;
    }
    motor.move(direction, speed);
    return true;
  }
}
