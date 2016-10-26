#include <LiquidCrystal.h>
#include <SPI.h>

#define CS 10    // chip-select
#define DATAOUT 11   // MOSI 
#define DATAIN 12    // MISO 
#define SPICK 13  // Clock 

SPISettings settings(100000, MSBFIRST, SPI_MODE0);
LiquidCrystal lcd(8, 7, 3, 4 ,5 ,6);

float V_REF = 4.69;

void setup() {
  // set up the LCD's number of columns and rows:
  DDRB |= (1 << DDB1);
  
  TCCR1A =
      (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
      
  TCCR1B =
      (1 << WGM12) | (1 << WGM13) | (1 << CS10);
  OCR1A = 0;

  //set_PWM_duty(.5);
  
  lcd.begin(16, 2);
  lcd.noCursor();
  // lcd.autoscroll();

  
  // SPI initialization
  pinMode(CS, OUTPUT); 
  pinMode(DATAOUT, OUTPUT); 
  pinMode(DATAIN, INPUT); 
  pinMode(SPICK, OUTPUT);
  // disable device to start with 
  digitalWrite(CS, HIGH); 
  // Begin SPI reading
  SPI.begin();

  set_PWM_frequency(50000);
  set_PWM_duty(.5);

  
}
void set_PWM_frequency(float frequency){
   int freq;
   freq = int(16000000.0 / frequency);
   lcd.print(freq);
   ICR1 = freq;
}

void set_PWM_duty(float duty){
  int percent;
  percent = int(duty * ICR1);
  OCR1A = percent;
  lcd.clear();
  lcd.print(OCR1A);
}


void loop() {
  int v;
  int i;
  float readval;

  for (i=0; i< 100; i++){
    set_PWM_duty(i/100.0);
    readval = read_adc(0);
    lcd.clear();
    lcd.print(readval, 4);
    delay(500);
  }



}

float read_adc(int ch) {
  
  int adcval = 0;

  SPI.beginTransaction(settings);
  digitalWrite(CS, LOW);
  
  byte config = 0x0C;

  SPI.transfer(config | (ch >> 1));
  byte high = SPI.transfer(ch << 7);
  byte low = SPI.transfer(0x00);

  digitalWrite(CS, HIGH);
  SPI.endTransaction();
  adcval = ((high & 0x0f) << 8) + low;
  Serial.println(adcval);
  return (adcval*V_REF) / 4095.0;
}

