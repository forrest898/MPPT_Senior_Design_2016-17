#include "Adafruit_INA219.hpp"
#include "Arduino.h"
#include "power_sensing.hpp"
#include <LiquidCrystal.h>
#include "main_menu.hpp"
#include "relay.hpp"

#define left_button A3
#define enter_button A2
#define right_button A1

extern LiquidCrystal lcd;
extern Adafruit_INA219 output;
extern Adafruit_INA219 input;

//POWER is a struct that hold the following variables
power::power(void){
   input_voltage = 0.0;
   input_current = 0.0;
   input_power = 0.0;
   output_voltage = 0.0;
   output_current = 0.0;
   output_power = 0.0;
   old_output_power = 0.0;
}
//Reads the input current and bus voltage from the input power sensing unit
void power::read_input_power(void){
  input_current = input.getCurrent_mA() / 1000;
  input_voltage = input.getBusVoltage_V() + (input.getShuntVoltage_mV() / 1000);
  input_power = input_current * input_voltage;

}
//Reads the output current and bus votlage from the output power sensing unit
void power::read_output_power(void){
  old_output_power = output_power;
  output_current = output.getCurrent_mA() / 1000;
  output_voltage = output.getBusVoltage_V() + (output.getShuntVoltage_mV() / 1000);
  output_power = output_current * output_voltage;
}
//Returns power efficiency of the SEPIC
float power::power_efficiency(void){
  return input_power/ output_power;
}
// Read both input power and output power simultaneously
void power::read_power(void){
  power::read_input_power();
  power::read_output_power();
}
//Displays just the output power sensing
void power::display_output(void){
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
}

// Displats input power, output power, and power efficiency
void power::display_all(void){

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("input  ");
  lcd.print(" V:");
  lcd.print(input_voltage,2);
  lcd.setCursor(0,1);
  lcd.print("I:");
  lcd.print(input_current,2);
  lcd.print("  P:");
  lcd.print(input_power,2);
  delay(1000);

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
  lcd.print(power::power_efficiency()*100,2);
  lcd.print("%");
  delay(1000);

}

void output_sensing(power MPPT){
  relay_on();
  delay(100);
  while(!digitalRead(enter_button)){
    MPPT.read_output_power();
    MPPT.display_output();
    delay(500);
  }
  lcd.clear();
  while(digitalRead(enter_button));
  relay_off();
  delay(100);
  
}

