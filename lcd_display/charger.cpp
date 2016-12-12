#include "power_sensing.hpp"
#include "Arduino.h"
#include "charger.hpp"
#include "MPPT.hpp"
#include <LiquidCrystal.h>

#define bat_ch  A6

#define bat_threshold 14.5
#define current_threshold .3
#define float_voltage 13.2

#define left_button A3
#define enter_button A2
#define right_button A1

extern LiquidCrystal lcd;
extern power MPPT;
extern float duty;

float bat_gain = (1/5);

//reads battery voltage
float check_battery(void){
  return(analogRead(bat_ch) * 1024 * 5);
}

//Keeps the battery pulling a constant current 
void constant_current(float current){
  while (check_battery() < bat_threshold){
    MPPT.read_output_power();
    
    if (MPPT.output_current > current) SEPIC_decrease(.01);
    else SEPIC_increase(.01); 
    delay(100);
  }
}

//keeps the battery in constant_voltage
void constant_voltage(void){
  while( MPPT.output_current > current_threshold){
    MPPT.read_output_power();
    if (check_battery() > bat_threshold) SEPIC_decrease(.01);
    else SEPIC_increase(.01);
    delay(100);
  }
}

//keeps the battery in float state
void float_charge(void){
  while(!digitalRead(enter_button)){
    if (check_battery() > float_voltage) SEPIC_decrease(.01);
    else SEPIC_increase(.01);
    delay(100);
  }
  lcd.clear();
  while(digitalRead(enter_button));
}

//Charge the battery through the 3 states
void charge(void){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Constant Current");
  constant_current(1.1);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Constant Voltage");
  constant_voltage();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Float");
  float_charge();
}

