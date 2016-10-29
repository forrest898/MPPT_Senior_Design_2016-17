#include <LiquidCrystal.h>
#include <SPI.h>
#include "adc.hpp"
#include "lcd.hpp"
#include "pwm.hpp"

#define RELAY 16 // Relay

LiquidCrystal lcd(8, 7, 3, 4 ,5 ,6);

float V_REF = 4.69;

void setup() {
  lcd_init();
  PWM_init();
  adc_init();

  set_PWM_frequency(50000);
  set_PWM_duty(.5);
}


void loop() {
  int i,v;
  float readval;

  for (i=0; i< 100; i++){
    set_PWM_duty(i/100.0);
    readval = read_adc(0);
    lcd.clear();
    lcd.print(readval, 4);
    delay(500);
  }

}

