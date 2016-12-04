#include "Arduino.h"
#include "lcd.hpp"
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 7, 2, 4 , 5 , 6);

//initialization for LCD
void lcd_init(void){
  lcd.begin(16, 2);
  lcd.noCursor();
}

