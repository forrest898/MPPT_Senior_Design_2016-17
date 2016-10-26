#include <SPI.h>
#include <HardwareSerial.h>

#define CS 10    // chip-select
#define DATAOUT 11   // MOSI 
#define DATAIN 12    // MISO 
#define SPICK 13  // Clock 

void setup() {
  //set pin modes 
  pinMode(CS, OUTPUT); 
  // disable device to start with 
  digitalWrite(CS, HIGH); 

  SPI.begin();
 
  Serial.begin(9600); 
}
int v;
double voltage;
void loop() {
  
  v =read_adc(0);
  voltage = (v*4.62) /4095.0;
  Serial.print("Voltage on CH0 =");
  Serial.println(voltage, 5);
  delay(500);
}

int read_adc(int ch) {
  
  int adcval = 0;

  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

  digitalWrite(CS, LOW);
  
  byte config = 0x0C;

  SPI.transfer(config | (ch >> 1));
  byte high = SPI.transfer(ch << 7);
  byte low = SPI.transfer(0x00);

  digitalWrite(CS, HIGH);

  adcval = ((high & 0x0f) << 8) + low;

  SPI.setClockDivider(SPI_CLOCK_DIV4);

  return adcval;
  
}

