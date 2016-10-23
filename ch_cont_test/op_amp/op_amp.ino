int analogPin = 6;
int val = 0;
float voltage = 0;
float voltageRef = 5.02;
float scale = 3.43;
int resolution = 1020;

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
}

float voltage_read(int pin, float scale) {
  val = analogRead(pin);
  Serial.println(val, 5);
  return((val&resolution) / (float)resolution * voltageRef * scale);
  //return val;
}

void loop() {
  voltage = voltage_read(analogPin, scale);
  Serial.println(voltage, 5);
}

