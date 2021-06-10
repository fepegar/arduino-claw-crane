#ifndef joystick_h
#define joystick_h

#include "Arduino.h"


class Joystick {
  public:
    Joystick(int pinX, int pinY, int pinPush);
    float readX();
    float readY();
    boolean readButton();

  private:
    int _pinX;
    int _pinY;
    int _pinPush;
    float _readAnalog(int pin);
};

#endif
