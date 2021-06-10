#include "Arduino.h"
#include "debounce.h"


boolean debounce(boolean reading, boolean * ptrLastState, unsigned long * ptrLastDebounceTime, boolean debouncedState) {
  // Adapted from https://www.arduino.cc/en/Tutorial/BuiltInExamples/Debounce
  if (reading != *ptrLastState) {
    // Reset the debouncing timer
    *ptrLastDebounceTime = millis();
  }
  unsigned long timeSinceLastChange = millis() - *ptrLastDebounceTime;
  if (timeSinceLastChange > DELAY_TIME) {
    if (reading != debouncedState) {
      debouncedState = reading;
    }
  }
  *ptrLastState = reading;
  return debouncedState;
}
