#ifndef limit_h
#define limit_h

#include "Arduino.h"


class LimitSwitch {
  public:
    LimitSwitch(int pin);
    boolean isPushed();
    boolean _isPushed();
    void begin();

  private:
    int _pin;
    boolean _lastState;
    boolean _debouncedState;
    unsigned long _lastDebounceTime;
};

#endif
