#include "main.h"

//encoder.OUTA---PB6(TIM4_CH1)
//encoder.OUTB---PB7(TIM4_CH2)

void Encoder_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure); 

	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,
	TIM_ICPolarity_Rising,
	TIM_ICPolarity_Rising);
	TIM_Cmd(TIM4,ENABLE);	 
}
void Encoder_Start(void)
{
	TIM4->CNT = 0x7fff;		 //¼ÆÊýÆ÷
}
int Encoder_Get_CNT(void)
{
	int cnt;
	cnt = (int)(TIM4->CNT) - 0x7fff;
	TIM4->CNT = 0x7fff;
	return cnt;
}
