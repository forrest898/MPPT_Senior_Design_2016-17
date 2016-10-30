#include "Arduino.h"
#include "power_sensing.hpp"
#include "adc.hpp"
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

//ADC Channel definitions
#define vin_ch 0
#define iin_ch 1
#define vout_ch 2
#define iout_ch 3

#define R1  385000.0
#define R2  99500.0

#define R5  100000.0
#define R6  1000.0
#define RS_1  .01

#define iin_scale 1.00
#define vin_scale 1.04


float vin_gain = (R2 + R1) / (R2) * vin_scale;
float iin_gain = (R5) / (R6 * RS_1) * iin_scale;

float read_voltage(int ch, float scale){
  float voltage;
  int i;
  voltage = 0.0;
  for(i = 0; i < 5; i++){
    voltage += read_adc(ch);
  }
  return voltage * scale / 5;
}

float read_current(int ch, float scale){
  float current;
  int i;
  current = 0.0;
  for(i = 0; i < 5; i++){
    current += read_adc(ch);
  }
  return current * scale / 5;
}

float power_efficiency(float input_power, float output_power){
  return input_power/output_power;
}

power::power(void){
   input_voltage = 0.0;
   input_current = 0.0;
   input_power = 0.0;
   output_voltage = 0.0;
   output_current = 0.0;
   output_power = 0.0;
   old_output_power = 0.0;
}

void power::read_input_power(void){ 
  input_voltage = read_voltage(vin_ch,vin_gain);
  input_current = read_current(iin_ch,iin_gain);
  input_power = input_voltage * input_current;
}

void power::read_output_power(void){
  output_voltage = read_voltage(vout_ch, 1);
  output_current = read_current(iout_ch, 1);
  old_output_power = output_power;
  output_power = output_voltage * output_current;
}

float power::power_efficiency(void){
  return output_power/ input_power;
}

void power::display_all(void){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("input ");
  lcd.print(" V:");
  lcd.print(input_voltage,2);
  lcd.setCursor(0,1);
  lcd.print("I:");
  lcd.print(input_current,2);
  lcd.print(" P:");
  lcd.print(input_power,2);
  delay(1000);
  /*
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("output ");
  lcd.print("V:");
  lcd.print(output_voltage,2);
  lcd.setCursor(0,1);
  lcd.print("I:");
  lcd.print(output_current,2);
  lcd.print(" P:");
  lcd.print(output_power,2);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Power efficiency ");
  lcd.setCursor(0,1);
  lcd.print(power_efficiency()*100,2);
  lcd.print("%");
  delay(1000);*/

}

