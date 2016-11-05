#include <LiquidCrystal.h>
#include <SPI.h>
#include "adc.hpp"
#include "lcd.hpp"
#include "power_sensing.hpp"
#include "pwm.hpp"

LiquidCrystal lcd(8,7,2,4,5,6);

float V_REF = 5.02;
float gain = 3.43;
float readval, readval2;

void setup() {
  lcd_init();
  adc_init();

  pinMode(3, OUTPUT);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  OCR2B = 0;
  //pinMode(3, INPUT);
  
 
}

void loop() {

  for(int i = 0; i <254; i++) {
    readval = read_voltage(0, gain);
    readval2 = read_voltage(2, 10.0);
    OCR2B += 1;
    lcd.clear();
    lcd.print(readval, 2);
    lcd.print("\n");
    lcd.print(readval2, 2);
    delay(50);
  }

  for(int i  = 254; i > 0; i--) {
   readval = read_voltage(0, gain);
   readval2 = read_voltage(2, 10.0);
    OCR2B -= 1;
    lcd.clear();
    lcd.print(readval, 2);
    lcd.print("\n");
    lcd.print(readval2, 2);
    delay(50);
  }
/*
  lcd.clear();
  readval = read_voltage(0, gain);
  lcd.print(readval, 2);
  delay(100);
  /*
  readval = 0;
  readval2 = 0;
  
  for(int i = 0; i < 10; i++) {
   
    readval +=  read_voltage(0, gain);
    readval2 +=  read_current(1, 10);
    
    delay(10);
  }

  readval /= 10;
  readval2 /= 10;
  lcd.clear();
  lcd.print(readval, 2);
  lcd.print("\n");
  lcd.print(readval2, 2);

  */
  /*
  for(int i=0; i<200; i++) {
    OCR2B += 1;
    for(int i = 0; i < 10; i++) {
     
      readval +=  read_voltage(0, gain);
      readval2 +=  read_current(1, 10);
      
    }
  
    readval /= 10;
    readval2 /= 10;
    lcd.clear();
    lcd.print(readval, 2);
    lcd.print("\n");
    lcd.print(readval2, 2);
    delay(20);
  }
  for(int i = 200; i > 0; i--) {
    OCR2B -= 1;
     for(int i = 0; i < 10; i++) {
     
      readval +=  read_voltage(0, gain);
      readval2 +=  read_current(1, 10);

    }
  
    readval /= 10;
    readval2 /= 10;
    lcd.clear();
    lcd.print(readval, 2);
    lcd.print("\n");
    lcd.print(readval2, 2);
    delay(20);
  }
   
*/
}

