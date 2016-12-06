#include "Arduino.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 4, 5, 6, 7, 8);

void setup() {
  lcd.begin(16,2);
  lcd.noCursor();

}

void loop() {
  lcd.clear();
  lcd.print("hello, its me");
  delay(100);

}
