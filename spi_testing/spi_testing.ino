#include <SPI.h>
#include <HardwareSerial.h>

#define CS 10    // chip-select
#define DATAOUT 11   // MOSI 
#define DATAIN 12    // MISO 
#define SPICK 13  // Clock 

SPISettings settings(100000, MSBFIRST, SPI_MODE0);

void setup() {
  //set pin modes 
  pinMode(CS, OUTPUT); 
  pinMode(DATAOUT, OUTPUT); 
  pinMode(DATAIN, INPUT); 
  pinMode(SPICK, OUTPUT);
  // disable device to start with 
  digitalWrite(CS, HIGH); 

  SPI.begin();
 
  Serial.begin(9600); 
}
int v;
double voltage;
void loop() {
  
  v =read_adc(2);
  voltage = (v*4.99) / 4095;
  Serial.print("Voltage on CH0 =");
  Serial.println(voltage, 5);
  delay(500);
}

int read_adc(int ch) {
  
  int adcval = 0;

  //SPI.setClockDivider(SPI_CLOCK_DIV16);
  
  //SPI.setBitOrder(MSBFIRST);
  //SPI.setDataMode(SPI_MODE0);
  SPI.beginTransaction(settings);
  digitalWrite(CS, LOW);
  
  byte config = 0x0C;

  SPI.transfer(config | (ch >> 1));
  byte high = SPI.transfer(ch << 7);
  byte low = SPI.transfer(0x00);

  digitalWrite(CS, HIGH);
  SPI.endTransaction();
  adcval = ((high & 0x0f) << 8) + low;
  
 // SPI.setClockDivider(SPI_CLOCK_DIV4);

  return adcval;
  
}

