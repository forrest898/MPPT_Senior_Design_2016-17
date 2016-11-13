#include "Arduino.h"
#include "relay.hpp"

#define RELAY A1

void relay_init(void){
  pinMode(RELAY, OUTPUT);
}

void relay_off(void){
  digitalWrite(RELAY, LOW);
}

void relay_on(void){
  digitalWrite(RELAY, HIGH);
}

