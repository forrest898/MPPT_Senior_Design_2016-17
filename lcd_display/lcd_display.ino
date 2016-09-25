#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // initialize the serial communications:
  Serial.begin(9600);
  lcd.noCursor();
  //lcd.autoscroll();
}

void loop() {
  int i = 0;
  for (i = 1000; i > 0; i--){
    lcd.print(i);
    delay(1000);
    lcd.clear();
  }
}
