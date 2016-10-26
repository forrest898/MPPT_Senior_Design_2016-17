void setup() {
  // Set PB1 as outputs.
  DDRB |= (1 << DDB1);
  
  TCCR1A =
      (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
      
  TCCR1B =
      (1 << WGM12) | (1 << WGM13) | (1 << CS10);
  OCR1A = 0;
  ICR1 = 0x0140;  //make the freq 50k
}

void loop() {
  // Use OCR1A and OCR1B to control the PWM
  // duty cycle. Duty cycle = OCR1A / ICR1.
  // OCR1A controls PWM on pin 9 (PORTB1).
  // OCR1B controls PWM on pin 10 (PORTB2).
  //OCR1A = 0x0000;
  //delay(500);
  OCR1A = 0x007F;
  //delay(500);
  //OCR1A = 0x0140;
  //delay(500);
}
