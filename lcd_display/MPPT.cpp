#include "MPPT.hpp"
#include "pwm.hpp"
#include "power_sensing.hpp"
#include "Arduino.h"
#include <LiquidCrystal.h>
#include "main_menu.hpp"

#define left_button A3
#define enter_button A2
#define right_button A1

float duty = .1;
float max_duty = .45;
float min_duty = .1;
extern power MPPT;
extern LiquidCrystal lcd;

//Increases SEPIC duty cycle by an increment, never go above max_duty
void SEPIC_increase(float increment){
  if (duty + increment > max_duty) duty = max_duty;
  else duty += increment;
  set_PWM_duty_p9(duty);
}

//Decreases SEPIC duty cycle by an increment, never go below min_duty
void SEPIC_decrease(float increment){
  if (duty - increment < min_duty) duty = min_duty;
  else duty-= increment;
  set_PWM_duty_p9(duty);
}

//Indefinitely tracks the maximum power point using the perturb and observe method
void mppt(void){
   while(!digitalRead(enter_button)){
    //read input & output power
    //MPPT.read_power();
    MPPT.read_output_power();

    //If the power decreases, go the other way
    if (MPPT.old_output_power > MPPT.output_power ){
      SEPIC_decrease(.33);
      set_PWM_duty_p9(duty);
    }

    //If the power increases, keep going
    else if(MPPT.old_output_power < MPPT.output_power){
      SEPIC_increase(.33);
      set_PWM_duty_p9(duty);
    }

    MPPT.display_all();
  }
  lcd.clear();
  while(digitalRead(enter_button));
  
}

//Sweeps the duty cycle and prints the duty cycle and power to the LCD
void duty_sweep(int start_duty, int end_duty ){
  int i;
  for(i = start_duty; i < end_duty; i++){
    //MPPT.read_power();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(i/100.0);
    //delay(100);
    //MPPT.display_all();
    set_PWM_duty_p9(i/100.0);
    delay(100);
  }
}



//Reads power first to initialize old_power
//The current sensors are not supposed to have a greater than 26 V bus voltage
// This also established the duty cycle required to get close to that voltage
void mppt_init(void){
  int i;
  MPPT.read_power();
  
  for(i = 10; i < 100; i++){
    MPPT.read_output_power();
    set_PWM_duty_p9(i/200.0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Initializing...");
    lcd.setCursor(0,1);
    lcd.print(i/200.0);
    lcd.print(" ");
    lcd.print(MPPT.output_voltage);
    if(MPPT.output_voltage >= 25.5){
      max_duty = i/200.0;
      return;
    }
    delay(1000);
  }

}

//Finds the power point in a single, slow sweep
void find_pp(void){
  int i;
  float max_power = 0;
  float max_voltage= 0;
  float max_current = 0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Finding PP...");
  delay(1000);
  
  for (i = min_duty * 100 * 2 ; i < max_duty * 100 * 2; i++){ //half a percentage steps
    duty = i/(200.0);
    Serial.println(i);
    set_PWM_duty_p9(duty);
    MPPT.read_output_power();
    if (MPPT.output_power > max_power ){
      max_power = MPPT.output_power;
      max_current = MPPT.output_current;
      max_voltage = MPPT.output_current;
    }  
    delay(100);
  }
  //Displays the pp results to the lcd
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Max Power: ");
  lcd.print(max_power,2);
  lcd.print(" W");
  lcd.setCursor(0,1);
  lcd.print(max_current,2);
  lcd.print(" A ");
  lcd.print(max_voltage,2);
  lcd.print(" V");
  while(!digitalRead(enter_button));
  lcd.clear();
  while(digitalRead(enter_button));
  delay(100);
  
}


