#include "pwm.hpp"

void setup() {
  PWM_init();
  set_PWM_frequency(50000);
  set_PWM_duty(50);
}

void loop() {
  
}
