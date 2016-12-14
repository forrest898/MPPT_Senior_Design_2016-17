#include <LiquidCrystal.h>
#include <SPI.h>
#include "lcd.hpp"
#include "pwm.hpp"
#include "power_sensing.hpp"
#include "relay.hpp"
#include "charger.hpp"
#include "main_menu.hpp"
#include "MPPT.hpp"
#include "Adafruit_INA219.hpp"

extern LiquidCrystal lcd;
extern float duty;
extern float max_duty;
extern float min_duty;

#define left_button A3
#define enter_button A2
#define right_button A1


power MPPT;
Adafruit_INA219 output(0x40);
Adafruit_INA219 input(0x41);

void setup() {
  //For debugging

  Serial.begin(9600);
  //Initializations
  lcd_init();
  PWM_init();
  relay_init();
  button_init();
  set_PWM_frequency(50000);
  set_PWM_duty_p9(.1);
  output.begin();
  input.begin();
  delay(1000);

}

void loop() {
  main_menu();
}
