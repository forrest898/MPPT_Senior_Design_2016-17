#ifndef MPPT_hpp
#define MPPT_hpp


void SEPIC_increase(float increment);
void SEPIC_decrease(float increment);
void mppt(void);
void mppt_init(void);
void find_pp(void);
void duty_sweep(int start_duty, int end_duty);

#endif
