#include <SPI.h>
#include <HardwareSerial.h>

#define CS 10    // chip-select
#define DATAOUT 11   // MOSI 
#define DATAIN 12    // MISO 
#define SPICK 13  // Clock 
#define R1  380000.0
#define R2  99500.0
#define V_ref 4.6

double gain = (R2+R1)/(R2);

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
  
  v =read_adc(6);
  voltage = (v*V_ref) / 4095.0;
  voltage = voltage * gain;
  Serial.print(voltage,5);
  Serial.println(" V");
  delay(500);
}

int read_adc(int ch) {
  
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

  return adcval;
  
}

