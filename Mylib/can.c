/************************************************************ 
Copyright (C), 1988-2013, Huawei Tech. Co., Ltd.
ProjectName: MotorDrive 
FileName: can.c 
Author: Wang XiaoYu      Version: 1.0V         Date: 17/5/14
Description: 
	1.CAN2_TX---PB13()
	2.CAN2_RX---PB12()
Version: 1.0V       
Function  List: 
	1.void CAN_Configuration(void);  
History:       
      <author>  <time>   <version>   <desc> 
	      Wang    17/5/14     1.0		        
***********************************************************/ 
#include  "main.h"
/*
*/
unsigned long g_Index;            //  全局变量,需要读的对象字典的索引
unsigned long g_SubIndex;         //  全局变量,需要读的对象字典的子索引
unsigned long g_ReadNodeID;       //  全局变量,需要读的节点ID

/* Public variables ---------------------------------------------------------*/
unsigned char DEVICE_CAN_ID = 4;
volatile unsigned char MailBox = 0;
volatile unsigned char CAN_FLAG = 0;
/* Private typedef -----------------------------------------------------------*/
CanTxMsg CAN_TxMessage;
CanRxMsg CAN_RxMessage;
/*
	初始化CAN
*/
void CAN_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
  CAN_InitTypeDef        CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* CAN GPIOs configuration **************************************************/

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  /* Connect CAN pins to AF9 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2); 
  
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* CAN configuration ********************************************************/  
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd((RCC_APB1Periph_CAN1 | RCC_APB1Periph_CAN2), ENABLE);
  /* CAN register init */
  CAN_DeInit(CAN2);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = DISABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	/* CAN Baudrate = 1 MBps (CAN clocked at 42 MHz) */
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq; 
  CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
  CAN_InitStructure.CAN_Prescaler = 3;
  CAN_Init(CAN2, &CAN_InitStructure);

  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = 14;
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = (DEVICE_CAN_ID<<5);//receive stdId=CAN_FilterIdHigh>>5.
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;//receive extId=CAN_FilterIdLow>>3
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFE0;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
  
  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
	
}
/*
	功能：测试CAN设置是否正确
*/
/*u8 CAN_send(void)		//环回模式 自测收发是否正确
{
  
}*/

