#ifndef __BLDC_CONTROL_H
#define __BLDC_CONTROL_H

extern volatile unsigned char Status;
extern volatile int Speed;

void TIM2_Configuration(void);

#endif
