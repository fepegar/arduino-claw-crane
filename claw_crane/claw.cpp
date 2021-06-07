#include "Arduino.h"
#include "claw.h"


Claw::Claw(int pin) {
  digitalWrite(pin, HIGH);  // https://youtu.be/d9evR-K6FAY?t=680
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Claw::setEnabled(boolean enabled) {
  if (enabled) {
    digitalWrite(_pin, LOW);
  } else {
    digitalWrite(_pin, HIGH);
  }
}
