#include "adc.hpp"
#include "Arduino.h"
#include <SPI.h>

#define CS 3    // chip-select
#define DATAOUT 11   // MOSI
#define DATAIN 12    // MISO
#define SPICK 13  // Clock

extern float V_REF;

SPISettings settings(100000, MSBFIRST, SPI_MODE0);

void adc_init(void){
	// SPI initialization
    pinMode(CS, OUTPUT);
    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(SPICK, OUTPUT);
    //disable device to start with
    digitalWrite(CS, HIGH);
    // Begin SPI reading
    SPI.begin();
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
