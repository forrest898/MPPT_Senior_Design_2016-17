#include "power_sensing.hpp"
#include "Arduino.h"
#include "charger.hpp"
#include "MPPT.hpp"
#include <LiquidCrystal.h>

#define bat_ch  4
#define bat_threshold 14.5
#define current_threshold .3
#define float_voltage 13.2

extern LiquidCrystal lcd;
extern power MPPT;
extern float duty;

float bat_gain = (1/5);

//reads battery voltage
float check_battery(void){
    return read_voltage(bat_ch, bat_gain);
}

//If the battery 
void constant_current(float current){
  while (check_battery() < bat_threshold){
    MPPT.read_output_power();
    
    if (MPPT.output_current > current) SEPIC_decrease(.01);
    else SEPIC_increase(.01); 
    delay(100);
  }

}

void constant_voltage(void){
  while( MPPT.output_current > current_threshold){
    MPPT.read_output_power();

    if (check_battery() > bat_threshold) SEPIC_decrease(.01);
    else SEPIC_increase(.01);
    delay(100);
  }
}

void float_charge(void){
  while(1){
    if (check_battery() > float_voltage) SEPIC_decrease(.01);
    else SEPIC_increase(.01);
    delay(100);
  }
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

