#include "Arduino.h"
#include "limit.h"
#include "debounce.h"


LimitSwitch::LimitSwitch(char switchID, int pin) {
  this->switchID = switchID;
  pinMode(pin, INPUT_PULLUP);
  _pin = pin;
}


void LimitSwitch::begin() {
  _lastState = _isPushed();
  _debouncedState = _lastState;
  _lastDebounceTime = 0;
}


boolean LimitSwitch::isPushed() {
  boolean currentState = _isPushed();
  _debouncedState = debounce(
    currentState,
    &_lastState,
    &_lastDebounceTime,
    _debouncedState
  );
  if (_debouncedState == true) {
    Serial.println("Limit switch enabled");
  }
  return _debouncedState;
}


boolean LimitSwitch::_isPushed() {
  // Get actual current state
  return digitalRead(_pin) == LOW;
}
