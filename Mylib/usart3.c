/************************************************************ 
Copyright (C), 1988-2013, Huawei Tech. Co., Ltd.
ProjectName: MotorDrive 
FileName: usart.c 
Author: Wang XiaoYu      Version: 1.0V         Date: 17/5/14
Description: 
	1.LED1---PC10()
	2.LED2---PC11()
	3.LED3---PC12()
Version: 1.0V       
Function  List: 
	1.void LED_Configuration(void);  
History:       
      <author>  <time>   <version>   <desc> 
	      Wang    17/5/14     1.0		        
***********************************************************/ 
#include "main.h"


void USART3_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the USART2 Interrupt */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;			     	//设置串口1中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	     	//抢占优先级 0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//子优先级为0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能
  NVIC_Init(&NVIC_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
		
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;//2:Tx 3:Rx
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOA, &GPIO_InitStruct);

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* Configure USART2 */
  USART_Init(USART2, &USART_InitStructure);//配置串口参数函数
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //使能接收中断
// 	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);//使能发送缓冲空中断
  USART_Cmd(USART2, ENABLE);
  /* Enable USART2 Receive and Transmit interrupts */
}
