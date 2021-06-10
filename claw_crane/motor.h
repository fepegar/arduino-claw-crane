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

class Motor {
  public:
    Motor(char motorID, int directionPin, int pwmPin, int brakePin, int currentPin, int limitPin0, int limitPin1);
    boolean update(int direction, float speed);
    void stop();
    float getMilliAmps();
    boolean limitSwitchIsPushed(int direction);

  private:
    char _motorID;
    int _pwmPin;
    int _directionPin;
    int _brakePin;
    int _currentPin;
    int _delayTime;
    void setDirection(int direction);
    int speedToByte(float speed);
    void setSpeed(float speed);
    void enableBrake();
    void disableBrake();
    float getMilliAmps(int current);
    float getVoltageFromPin();
    float getCurrentFromVoltage(float voltage);
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
