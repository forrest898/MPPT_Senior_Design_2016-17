#include "Arduino.h"
#include "power_sensing.hpp"
#include "adc.hpp"

float read_voltage(int ch, float scale){
  float voltage;
  voltage = read_adc(ch);
  return voltage * scale;
}

float read_current(int ch){
  return read_adc(ch);
}

float read_power(int v_ch, int i_ch, float v_scale){
  float voltage, current;
  voltage = read_voltage(v_ch, v_scale);
  current = read_current(i_ch);
  return voltage * current;
}

float power_efficiency(float input_power, float output_power){
  return input_power/output_power
}

