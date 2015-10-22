#include "main.h"

//set as timing 


void TIM3_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM3_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_Structure;
	
	uint16_t PrescalerValue = 0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_Structure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_Structure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Structure);	
		
	PrescalerValue = (uint16_t) (SystemCoreClock / 100000)-1;
	TIM3_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM3_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM3_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM3_TimeBaseStructure.TIM_Period = 1000;      //20ms
	TIM3_TimeBaseStructure.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM3,&TIM3_TimeBaseStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
}
