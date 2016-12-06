#include "Arduino.h"
#include "lcd.hpp"
#include <LiquidCrystal.h>

//LiquidCrystal lcd(8, 7, 2, 4 , 5 , 6);  //for the breadboard
LiquidCrystal lcd(2, 4, 5, 6, 7, 8);  //for the solderboard

void lcd_init(void){
  lcd.begin(16, 2);
  lcd.noCursor();
  //lcd.autoscroll();
}

