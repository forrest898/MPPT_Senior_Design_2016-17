#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 6, 7, 8);

int analogPin = 3;
int val = 0;
float voltage = 0;
float voltageRef = 4.9;
float scale = 4.9;
int resolution = 1020;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.noCursor();
  analogReference(EXTERNAL);


}

void loop() {
  // put your main code here, to run repeatedly:

}
