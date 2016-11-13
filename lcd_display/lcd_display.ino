#include <LiquidCrystal.h>
#include <SPI.h>
#include "adc.hpp"
#include "lcd.hpp"
#include "pwm.hpp"
#include "power_sensing.hpp"
#include "relay.hpp"
#include "charger.hpp"
#include "MPPT.hpp"

extern float duty;
extern float max_duty;
extern float min_duty;
power MPPT;

extern LiquidCrystal lcd;

void setup() {
  //For debugging
  Serial.begin(9600);

  //Initializations
  lcd_init();
  PWM_init();
  relay_init();
  adc_init();
  mppt_init();
  set_PWM_frequency(50000);
  set_PWM_duty_p9(duty);
  
  relay_on();
  delay(1000);
  
}

void loop() {
  MPPT.read_output_power();
  MPPT.display_all();

}

