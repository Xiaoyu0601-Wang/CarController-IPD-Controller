#include "main.h"

//set as timing 


void TIM4_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM4_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_Structure;
	
	uint16_t PrescalerValue = 0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	/*To get TIM1 counter clock at 1 MHz, the prescaler is computed as follows:
				 Prescaler = (TIM9CLK / TIM1 counter clock) - 1
				 Prescaler = (SystemCoreClock /1 MHz) - 1	*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_Structure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_Structure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Structure);	
		
	PrescalerValue = (uint16_t) (SystemCoreClock / 100000)-1;
	TIM4_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM4_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM4_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM4_TimeBaseStructure.TIM_Period = 5000;      //100ms//5000,100ms
	TIM4_TimeBaseStructure.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM4,&TIM4_TimeBaseStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
}
