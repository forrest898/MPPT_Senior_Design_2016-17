'#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 7, 3, 4 ,5 ,6);

int fetSW = 3;
int analogPin = 6;
int val = 0;
float voltage = 0;
float voltageRef = 5.01;
float scale = 3.43;
int resolution = 1020;

void setup() { 
  lcd.begin(16, 2);
  lcd.noCursor();
  pinMode(fetSW, OUTPUT);
  Serial.begin(9600);
  analogReference(EXTERNAL);
}

float voltage_read(int pin, float scale) {
  val = analogRead(pin);
  return((val&resolution) / (float)resolution * voltageRef * scale);
  //return val;
}


void loop() {

  //digitalWrite(fetSW, HIGH);
  //op_amp 
  delay(70);
  lcd.clear();
  voltage = voltage_read(analogPin, scale);
  lcd.print(voltage);
  lcd.print("\n");
  Serial.println(voltage, 5);
  if(voltage > 13.85) {
    digitalWrite(fetSW, LOW);
    lcd.print("Const V\n");
  } else {
    digitalWrite(fetSW, HIGH);
    lcd.print("Const Curr\n");
  }
  
 
}

