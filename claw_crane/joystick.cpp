#include "Arduino.h"
#include "joystick.h"


Joystick::Joystick(int pinX, int pinY, int pinPush) {
  pinMode(pinX, INPUT);
  _pinX = pinX;

  pinMode(pinY, INPUT);
  _pinY = pinY;

  pinMode(pinPush, INPUT_PULLUP);
  _pinPush = pinPush;
}

int Joystick::readX() {
  return _readAnalog(_pinX);
}

int Joystick::readY() {
  return _readAnalog(_pinY);
}

boolean Joystick::readButton() {
  return digitalRead(_pinPush) == LOW;  // pull-up
}

int Joystick::_readAnalog(int pin) {
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
