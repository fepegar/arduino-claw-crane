#include "Arduino.h"
#include "motor.h"


Motor::Motor(int directionPin, int pwmPin, int brakePin, int currentPin, int limitPin0, int limitPin1)
{
  pinMode(directionPin, OUTPUT);
  _directionPin = directionPin;

  pinMode(pwmPin, OUTPUT);
  _pwmPin = pwmPin;

  pinMode(brakePin, OUTPUT);
  _brakePin = brakePin;

  pinMode(currentPin, INPUT);
  _currentPin = currentPin;

  pinMode(limitPin0, INPUT);
  _limitPin0 = limitPin0;

  pinMode(limitPin1, INPUT);
  _limitPin1 = limitPin1;

  _delayTime = 50;  // ms
}

boolean Motor::move(int direction, float speed)
{
  if (limitSwitchIsPushed(direction) || direction == 0) {
    stop();
    return false;
  }
  setBrakeEnabled(false);
  setDirection(direction);
  setSpeed(speedToByte(speed));
  return true;
}

void Motor::stop()
{
  setSpeed(0);
  setBrakeEnabled(true);
}

void Motor::setBrakeEnabled(boolean enable)
{
  if (enable) {
    digitalWrite(_brakePin, HIGH);
  } else {
    digitalWrite(_brakePin, LOW);
  }
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
  // Limit switches are connected using pull-up resistors
  boolean result;
  if (direction == -1) {
    result = digitalRead(_limitPin0) == LOW;
  } else if (direction == 1) {
    result = digitalRead(_limitPin1) == LOW;
  }
  delay(_delayTime);  // account for bouncing
  return result;
}

void Motor::setSpeed(int speed) {
  analogWrite(_pwmPin, speedToByte(speed));
}

float Motor::getMilliAmps(int current) {
  float voltage = getVoltageFromPin();
  return getCurrentFromVoltage(voltage);
}

float Motor::getVoltageFromPin() {
  int lecture = analogRead(_currentPin);
  float voltage = (float)(lecture) / 1023 * 5;
  return voltage;
}

float Motor::getCurrentFromVoltage(float voltage) {
  // Docs say 3.3 V for 2 A
  float current = voltage / 3.3 * 2;
  return current;
}
