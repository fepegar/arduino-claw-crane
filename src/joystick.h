#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"
#include "motor.h"

class Joystick {
  public:
    Joystick(Motor motorX, Motor motorY, int pinX, int pinY);
    void readAndMove();

  private:
    Motor _motorX;
    Motor _motorY;
    int _pinX;
    int _pinY;
    void moveX();
    void moveY();
    boolean _move(int pin, Motor motor, float speed);
};

#endif
