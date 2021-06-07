#include "Arduino.h"
#include "remote.h"

#include <IRremote.h>

Remote::Remote(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
  IRrecv _irrecv(pin);
  decode_results _results;
}

void Remote::init() {
  _irrecv->enableIRIn();
}

boolean Remote::decode() {
  return _irrecv->decode(_results);
}

int Remote::getResultsValue() {
  return _results->value;
}

decode_type_t Remote::getResultsDecodeType() {
  return _results->decode_type;
}

void Remote::resume() {
  _irrecv->resume();
}
