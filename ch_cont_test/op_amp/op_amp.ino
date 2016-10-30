
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 7, 3, 4 ,5 ,6);

int analogPin = 6;
int val = 0;
float voltage = 0;
float voltageRef = 5.01;
float scale = 3.43;
int resolution = 1020;

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  lcd.begin(16, 2);
  lcd.noCursor();
}

float voltage_read(int pin, float scale) {
  val = analogRead(pin);
   
  return((val&resolution) / (float)resolution * voltageRef * scale);
  //return val;
}

void loop() {
  lcd.clear();
  voltage = voltage_read(analogPin, scale);
  lcd.println(voltage, 5);
  delay(70);
}

