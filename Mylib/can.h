#ifndef _CAN_H
#define _CAN_H

#include  "main.h"

#define CAN CAN2

extern unsigned long g_Index;            //  ȫ�ֱ���,��Ҫ���Ķ����ֵ������
extern unsigned long g_SubIndex;         //  ȫ�ֱ���,��Ҫ���Ķ����ֵ��������
extern unsigned long g_ReadNodeID;       //  ȫ�ֱ���,��Ҫ���Ľڵ�ID

extern unsigned char DEVICE_CAN_ID;
extern volatile unsigned char MailBox;
extern volatile unsigned char CAN_FLAG;

extern CanTxMsg CAN_TxMessage;
extern CanRxMsg CAN_RxMessage;

//extern void CAN_Configuration(void);
void CAN_Configuration(void);
//extern u8 CAN_send(void);
#endif
