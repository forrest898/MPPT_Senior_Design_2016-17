int cur_in = 1; 
int cur_out = 3;
int v_in = 0;
int v_out = 2;
int val = 0;
int resolution = 1020;
float v1 = 0;
float v2 = 0;
float i1 = 0;
float i2 = 0;
float p1 = 0;
float p2 = 0;
float scale = 4.9;
float voltageRef = 4.9;


void setup() {
  // put your setup code here, to run once:

  // Set PB1/2 as outputs.
  DDRB |= (1 << DDB1) | (1 << DDB2);

  TCCR1A =
      (1 << COM1A1) | (1 << COM1B1) |
      // Fast PWM mode.
      (1 << WGM11);
  TCCR1B =
      // Fast PWM mode.
      (1 << WGM12) | (1 << WGM13) |
      // No clock prescaling (fastest possible
      // freq).
      (1 << CS10);
  OCR1A = 0;
  // Set the counter value that corresponds to
  // full duty cycle. For 15-bit PWM use
  // 0x7fff, etc. A lower value for ICR1 will
  // allow a faster PWM frequency.
  ICR1 = 0x0140;  //make the freq 50k
  
  //analog and debug init stuff
  Serial.begin(9600);
  analogReference(EXTERNAL);

}

float read_v(int pin) {
  val = analogRead(pin);
  return((val&resolution) / (float)resolution * voltageRef * scale);
}

float read_i(int pin) {
  val = analogRead(pin);
  return val;
}

void loop() {

  v1 = read_v(v_in);
  v2 = read_v(v_out);
  i1 = ;
  i2 = ;
  
  // put your main code here, to run repeatedly:

}
