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

  _moving = false;
  _timeToMove = millis() + _getRandomStopInterval();
  Serial.print("Time to move: ");
  Serial.println(_timeToMove);

  _speed = 0;
}

void Motor::stop() {
  _enableBrake();
  _setSpeed(0);
}

void Motor::moveAuto() {
  if (_speed != 0) {
    boolean mustStop = millis() >= _timeToStop;
    boolean limitReached = _getLimitSwitchFromSpeed(_speed)->isPushed();
    if (mustStop || limitReached) {
      Serial.println("Time to stop: " + String(mustStop));
      Serial.println("Limit reached: " + String(limitReached));
      Serial.println("Current speed: " + String(_speed));
      stop();
      unsigned long waitingTime = _getRandomStopInterval();
      _timeToMove = millis() + waitingTime;
      Serial.println("Stopping " + String(_motorID) + " for " + String(waitingTime));
    }
  } else if ((_speed == 0) && (millis() >= _timeToMove)) {
    float speed = _getRandomSpeed();
    Serial.println("Setting new speed: " + String(speed));
    _setSpeed(speed);
    unsigned long movingTime = _getRandomMoveInterval();
    _timeToStop = millis() + movingTime;
    Serial.println("Moving " + String(_motorID) + " at speed " + String(speed) + " for " + String(movingTime));
  }
}

float Motor::getMilliAmps() {
  float voltage = _getVoltageFromPin();
  return _getCurrentFromVoltage(voltage);
}

void Motor::setSpeed(float speed) {
  if (speed == 0) {
    _setSpeed(0);
    return;
  }
  LimitSwitch* limitSwitch = _getLimitSwitchFromSpeed(speed);
  if (limitSwitch->isPushed()) {
    Serial.println("Cannot set speed " + String(speed) + " as limit switch is pushed");
    _setSpeed(0);
  } else {
    Serial.println("Setting speed: " + String(speed));
    _setSpeed(speed);
  }
}

void Motor::_setSpeed(float speed) {
  _speed = speed;
  // Speed should be in [-1, 1]
  if (speed == 0) {
    _enableBrake();
  } else {
    _disableBrake();
    if (speed < 0) {
      speed *= -1;
      _setDirection(-1);
    } else {
      _setDirection(1);
    }
  }
  analogWrite(_pwmPin, _speedToByte(speed));
}

LimitSwitch* Motor::_getLimitSwitchFromSpeed(float speed) {
  LimitSwitch* limitSwitch;
  if (speed < 0) {
    limitSwitch = _ptrLimitSwitch0;
  } else if (speed > 0) {
    limitSwitch = _ptrLimitSwitch1;
  } else {
    limitSwitch = nullptr;
  }
  return limitSwitch;
}

void Motor::_enableBrake() {
  digitalWrite(_brakePin, HIGH);
}

void Motor::_disableBrake() {
  digitalWrite(_brakePin, LOW);
}

void Motor::_setDirection(int direction) {
  if (direction == -1) {
    digitalWrite(_directionPin, LOW);
  } else if (direction == 1) {
    digitalWrite(_directionPin, HIGH);
  }
}

int Motor::_speedToByte(float speed)
{
  float rescaled = 255 * speed;
  return (int) rescaled;
}

float Motor::_getVoltageFromPin() {
  int lecture = analogRead(_currentPin);
  float voltage = (float)(lecture) / MAX_10_BITS * MAX_INPUT_VOLTAGE;
  return voltage;
}

float Motor::_getCurrentFromVoltage(float voltage) {
  float current = voltage / VOLTAGE_AT_MAX_CURRENT * CURRENT_AT_MAX_VOLTAGE;
  return current;
}

float Motor::_getRandomSpeed() {
  float x, m, n, y;
  x = _getRandomFloat();
  m = MAX_RANDOM_SPEED - MIN_RANDOM_SPEED;
  n = MIN_RANDOM_SPEED;
  y = m * x + MIN_RANDOM_SPEED;
  if (random(2) == 0) {
    y *= -1;
  }
  if (y < 0 && _ptrLimitSwitch0->isPushed()) {
    Serial.println("Flipping speed as switch 0 is enabled");
    y *= -1;
  } else if (y > 0 && _ptrLimitSwitch1->isPushed()) {
    Serial.println("Flipping speed as switch 1 is enabled");
    y *= -1;
  }
  return y;
}

float Motor::_getRandomFloat() {
  return random(0, 100000) / 100000.0;
}

unsigned long Motor::_getRandomStopInterval() {
  return random(MIN_STOP_INTERVAL, MAX_STOP_INTERVAL);
}

unsigned long Motor::_getRandomMoveInterval() {
  return random(MIN_MOVE_INTERVAL, MAX_MOVE_INTERVAL);
}
