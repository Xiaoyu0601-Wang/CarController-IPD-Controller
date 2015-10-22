/************************************************************ 
Copyright (C), 1988-2013, Huawei Tech. Co., Ltd.
ProjectName: MotorDrive 
FileName: buzz.c 
Author: Wang XiaoYu      Version: 1.0V         Date: 17/5/14
Description: 
	1.BUZZ---PC13()

Version: 1.0V       
Function  List: 
	1.void BUZZ_Configuration(void);  
History:       
      <author>  <time>   <version>   <desc> 
	      Wang    17/5/14     1.0		        
***********************************************************/ 
#include "main.h"

void BUZZ_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;   
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		
  GPIO_InitStructure.GPIO_Pin = BUZZ;			
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOC, &GPIO_InitStructure); 	
}
