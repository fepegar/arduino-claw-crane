#ifndef motor_h
#define motor_h

#include "Arduino.h"
#include "limit.h"

#define VERBOSE 1

// Docs say 3.3 V for 2 A
#define CURRENT_AT_MAX_VOLTAGE 2
#define VOLTAGE_AT_MAX_CURRENT 3.3

#define MAX_10_BITS 1023
#define MAX_INPUT_VOLTAGE 5

#define MIN_RANDOM_SPEED 0.5
#define MAX_RANDOM_SPEED 1

#define MIN_STOP_INTERVAL 2000  // 2 s
#define MAX_STOP_INTERVAL 10000  // 10 s

#define MIN_MOVE_INTERVAL 500  // 0.2 s
#define MAX_MOVE_INTERVAL 2000 // 2 s


class Motor {
  public:
    Motor(char motorID, int directionPin, int pwmPin, int brakePin, int currentPin, int limitPin0, int limitPin1);
    void setSpeed(float speed);
    void stop();
    float getMilliAmps();
    boolean limitSwitchIsPushed(int direction);
    void moveAuto();
    boolean _limitReached();

  private:
    char _motorID;
    int _pwmPin;
    int _directionPin;
    int _brakePin;
    int _currentPin;
    int _delayTime;
    float _speed;
    void _setSpeed(float speed);
    void _setDirection(int direction);
    int _speedToByte(float speed);
    void _enableBrake();
    void _disableBrake();
    float _getVoltageFromPin();
    float _getCurrentFromVoltage(float voltage);
    int _getCurrentDirection();
    LimitSwitch* _getLimitSwitchFromSpeed(float speed);
    LimitSwitch* _getRelevantLimitSwitch();
    float _getRandomSpeed();
    float _getRandomFloat();
    unsigned long _getRandomStopInterval();
    unsigned long _getRandomMoveInterval();
    unsigned long _timeToMove;
    unsigned long _timeToStop;
    boolean _moving;
    LimitSwitch* _ptrLimitSwitch0;
    LimitSwitch* _ptrLimitSwitch1;
};


namespace ConstantsMotorA
{
  const int directionPin = 12;
  const int pwmPin = 3;
  const int brakePin = 9;
  const int currentPin = A0;
}


namespace ConstantsMotorB
{
  const int directionPin = 13;
  const int pwmPin = 11;
  const int brakePin = 8;
  const int currentPin = A1;
}

#endif
