#include "main.h"

//set as timing 


void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  TIM2_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_Structure;
	
	uint16_t PrescalerValue = 0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	/*To get TIM1 counter clock at 1 MHz, the prescaler is computed as follows:
				 Prescaler = (TIM9CLK / TIM1 counter clock) - 1
				 Prescaler = (SystemCoreClock /1 MHz) - 1	*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_Structure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_Structure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Structure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Structure);	
		
	PrescalerValue = (uint16_t) (SystemCoreClock / 100000)-1;
	TIM2_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM2_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM2_TimeBaseStructure.TIM_Period = 1000;      //20ms
	//（采样时间设定为10ms会引起震荡，原因不明；设为20ms后，震荡消失）
	TIM2_TimeBaseStructure.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2,ENABLE);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
}
