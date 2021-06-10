#include "Arduino.h"
#include "motor.h"
#include "limit.h"


Motor::Motor(char motorID, int directionPin, int pwmPin, int brakePin, int currentPin, int limitPin0, int limitPin1)
{
  _motorID = motorID;

  pinMode(directionPin, OUTPUT);
  _directionPin = directionPin;

  pinMode(pwmPin, OUTPUT);
  _pwmPin = pwmPin;

  pinMode(brakePin, OUTPUT);
  _brakePin = brakePin;

  pinMode(currentPin, INPUT);
  _currentPin = currentPin;

  _ptrLimitSwitch0 = new LimitSwitch(limitPin0);
  _ptrLimitSwitch1 = new LimitSwitch(limitPin1);
  _ptrLimitSwitch0->begin();
  _ptrLimitSwitch1->begin();
}


boolean Motor::update(int direction, float speed) {
  if (direction == 0 || limitSwitchIsPushed(direction)) {
    stop();
  } else {
    setDirection(direction);
    setSpeed(speed);
  }
}

void Motor::stop() {
  enableBrake();
  setSpeed(0);
}

void Motor::enableBrake() {
  digitalWrite(_brakePin, HIGH);
}

void Motor::disableBrake() {
  digitalWrite(_brakePin, LOW);
}

void Motor::setDirection(int direction) {
  if (direction == -1) {
    digitalWrite(_directionPin, LOW);
  } else if (direction == 1) {
    digitalWrite(_directionPin, HIGH);
  }
}

int Motor::speedToByte(float speed)
{
  float rescaled = 255 * speed;
  return (int) rescaled;
}

boolean Motor::limitSwitchIsPushed(int direction)
{
  // Limit switches are connected using pull-up resistors,
  // which means that the signal is LOW when they are enabled
  boolean isPushed;
  if (direction == -1) {
    isPushed = _ptrLimitSwitch0->isPushed();
  } else if (direction == 1) {
    isPushed = _ptrLimitSwitch1->isPushed();
  }
  if (isPushed && VERBOSE) {
    Serial.print("Limit ");
    Serial.print(direction);
    Serial.print(" of motor ");
    Serial.print((String)(_motorID));
    Serial.println(" ON");
  }
  return isPushed;
}

void Motor::setSpeed(float speed) {
  // Speed should be in [0, 1]
  if (speed == 0) {
    enableBrake();
  } else {
    disableBrake();
  }
  analogWrite(_pwmPin, speedToByte(speed));
}

float Motor::getMilliAmps() {
  float voltage = getVoltageFromPin();
  return getCurrentFromVoltage(voltage);
}

float Motor::getVoltageFromPin() {
  int lecture = analogRead(_currentPin);
  float voltage = (float)(lecture) / MAX_10_BITS * MAX_INPUT_VOLTAGE;
  return voltage;
}

float Motor::getCurrentFromVoltage(float voltage) {
  float current = voltage / VOLTAGE_AT_MAX_CURRENT * CURRENT_AT_MAX_VOLTAGE;
  return current;
}
