/************************************************************ 
Copyright (C), 1988-2013, Huawei Tech. Co., Ltd.
FileName: PWM.c 
Author: Wang XiaoYu      Version: 1.0V         Date: 13/5/6
Description:
	1.PWM1----PC6(TIM3_CH1)
	2.PWM2---PC7(TIM3_CH2)
	3.EN----PB0        
Version: 1.0V       
Function  List: 
	1.void PWM_Configuration(void);
	2.void Motor_Run(int Pulse); 
	3.void Motor_ON(void)；
	4.void Motor_OFF(void)； 
History:       
      <author>  <time>   <version>   <desc> 
				Wang      13/5/6      1.0		  
***********************************************************/ 
#include "main.h"
int Period = 4200;
int Max_Pulse = 2000;
volatile int Pulse_Temp = 0;

void Motor_Configuration(void)
{
/***************PWM*******************/	
	TIM_TimeBaseInitTypeDef  TIM3_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM3_OCInitStructure;
	GPIO_InitTypeDef         GPIO_InitStructure;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB
												| RCC_AHB1Periph_GPIOC, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	TIM3_TimeBaseStructure.TIM_Period = Period;
	TIM3_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock /2) / 84000000) - 1;
	TIM3_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM3_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM3_TimeBaseStructure);

	TIM3_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM3_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM3_OCInitStructure.TIM_Pulse = 0;
	TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM3_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC1Init(TIM3, &TIM3_OCInitStructure);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM3, &TIM3_OCInitStructure);

	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_CtrlPWMOutputs(TIM3,ENABLE);   
	TIM_Cmd(TIM3, ENABLE);
/***************ADC*******************/	
  GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_4 | GPIO_Pin_5);//AD
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_3Cycles);//change
  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_3Cycles);//change


}

/************************************************* 
Function: void Motor_Run(int Pulse)； 
Description: PWM占空比控制 
Calls: 无          //被本函数调用的函数清单 
Called By: 
	1.int main(void);        //调用本函数的函数清单 
Table Accessed:    // 被访问的表（此项仅对于牵扯到数据库操作的程序） 
Table Updated:     // 被修改的表（此项仅对于牵扯到数据库操作的程序） 
Input: Pulse PWM占空比控制输入，0~5960  //输入参数说明，包括每个参数的作 
                                        //用、取值说明及参数间关系。 
Output: 无 
Return: 无
Others: 无 
*************************************************/
void Motor_Run(int Pulse)
{
	if(Pulse > 0)
	{
		if(Pulse > Max_Pulse)
			{Pulse = Max_Pulse;}
		TIM3->CCR1 = 0;
		TIM3->CCR2 = abs(Pulse);
	}
	else 
	{
		if(Pulse < -Max_Pulse)
			{Pulse = -Max_Pulse;}
		TIM3->CCR1 = abs(Pulse);
		TIM3->CCR2 = 0;
	}
}
/***********************电机驱动使能***********************/
int Motor_ON(void)
{
	//Encoder_Start();				//启动编码器
	GPIO_SetBits(GPIOB,GPIO_Pin_0);	//使能电机
	return 1;
}
int Motor_OFF(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	return 0;
}
