#include <LiquidCrystal.h>
#include <SPI.h>
#include "adc.hpp"
#include "lcd.hpp"
#include "pwm.hpp"
#include "power_sensing.hpp"

#define RELAY 16 // Relay

#define R1  385000.0
#define R2  99500.0

#define R3  1.0
#define R4  1.0

#define R5  1.0
#define R6  1.0
#define RS_1  1.0

#define R7  1.0
#define R8 1.0
#define RS_2  1.0

#define vin_scale 1.04
#define vout_scale 1.00
#define iin_scale 1.00
#define iout_scale 1.00

float V_REF = 5.00;
float vin_gain = (R2 + R1) / (R2) * vin_scale;
float vout_gain= (R4 + R3) / (R3) * vout_scale;
float iin_gain = (R5) / (R6 * RS_1) * iin_scale;
float iout_gain = (R7) / (R8 * RS_2) * iout_scale;
float duty = .5;
power MPPT;

LiquidCrystal lcd(8, 7, 2, 4 , 5 , 6);

void setup() {
  //For debugging
  Serial.begin(9600);
  lcd_init();
  PWM_init();
  adc_init();
  set_PWM_frequency(50000);
  set_PWM_duty_p9(duty);
  delay(100);
  MPPT.read_output_power();
  duty += .01;
  delay(100);
  MPPT.read_output_power();
  duty -= .01;
  
}

void loop() {
  if (MPPT.old_output_power > MPPT.output_power ){
    duty -= .01;
  }
  else if(MPPT.old_output_power < MPPT.output_power){
    duty += .01;
  }

  MPPT.read_output_power();
  
}

