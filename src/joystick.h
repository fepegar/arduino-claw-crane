#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"
#include "motor.h"

class Joystick {
  public:
    Joystick(int pinX, int pinY);
    int readX();
    int readY();

  private:
    int _pinX;
    int _pinY;
    int _read(int pin);
};

#endif
