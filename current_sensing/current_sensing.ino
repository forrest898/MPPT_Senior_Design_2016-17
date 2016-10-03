void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(EXTERNAL);

}

float current_read(int pin) {
  val = analogRead(pin);
  return((val&resolution) / (float)resolution * voltageRef);
}

void loop() {
  // put your main code here, to run repeatedly:

}
