#ifndef Motor_h
#define Motor_h

#include "Arduino.h"


class Motor {
  public:
    Motor(int directionPin, int pwmPin, int brakePin, int currentPin, int limitPin0, int limitPin1);
    boolean move(int direction, float speed);
    void stop();
    float getMilliAmps();

  private:
    int _pwmPin;
    int _directionPin;
    int _brakePin;
    int _currentPin;
    int _limitPin0;
    int _limitPin1;
    int _delayTime;
    boolean limitSwitchIsPushed(int direction);
    void setDirection(int direction);
    int speedToByte(float speed);
    void pwmWrite(int speed);
    void setBrakeEnabled(boolean enable);
    float getMilliAmps(int current);
    float getVoltageFromPin();
    float getCurrentFromVoltage(float voltage);
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
