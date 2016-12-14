#include "power_sensing.hpp"
#include "Arduino.h"
#include "charger.hpp"
#include "MPPT.hpp"
#include <LiquidCrystal.h>

#define bat_ch  A6

#define bat_threshold 14.1
#define current_threshold .1
#define float_voltage 13.2

#define left_button A3
#define enter_button A2
#define right_button A1

extern LiquidCrystal lcd;
extern power MPPT;
extern float duty;

float bat_gain = 3.377;

//reads battery voltage
float check_battery(void){
  float batt_v = 0;
  for(int i = 0; i < 5; i++) {
    batt_v += (analogRead(bat_ch) * bat_gain * 5.0 )/ 1024.0;
  }
  batt_v /= 5;
  return batt_v;
}

//Keeps the battery pulling a constant current 
void constant_current(float current){
  digitalWrite(3,HIGH);
  while (check_battery() < bat_threshold){
    MPPT.read_output_power();
    
    if (MPPT.output_current > current) SEPIC_decrease(.01);
    else SEPIC_increase(.01); 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Batt_Volt: ");
    lcd.print(check_battery());
    lcd.setCursor(0,1);
    lcd.print("Const Cur: ");
    lcd.print(MPPT.output_current);
    delay(100);
  }
  digitalWrite(3,LOW);
}

//keeps the battery in constant_voltage
void constant_voltage(void){
  digitalWrite(3,HIGH);
  while( MPPT.output_current > current_threshold){
    MPPT.read_output_power();
    if (check_battery() > bat_threshold) SEPIC_decrease(.01);
    else SEPIC_increase(.01);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Batt_Volt: ");
    lcd.print(check_battery());
    lcd.setCursor(0,1);
    lcd.print("Const Volt: ");
    lcd.print(MPPT.output_current);
    delay(100);
  }
  digitalWrite(3,LOW);
}

//keeps the battery in float state
void float_charge(void){
  digitalWrite(3,LOW);
  while(!digitalRead(enter_button)){
    if (check_battery() > float_voltage) SEPIC_decrease(.01);
    else SEPIC_increase(.01);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Batt_Volt: ");
    lcd.print(check_battery());
    lcd.setCursor(0,1);
    lcd.print("Float : ");
    lcd.print(MPPT.output_current);
    delay(100);
  }
  lcd.clear();
  while(digitalRead(enter_button));
}

//Charge the battery through the 3 states
void charge(void){
  while(1) {
  lcd.clear();
  lcd.setCursor(0,0);
  constant_current(.2);
  lcd.clear();
  lcd.setCursor(0,0);
  constant_voltage();
  lcd.clear();
  lcd.setCursor(0,0);
  float_charge();
  }
}

