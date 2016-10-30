#include "pwm.hpp"

void setup() {
  PWM_init();
  set_PWM_frequency(50000);
  set_PWM_duty(.50);
  Serial.begin(9600);
  delay(5000);
}

void loop() {
  float i;
  for (i =10; i < 55; i++){
    set_PWM_duty(i/100.0);
    Serial.println(i/100.0);
    delay(100);
  }
}
