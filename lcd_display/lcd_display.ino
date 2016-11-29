#include <LiquidCrystal.h>
#include <SPI.h>
#include "adc.hpp"
#include "lcd.hpp"
#include "pwm.hpp"
#include "power_sensing.hpp"
#include "relay.hpp"
#include "charger.hpp"
#include "MPPT.hpp"
#include "Adafruit_INA219.h"

extern LiquidCrystal lcd;
extern float duty;
extern float max_duty;
extern float min_duty;
power MPPT;
Adafruit_INA219 ina219;

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
  set_PWM_duty_p9(.2);
  relay_on();
  ina219.begin();
  delay(1000);
  
}

void loop() {
  float current_mA;
   current_mA = ina219.getCurrent_mA();
   Serial.print("Current:   "); Serial.println(current_mA);
   delay(100);
}

