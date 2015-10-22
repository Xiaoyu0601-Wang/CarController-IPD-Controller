#include "main.h"

volatile unsigned char Status = 1;
volatile char direction = 0;//0是正，1是反
volatile int Speed = 30;
volatile int Speed_Temp = 0;

void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM2_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_Structure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	NVIC_Structure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Structure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Structure);

	TIM2_TimeBaseStructure.TIM_Prescaler = 0;  
	TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM2_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM2_TimeBaseStructure.TIM_Period = 14400;      //200us timing
	TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseStructure);

	TIM_Cmd(TIM2, ENABLE);	 
	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	
}

void TIM2_IRQHandler(void)
{
// 	ENCODER_FLAG = 1;
// 	LED_FLAG++; 
	direction = Speed >> 31;
// 	if(direction == 0)
// 	{Status = 6;}	
 	switch(Status)
	{	
		case 1 :  Motor_Run('A', Max_Pulse);
							Motor_Run('B', Speed);
							Motor_Run('C', 0);
							if(direction == 0)
							{
								if(TIM3->CCR2 == Max_Pulse)
								{Status = 2;}
							}
							else
							{
								if(TIM3->CCR2 == 0)
								{Status = 6;}
							}break;
		case 2 :  Motor_Run('A', -Speed);
							Motor_Run('B', Max_Pulse);
							Motor_Run('C', 0);
							if(direction == 0)
							{
								if(TIM3->CCR1 == 0)
								{Status = 3;}
							}
							else
							{
								if(TIM3->CCR1 == Max_Pulse)
								{Status = 1;}
							}break;
		case 3 :  Motor_Run('A', 0);
							Motor_Run('B', Max_Pulse);
							Motor_Run('C', Speed);
							if(direction == 0)
							{
								if(TIM3->CCR3 == Max_Pulse)
								{Status = 4;}
							}
							else
							{
								if(TIM3->CCR3 == 0)
								{Status = 2;}
							}break;
		case 4 :  Motor_Run('A', 0);
							Motor_Run('B', -Speed);
							Motor_Run('C', Max_Pulse);
							if(direction == 0)
							{	
								if(TIM3->CCR2 == 0)
								{Status = 5;}
							}
							else
							{
								if(TIM3->CCR2 == Max_Pulse)
								{Status = 3;}
							}break;
		case 5 :  Motor_Run('A', Speed);
							Motor_Run('B', 0);
							Motor_Run('C', Max_Pulse);
							if(direction == 0)
							{	
								if(TIM3->CCR1 == Max_Pulse)
								{Status = 6;}
							}
							else
							{
								if(TIM3->CCR1 == 0)
								{Status = 4;}
							}break;
		case 6 :  Motor_Run('A', Max_Pulse);
							Motor_Run('B', 0);
							Motor_Run('C', -Speed);
							if(direction == 0)
							{	
								if(TIM3->CCR3 == 0)
								{Status = 1;}
							}
							else
							{
								if(TIM3->CCR3 == Max_Pulse)
								{Status = 5;}
							}break;
		default	: break;
	}
  if(TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET) 
  {TIM_ClearFlag(TIM2, TIM_FLAG_Update);}	
}
