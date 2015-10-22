/************************************************************ 
Copyright (C), 1988-2013, Huawei Tech. Co., Ltd.
ProjectName: MotorDrive 
FileName: Main.c 
Author: Wang XiaoYu      Version: 2.0V         Date: 13/8/12
Description:           
Version: 2.0V       
Function  List: 
	1.int main(void);
	2.void RCC_Configuration(void);  
History:       
      <author>  <time>   <version>   <desc> 
	  Wang     13/5/6       1.0		  PID
      Wang     13/8/12      2.0     Kalman based PID   
***********************************************************/ 
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_DMA
  * @{
  */ 


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t uhADCxConvertedValue[6] = {0};//
/**
  * @brief  ADC3 channel07 with DMA configuration
  * @note   This function Configure the ADC peripheral  
            1) Enable peripheral clocks
            2) DMA2_Stream0 channel2 configuration
            3) Configure ADC Channel7 pin as analog input
            4) Configure ADC3 Channel7 
  * @param  None
  * @retval None
  */
void ADC_Configuration(void)
{
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;

  /* Enable ADCx, DMA and GPIO clocks ****************************************/ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	 
	DMA_InitStructure.DMA_Channel = DMA_Channel_0 ;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(ADC1_BASE+0x4C);
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)uhADCxConvertedValue;//change
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 6;//change
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//change
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);//change
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode =ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//change
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 6;//change
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel1 configuration **************************************/
  //ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_3Cycles);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_3Cycles);//change
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_3Cycles);//change
  ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_3Cycles);//change
  ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_3Cycles);//change
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_3Cycles);//change
  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_3Cycles);//change
 /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
	
	ADC_SoftwareStartConv(ADC1);
}






/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
