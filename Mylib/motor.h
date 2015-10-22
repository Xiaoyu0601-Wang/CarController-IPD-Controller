#ifndef __PWM_H__
#define __PWM_H__

extern int Period;
extern int Max_Pulse;
void Motor_Configuration(void);
void Motor_Run(int pulse);
int Motor_ON(void);
int Motor_OFF(void);

#endif
