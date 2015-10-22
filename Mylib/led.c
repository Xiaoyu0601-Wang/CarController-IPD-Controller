/************************************************************ 
Copyright (C), 1988-2013, Huawei Tech. Co., Ltd.
ProjectName: Car 
FileName: led.c 
Author: Wang XiaoYu      Version: 1.0V         Date: 17/5/14
Description: 
	1.LED1---PC0():Green
	2.LED2---PC1():White
	3.LED3---PC2():Red
Version: 1.0V       
Function  List: 
	1.void LED_Configuration(void);  
History:       
      <author>  <time>   <version>   <desc> 
	      Wang    17/5/14     1.0		        
***********************************************************/ 
#include "main.h"

volatile unsigned short int LED_FLAG = 0;

void LED_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;   
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		
  GPIO_InitStructure.GPIO_Pin = LED1 | LED2 | LED3;			
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
  GPIO_Init(GPIOC, &GPIO_InitStructure); 	
}
