#include <LiquidCrystal.h>
#include <SPI.h>
#include "adc.hpp"
#include "lcd.hpp"
#include "pwm.hpp"
#include "power_sensing.hpp"

#define RELAY 16 // Relay

#define R1  385000.0
#define R2  99500.0

#define R3  
#define R4

#define R5
#define R6
#define R7
#define R8

#define R9
#define R10
#define R11
#define R12

#define vin_scale 1.04
#define vout_scale 1.05
#define iin_scale 1.00
#define iout_scale 1.00

LiquidCrystal lcd(8, 7, 2, 4 , 5 , 6);

float V_REF = 5.00;
float vin_gain = (R2 + R1) / (R2) * scale;
float vout_gain= (R4 + R3) / (R3) * scale
float iin_gain = 

void setup() {
  lcd_init();
  //PWM_init();
  adc_init();

  //set_PWM_frequency(50000);
  //set_PWM_duty(.5);
}


void loop() {
  int i, v;
  float readval;
  readval = read_voltage(7, v_gain);
  lcd.clear();
  lcd.print(readval, 2);
  delay(1000);

}

