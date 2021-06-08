#include "Arduino.h"
#include "motor.h"


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

  pinMode(limitPin0, INPUT_PULLUP);
  _limitPin0 = limitPin0;

  pinMode(limitPin1, INPUT_PULLUP);
  _limitPin1 = limitPin1;

  _delayTime = 50;  // ms
}

boolean Motor::move(int direction, float speed)
{
  boolean moved;
  if (direction == 0 || limitSwitchIsPushed(direction)) {
    stop();
    moved = false;
  } else {
    setBrakeEnabled(false);
    setDirection(direction);
    setSpeed(speed);
    moved = true;
  }
  return moved;
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
  // Limit switches are connected using pull-up resistors,
  // which means that the signal is LOW when they are enabled
  boolean isPushed;
  boolean verbose = true;
  int pin;
  if (direction == -1) {
    pin = _limitPin0;
  } else if (direction == 1) {
    pin = _limitPin1;
  }
  isPushed = digitalRead(pin) == LOW;
  delay(_delayTime);  // account for bouncing
  if (isPushed && verbose) {
    Serial.print("Limit ");
    Serial.print(direction);
    Serial.print(" of motor ");
    Serial.print((String)(_motorID));
    Serial.print(" (pin ");
    Serial.print(pin);
    Serial.println(") ON");
  }
  return isPushed;
}

void Motor::setSpeed(float speed) {
  // Speed should be in [0, 1]
  analogWrite(_pwmPin, speedToByte(speed));
}

float Motor::getMilliAmps() {
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
