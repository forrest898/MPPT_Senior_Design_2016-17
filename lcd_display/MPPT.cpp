#include "MPPT.hpp"
#include "pwm.hpp"
#include "power_sensing.hpp"
#include "Arduino.h"
#include <LiquidCrystal.h>
#include "main_menu.hpp"

#define left_button A3
#define enter_button A2
#define right_button A1

float duty = .05;
float max_duty = .35;
float absolute_max = .65;
float min_duty = .01;
extern power MPPT;
extern LiquidCrystal lcd;

//Increases SEPIC duty cycle by an increment, never go above max_duty
void SEPIC_increase(float increment){
  if (duty + increment > absolute_max) duty = max_duty;
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
   duty = min_duty;
   MPPT.read_power();
   
   while(!digitalRead(enter_button)){
    //read input & output power
    MPPT.read_power();

    //If the power decreases, go the other way
    if (MPPT.old_output_power > MPPT.output_power ){
      SEPIC_decrease(.005);
    }

    //If the power increases, keep going
    else if(MPPT.old_output_power < MPPT.output_power){
      SEPIC_increase(.005);
    }
    delay(1000);
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
  //sweeps over a 
  for(i = 40; i < absolute_max*2*100; i++){
    MPPT.read_output_power();
    set_PWM_duty_p9(i/200.0); //allows for half percent increments
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Initializing...");
    lcd.setCursor(0,1);
    lcd.print(i/200.0);
    lcd.print(" ");
    lcd.print(MPPT.output_voltage);
    if(MPPT.output_voltage >= 24){
      max_duty = i/200.0;
      break;
    }
    delay(1000);
  }
  if(i == absolute_max*2*100) max_duty = absolute_max;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Max Duty:");
  lcd.print(max_duty);
  delay(3000);

}

//Finds the power point in a single, slow sweep
void find_pp(void){
  
  int i;
  float max_power = 0;
  float max_voltage= 0;
  float max_current = 0;

  mppt_init();
 
  for (i = min_duty * 100 * 2 ; i < max_duty * 100 * 2; i++){ //half a percentage steps
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Finding PP...");
    delay(1000);
    duty = i/(200.0);
    lcd.setCursor(0,1);
    lcd.print("D:");
    lcd.print(duty,3);
    lcd.print(" ");
    
    SEPIC_increase(duty);
    MPPT.read_output_power();
    
    lcd.print("P:");
    lcd.print(MPPT.output_power,3);
    
    if (MPPT.output_power > max_power ){
      max_power = MPPT.output_power;
      max_current = MPPT.output_current;
      max_voltage = MPPT.output_voltage;
    }  
    delay(1000);
  }
  //Displays the pp results to the lcd
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Max Power: ");
  lcd.print(max_power,3);
  lcd.print(" W");
  lcd.setCursor(0,1);
  lcd.print(max_current,3);
  lcd.print(" A ");
  lcd.print(max_voltage,3);
  lcd.print(" V");
  while(!digitalRead(enter_button));
  lcd.clear();
  while(digitalRead(enter_button));
  delay(100);
  
}
// User adjustable SEPIC values that print voltage, power, and current
void sepic_adjust(void){
  int eb,rb,lb;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(duty);
  
  while(1){

    while(1){
        MPPT.read_output_power();
        lcd.setCursor(0,1);
        lcd.print("V:");
        lcd.print(MPPT.output_voltage,3);
        lcd.print("  I:");
        lcd.print(MPPT.output_current,3);
        lcd.setCursor(8,0);
        lcd.print("P:");
        lcd.print(MPPT.output_power,3);
        
        eb = digitalRead(enter_button);
        rb = digitalRead(right_button);
        lb = digitalRead(left_button);
        if(eb | rb | lb){
          while((digitalRead(enter_button) | digitalRead(right_button) | digitalRead(left_button))); 
          break;
        }
        delay(10);
    }
    if(eb) break;
    if(rb) {
      duty += .01;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(duty);
      set_PWM_duty_p9(duty);
      
    }
    if(lb) {
      duty -= .01;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(duty);
      set_PWM_duty_p9(duty);
    }
  }
}


