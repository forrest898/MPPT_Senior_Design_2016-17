#ifndef power_sensing_hpp
#define power_sensing_hpp

float read_voltage(int ch, float scale);
float read_current(int ch);
float read_power(int v_ch, int i_ch, float v_scale);
float power_efficiency(float input_power, float output_power);


#endif
