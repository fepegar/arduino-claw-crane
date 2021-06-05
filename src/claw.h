#ifndef Claw_h
#define Claw_h

#include "Arduino.h"

class Claw {
  public:
    Claw(int pin);
    void setEnabled(boolean enabled);

  private:
    int _pin;
};

#endif
