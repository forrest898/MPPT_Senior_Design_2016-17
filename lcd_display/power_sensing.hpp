#ifndef power_sensing_hpp
#define power_sensing_hpp

class power {
  public:
   power(void);
   float input_voltage;
   float input_current;
   float input_power;
   float output_voltage;
   float output_current;
   float output_power;
   float old_output_power;
   void read_input_power(void);
   void read_output_power(void);
   void read_power(void);
   float power_efficiency(void);
   void display_all(void);
   void display_output(void);
};

void output_sensing(power MPPT);

#endif
