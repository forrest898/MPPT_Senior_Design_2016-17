#include <LiquidCrystal.h>
#include <SPI.h>
#include "C:\Users\Forrest\Documents\402\code\MPPT_Senior_Design_2016-17\lcd_display\adc.hpp"
#include "C:\Users\Forrest\Documents\402\code\MPPT_Senior_Design_2016-17\lcd_display\pwm.hpp"
#include "C:\Users\Forrest\Documents\402\code\MPPT_Senior_Design_2016-17\lcd_display\power_sensing.hpp"
#include "C:\Users\Forrest\Documents\402\code\MPPT_Senior_Design_2016-17\lcd_display\lcd.hpp"

LiquidCrystal lcd(8,7,2,4,5,6);

float V_REF = 5.02;
float gain = 3.43;
float readval;

void setup() {
  lcd_init();
  adc_init();
  //pinMode(3, INPUT);
  
  pinMode(3, OUTPUT);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  
  OCR2B = 175;
  
}

void loop() {

  readval =  read_voltage(0, gain);
  lcd.clear();
  lcd.print(readval, 2);
  delay(50);
  /*
  for(int i=0; i<200; i++) {
    OCR2B += 1;
    readval =  read_voltage(0, gain);
    lcd.clear();
    lcd.print(readval, 2);
    delay(20);
  }
  for(int i = 200; i > 0; i--) {
    OCR2B -= 1;
    readval =  read_voltage(0, gain);
    lcd.clear();
    lcd.print(readval, 2);
    delay(20);
  }
  */  

}

