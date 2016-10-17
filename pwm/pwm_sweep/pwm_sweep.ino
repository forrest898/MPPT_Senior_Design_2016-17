void setup() {
  // Set PB1/2 as outputs.

  Serial.begin(9600);
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

}

void loop() {

  int i = 0;
  OCR1A = 0x03F;
  for(i = 0; i < 160; i++) {
    OCR1A += 0x01;
    delay(20);
    Serial.print(i);
  }
  // put your main code here, to run repeatedly:

}
