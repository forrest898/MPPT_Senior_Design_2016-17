#include "Arduino.h"
#include "lcd.hpp"
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

void lcd_init(void){
  lcd.begin(16, 2);
  lcd.noCursor();
  // lcd.autoscroll();
}

