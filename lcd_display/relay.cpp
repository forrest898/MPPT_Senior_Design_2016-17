#include "Arduino.h"
#include "relay.hpp"

#define RELAY A0
int state = 0;

void relay_init(void){
  pinMode(RELAY, OUTPUT);
}

void relay_off(void){
  digitalWrite(RELAY, LOW);
  state = 0;
}

void relay_on(void){
  digitalWrite(RELAY, HIGH);
  state = 1;
}

void relay_toggle(void){
  if(state) relay_off();
  else relay_on();
}

