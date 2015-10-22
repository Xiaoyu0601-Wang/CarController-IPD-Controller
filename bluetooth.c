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
	1.void BLUETOOTH_Configuration(void);  
History:       
      <author>  <time>   <version>   <desc> 
	      Wang    17/5/14     1.0		        
***********************************************************/ 
#include "main.h"


void BLUETOOTH_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
 //char setname[]="AT+NAMEPRMI\r\n";//set bluetooth  name.
	//char psswrd[]="AT+PIN1234\r\n";//set bluetooth password
 // char master[]="AT+ROLE1\r\n";// master
  //char slave[]="AT+ROLE0\r\n";// slave
	uint8_t uart_i=0;//count the number of sending data
  uint8_t size=0;
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
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

// 	Delay1ms(10);
//   size=sizeof(psswrd);
// 	for(uart_i=0;uart_i<(size-1);uart_i++){
// 		USART_SendData(USART2, psswrd[uart_i]);
// 		Delay1ms(1);	
//   }
// 	for(uart_i=0;uart_i<(size-1);uart_i++){
// 		USART_SendData(USART2, psswrd[uart_i]);
// 		Delay1ms(1);	
//   }
}
void Delay1ms( unsigned int nCnt_1ms )
{
  u32 nCnt;
  for(; nCnt_1ms != 0; nCnt_1ms--)
    for(nCnt = 48000; nCnt != 0; nCnt--);
	
}
