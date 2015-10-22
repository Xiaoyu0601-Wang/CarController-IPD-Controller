#include "main.h"

//set as timing 


void TIM1_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM1_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_Structure;
	
	uint16_t PrescalerValue = 0;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	/*To get TIM1 counter clock at 1 MHz, the prescaler is computed as follows:
				 Prescaler = (TIM9CLK / TIM1 counter clock) - 1
				 Prescaler = (SystemCoreClock /1 MHz) - 1	*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_Structure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Structure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Structure);	
		
	PrescalerValue = (uint16_t) (SystemCoreClock / 100000)-1;
	TIM1_TimeBaseStructure.TIM_Prescaler = PrescalerValue;  
	TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM1_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM1_TimeBaseStructure.TIM_Period = 500;      //5ms
	TIM1_TimeBaseStructure.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM1,&TIM1_TimeBaseStructure);
	
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);  		
	TIM_Cmd(TIM1,ENABLE);    
	TIM_ClearFlag(TIM1,TIM_FLAG_Update);  
}
