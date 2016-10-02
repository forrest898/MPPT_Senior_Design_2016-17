#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 6, 7, 8);

int analogPin = 3;
int val = 0;
float voltage = 0;
float voltageRef = 5.01;
float scale = 1;
int resolution = 1020;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.noCursor();
  analogReference(EXTERNAL);


}

float voltage_read(int pin, float scale) {
  val = analogRead(pin);
  return((val&resolution)/ float(resolution)*voltageRef*scale);
}

void loop() {
  voltage = voltage_read(analogPin, scale);
  lcd.print(voltage);
  delay(500);
  lcd.clear();

}
