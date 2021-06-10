#ifndef debounce_h
#define debounce_h

#include "Arduino.h"

#define DELAY_TIME 50  // ms


boolean debounce(boolean reading, boolean * ptrLastState, unsigned long * ptrLastDebounceTime, boolean debouncedState);

#endif
