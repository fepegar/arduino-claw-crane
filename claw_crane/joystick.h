#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"


class Joystick {
  public:
    Joystick(int pinX, int pinY, int pinPush);
    int readX();
    int readY();
    boolean readButton();

  private:
    int _pinX;
    int _pinY;
    int _pinPush;
    int _readAnalog(int pin);
};

#endif
