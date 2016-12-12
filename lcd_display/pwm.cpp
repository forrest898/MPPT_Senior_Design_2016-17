#include "Arduino.h"
#include "pwm.hpp"

#define left_button A3
#define enter_button A2
#define right_button A1

//Initializes PWM on pin 9, fast pwm mode
void PWM_init(void){
  DDRB |= (1 << DDB1) | (1 << DDB2);

  TCCR1A =
      (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);

  TCCR1B =
      (1 << WGM12) | (1 << WGM13) | (1 << CS10);
  OCR1A = 0;
}

//Sets the frequency of the PWM
void set_PWM_frequency(float frequency){
   int freq;
   freq = int(16000000.0 / frequency);
   ICR1 = freq;
}

void set_PWM_duty_p9(float duty){
  int percent;
  percent = int(duty * ICR1);
  OCR1A = percent;
}

void set_PWM_duty_p10(float duty){
  int percent;
  percent = int(duty * ICR1);
  OCR1B = percent;
}



