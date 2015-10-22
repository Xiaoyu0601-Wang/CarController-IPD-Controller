#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

extern volatile unsigned char BLUETOOTH_TxMessage[16];
extern volatile unsigned char BLUETOOTH_RxMessage[16];
extern volatile unsigned char BLUETOOTH_RXFLAG;
extern volatile unsigned char BLUETOOTH_RxMessagePosion;
extern volatile unsigned char BLUETOOTH_RxMessageSize;

void BLUETOOTH_Configuration(void);
void Delay1ms( unsigned int nCnt_1ms );
#endif
