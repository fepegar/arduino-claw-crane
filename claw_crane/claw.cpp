#include "Arduino.h"
#include "claw.h"


Claw::Claw(int pin) {
  digitalWrite(pin, HIGH);  // https://youtu.be/d9evR-K6FAY?t=680
  pinMode(pin, OUTPUT);
  _pin = pin;
  _isOpen = true;
  _timeToClose = millis() + _getRandomTimeOpen();
}

void Claw::close() {
  Serial.println("Closing claw");
  setEnabled(true);
  _isOpen = false;
}

void Claw::release() {
  Serial.println("Releasing claw\n");
  setEnabled(false);
  _isOpen = true;
}

void Claw::setEnabled(boolean enabled) {
  if (enabled) {
    digitalWrite(_pin, LOW);
  } else {
    digitalWrite(_pin, HIGH);
  }
}

void Claw::moveAuto() {
  if (_isOpen) {
    if (millis() > _timeToClose) {
      close();
      _timeWhenClosed = millis();
    }
  } else {
    if ((millis() - _timeWhenClosed) > MAX_CLOSED_TIME) {
      release();
      _timeToClose = millis() + _getRandomTimeOpen();
    }
  }
}


unsigned long Claw::_getRandomTimeOpen() {
  return random(MIN_TIME_OPEN, MAX_TIME_OPEN);
}
