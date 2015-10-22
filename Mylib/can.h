#ifndef _CAN_H
#define _CAN_H

#include  "main.h"

#define CAN CAN2

extern unsigned long g_Index;            //  全局变量,需要读的对象字典的索引
extern unsigned long g_SubIndex;         //  全局变量,需要读的对象字典的子索引
extern unsigned long g_ReadNodeID;       //  全局变量,需要读的节点ID

extern unsigned char DEVICE_CAN_ID;
extern volatile unsigned char MailBox;
extern volatile unsigned char CAN_FLAG;

extern CanTxMsg CAN_TxMessage;
extern CanRxMsg CAN_RxMessage;

//extern void CAN_Configuration(void);
void CAN_Configuration(void);
//extern u8 CAN_send(void);
#endif
