
int analogPin = 3;
int val = 0;
float voltage = 0;
float voltageRef = 4.9;
float scale = 4.9;
int resolution = 1020;

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
}

float voltage_read(int pin, float scale) {
  val = analogRead(pin);
  return((val&resolution) / (float)resolution * voltageRef * scale);
  //return val;
}

void loop() {
  voltage = voltage_read(analogPin, scale);
  Serial.println(voltage, 5);
}


