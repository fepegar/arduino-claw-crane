#include "Arduino.h"
#include "motor.h"
#include "joystick.h"


Joystick::Joystick(int pinX, int pinY) {
  pinMode(pinX, INPUT);
  _pinX = pinX;

  pinMode(pinY, INPUT);
  _pinY = pinY;
};

int Joystick::readX() {
  return _read(_pinX);
}

int Joystick::readY() {
  return _read(_pinY);
}

int Joystick::_read(int pin) {
  // Speed is binary for the moment (all or nothing)
  const int midSignal = 1024 / 2;
  int signal = analogRead(pin);
  int direction;
  if (signal > 400 && signal < 600) {
    direction = 0;
  } else {
    if (signal > midSignal) {
      direction = 1;
    } else if (signal < midSignal) {
      direction = -1;
    }
  }
  return direction;
}
