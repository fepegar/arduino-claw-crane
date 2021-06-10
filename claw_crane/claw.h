#ifndef claw_h
#define claw_h

#include "Arduino.h"

#define MIN_TIME_OPEN 10000  // 10 s
#define MAX_TIME_OPEN 30000  // 30 s
#define MAX_CLOSED_TIME 50  // ms


class Claw {
  public:
    Claw(int pin);
    void close();
    void release();
    void setEnabled(boolean enabled);
    void moveAuto();

  private:
    int _pin;
    boolean _isOpen;
    unsigned long _timeToClose;
    unsigned long _timeWhenClosed;
    unsigned long _getRandomTimeOpen();
};

#endif
