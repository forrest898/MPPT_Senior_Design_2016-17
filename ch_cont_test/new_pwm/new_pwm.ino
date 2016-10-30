#include <LiquidCrystal.h>
#include <SPI.h>
#include "adc.hpp"
#include "lcd.hpp"
#include "power_sensing.hpp"

LiquidCrystal lcd(8,7,2,4,5,6);

float V_REF = 5.02;
float gain = 3.43;
float readval;

void setup() {
  lcd_init();
  adc_init();
  //pinMode(3, INPUT);
  /*
  pinMode(3, OUTPUT);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  
  OCR2B = 0;
  */
}

void loop() {

 // readval =  read_voltage(0, gain);
 // lcd.clear();
 // lcd.print(readval, 2);
  
  for(int i=0; i<254; i++) {
    OCR2B += 1;
    readval =  read_voltage(0, gain);
    lcd.clear();
    lcd.print(readval, 2);
    delay(100);
  }
  for(int i = 254; i > 0; i--) {
    OCR2B -= 1;
    readval =  read_voltage(0, gain);
    lcd.clear();
    lcd.print(readval, 2);
    delay(100);
  }
  

}

