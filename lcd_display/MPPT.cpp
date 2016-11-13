#include "MPPT.hpp"
#include "pwm.hpp"
#include "power_sensing.hpp"
#include "Arduino.h"
#include <LiquidCrystal.h>

float duty = .3;
float max_duty = .43;
float min_duty = .15;
extern power MPPT;
extern LiquidCrystal lcd;

//15 volt in -- .15 min, .45 max

//Increases SEPIC duty cycle by an increment
void SEPIC_increase(float increment){
  if (duty + increment > max_duty) duty = max_duty;
  else duty += increment;
  set_PWM_duty_p9(duty);
}

//Decreases SEPIC duty cycle by an increment
void SEPIC_decrease(float increment){
  if (duty - increment < min_duty) duty = min_duty;
  else duty-= increment;
  set_PWM_duty_p9(duty);
}

//Indefinitely tracks the maximum power point using the perturb and observe method
void mppt(void){
  while (1){
    //read input & output power
    MPPT.read_power();

    //If the power decreases, go the other way
    if (MPPT.old_output_power > MPPT.output_power ){
      SEPIC_decrease(.33);
      set_PWM_duty_p9(duty);
    }

    //If the power increases, 
    else if(MPPT.old_output_power < MPPT.output_power){
      SEPIC_increase(.33);
      set_PWM_duty_p9(duty);
    }

    MPPT.display_all();
    
  }
}

//Reads power first to initialize old_power
void mppt_init(void){
  MPPT.read_power();
  delay(100);

}

//Finds the power point in a single, slow sweep
void find_pp(void){
  int i;
  float max_power = 0;
  float max_voltage= 0;
  float max_current = 0;
  
  for (i = min_duty*100; i < max_duty*100; i++){
    duty = i/(100.0);
    set_PWM_duty_p9(duty);
    MPPT.read_output_power();
    if (MPPT.output_power > max_power ){
      max_power = MPPT.output_power;
      max_current = MPPT.output_current;
      max_voltage = MPPT.output_current;
    }
    
    delay(500);
  }
  //Displays the pp results to the lcd
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Max Power: ");
  lcd.print(max_power,2);
  lcd.setCursor(0,1);
  lcd.print(max_current,2);
  lcd.print(" A, ");
  lcd.print(max_voltage,2);
  lcd.print(" V, ");

  while(1);

  
}


