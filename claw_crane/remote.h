#include "Arduino.h"

#include <IRremote.h>


class Remote {
  public:
    Remote(int pin);
    boolean decode();
    void init();
    int getResultsValue();
    decode_type_t getResultsDecodeType();
    void resume();

  private:
    int _pin;
    IRrecv* _irrecv;
    decode_results* _results;
};
