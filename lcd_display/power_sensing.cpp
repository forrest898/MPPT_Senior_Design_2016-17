#include "Arduino.h"
#include "power_sensing.hpp"
#include "adc.hpp"
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

//ADC Channel definitions
#define vin_ch 0
#define iin_ch 1
#define vout_ch 6
#define iout_ch 7

#define R1  385000.0
#define R2  99500.0
#define R3  385000.0
#define R4  98200.0

#define R5  100000.0
#define R6  1000.0
#define RS_1  .01

#define iin_scale 1.0
#define vin_scale 1.04
#define vout_scale 1.03
#define iout_scale 1.0

float vin_gain = (R2 + R1) / (R2) * vin_scale;
float iin_gain = (R5 / R6) * RS_1 * iin_scale;

float vout_gain = (R3 + R4) / (R4) * vout_scale;
float iout_gain = (R5 / R6) * RS_1 * iout_scale;

float read_voltage(int ch, float scale){
  float voltage;
  int i;
  int iterations = 10;
  voltage = 0.0;
  //averaging for smoothing
  for(i = 0; i < iterations; i++){
    voltage += read_adc(ch);
    delay(2);
  }
  return voltage * scale / iterations;
}

float read_current(int ch, float scale){
  float current;
  int i;
  int iterations =10; 
  current = 0.0;
  //averaging for smoothing
  for(i = 0; i < iterations; i++){
    current += read_adc(ch);
    delay(2);
  }
  return current * scale / iterations;
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
  output_voltage = read_voltage(vout_ch, vout_gain);
  output_current = read_current(iout_ch, iout_gain);
  old_output_power = output_power;
  output_power = output_voltage * output_current;
}

float power::power_efficiency(void){
  return output_power/ input_power;
}

void power::read_power(void){
  power::read_input_power();
  power::read_output_power();
}

void power::display_all(void){
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("input  ");
  lcd.print(" V:");
  lcd.print(input_voltage,3);
  lcd.setCursor(0,1);
  lcd.print("I:");
  lcd.print(input_current,3);
  lcd.print("  P:");
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

