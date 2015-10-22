#include "main.h"

void mapan_print(void)
{
	int TempX, TempY, TempA;
	unsigned char i;
	TempX = (int)Total.x;
	TempY = (int)Total.y;
	TempA = (int)(Total.theta*100);
/**************************Total.X*****************************/
	if (TempX < 0)
	{	
		BLUETOOTH_TxMessage[4] = (~TempX)%10 + '0';	
		BLUETOOTH_TxMessage[3] = ((~TempX)/10)%10 + '0';			
		BLUETOOTH_TxMessage[2] = ((~TempX)/100)%10 + '0';	
		BLUETOOTH_TxMessage[1] = ((~TempX)/1000)%10 + '0';	
		BLUETOOTH_TxMessage[0] = '-';
		BLUETOOTH_TxMessage[5] = ',';		
		for (i=0;i<=5;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
	else
	{
		BLUETOOTH_TxMessage[3] = TempX%10 + '0';	
		BLUETOOTH_TxMessage[2] = (TempX/10)%10 + '0';			
		BLUETOOTH_TxMessage[1] = (TempX/100)%10 + '0';	
		BLUETOOTH_TxMessage[0] = (TempX/1000)%10 + '0';	
		BLUETOOTH_TxMessage[4] = ',';
		for (i=0;i<=4;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
/**************************Total.Y*****************************/		
	if (TempY < 0)
	{	
		BLUETOOTH_TxMessage[4] = (~TempY)%10 + '0';	
		BLUETOOTH_TxMessage[3] = ((~TempY)/10)%10 + '0';			
		BLUETOOTH_TxMessage[2] = ((~TempY)/100)%10 + '0';	
		BLUETOOTH_TxMessage[1] = ((~TempY)/1000)%10 + '0';	
		BLUETOOTH_TxMessage[0] = '-';
		BLUETOOTH_TxMessage[5] = ',';		
		for (i=0;i<=5;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
	else
	{
		BLUETOOTH_TxMessage[3] = TempY%10 + '0';	
		BLUETOOTH_TxMessage[2] = (TempY/10)%10 + '0';			
		BLUETOOTH_TxMessage[1] = (TempY/100)%10 + '0';	
		BLUETOOTH_TxMessage[0] = (TempY/1000)%10 + '0';	
		BLUETOOTH_TxMessage[4] = ',';
		for (i=0;i<=4;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
/**************************Total.A*****************************/
	if (TempA < 0)
	{	
		BLUETOOTH_TxMessage[6] = (~TempA)%10 + '0';	
		BLUETOOTH_TxMessage[5] = ((~TempA)/10)%10 + '0';
		BLUETOOTH_TxMessage[4] = '.';
		BLUETOOTH_TxMessage[3] = ((~TempA)/100)%10 + '0';	
		BLUETOOTH_TxMessage[2] = ((~TempA)/1000)%10 + '0';	
		BLUETOOTH_TxMessage[1] = ((~TempA)/10000)%10 + '0';			
		BLUETOOTH_TxMessage[0] = '-';
		BLUETOOTH_TxMessage[7] = ';';		
		for (i=0;i<=7;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
	else
	{
		BLUETOOTH_TxMessage[5] = TempA%10 + '0';	
		BLUETOOTH_TxMessage[4] = (TempA/10)%10 + '0';
		BLUETOOTH_TxMessage[3] = '.';
		BLUETOOTH_TxMessage[2] = (TempA/100)%10 + '0';	
		BLUETOOTH_TxMessage[1] = (TempA/1000)%10 + '0';	
		BLUETOOTH_TxMessage[0] = ((~TempA)/10000)%10 + '0';		
		BLUETOOTH_TxMessage[6] = ';';
		for (i=0;i<=6;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
}

void gyro_print(void)
{
	int i;
	if (GyroRawData[2] < 0)
	{	
		BLUETOOTH_TxMessage[5] = (~GyroRawData[2])%10 + '0';	
		BLUETOOTH_TxMessage[4] = ((~GyroRawData[2])/10)%10 + '0';			
		BLUETOOTH_TxMessage[3] = ((~GyroRawData[2])/100)%10 + '0';	
		BLUETOOTH_TxMessage[2] = ((~GyroRawData[2])/1000)%10 + '0';
		BLUETOOTH_TxMessage[1] = ((~GyroRawData[2])/10000)%10 + '0';		
		BLUETOOTH_TxMessage[0] = '-';
		BLUETOOTH_TxMessage[6] = ',';//0x0D;//
		for (i=0;i<=6;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
	else
	{
		BLUETOOTH_TxMessage[4] = GyroRawData[2]%10 + '0';	
		BLUETOOTH_TxMessage[3] = (GyroRawData[2]/10)%10 + '0';			
		BLUETOOTH_TxMessage[2] = (GyroRawData[2]/100)%10 + '0';	
		BLUETOOTH_TxMessage[1] = (GyroRawData[2]/1000)%10 + '0';
		BLUETOOTH_TxMessage[0] = (GyroRawData[2]/10000)%10 + '0';
		BLUETOOTH_TxMessage[5] = ',';//0x0D;//
		for (i=0;i<=5;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
	if (GyroData[2] < 0)
	{	
		BLUETOOTH_TxMessage[5] = (~GyroData[2])%10 + '0';	
		BLUETOOTH_TxMessage[4] = ((~GyroData[2])/10)%10 + '0';			
		BLUETOOTH_TxMessage[3] = ((~GyroData[2])/100)%10 + '0';	
		BLUETOOTH_TxMessage[2] = ((~GyroData[2])/1000)%10 + '0';
		BLUETOOTH_TxMessage[1] = ((~GyroData[2])/10000)%10 + '0';		
		BLUETOOTH_TxMessage[0] = '-';
		BLUETOOTH_TxMessage[6] = 0x0D;//
		for (i=0;i<=6;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
	else
	{
		BLUETOOTH_TxMessage[4] = GyroData[2]%10 + '0';	
		BLUETOOTH_TxMessage[3] = (GyroData[2]/10)%10 + '0';			
		BLUETOOTH_TxMessage[2] = (GyroData[2]/100)%10 + '0';	
		BLUETOOTH_TxMessage[1] = (GyroData[2]/1000)%10 + '0';
		BLUETOOTH_TxMessage[0] = (GyroData[2]/10000)%10 + '0';
		BLUETOOTH_TxMessage[5] = 0x0D;//
		for (i=0;i<=5;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
}

void angle_print(void)
{
	int TempA;//TempRA,
	unsigned char i;
//	TempRA = (int)(RawAngle*1000);
	TempA = (int)(Angle[2]*100);

/**************************Total.RA*****************************/		
//	if (TempRA < 0)
//	{	
//		BLUETOOTH_TxMessage[6] = (~TempRA)%10 + '0';	
//		BLUETOOTH_TxMessage[5] = ((~TempRA)/10)%10 + '0';
//		BLUETOOTH_TxMessage[4] = ((~TempRA)/100)%10 + '0';	
//		BLUETOOTH_TxMessage[3] = '.';
//		BLUETOOTH_TxMessage[2] = ((~TempRA)/1000)%10 + '0';	
//		BLUETOOTH_TxMessage[1] = ((~TempRA)/10000)%10 + '0';			
//		BLUETOOTH_TxMessage[0] = '-';
//		BLUETOOTH_TxMessage[7] = ',';		
//		for (i=0;i<=7;i++)
//		{
//		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
//		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
//		}
//	}
//	else
//	{
//		BLUETOOTH_TxMessage[5] = TempRA%10 + '0';	
//		BLUETOOTH_TxMessage[4] = (TempRA/10)%10 + '0';
//		BLUETOOTH_TxMessage[3] = (TempRA/100)%10 + '0';	
//		BLUETOOTH_TxMessage[2] = '.';
//		BLUETOOTH_TxMessage[1] = (TempRA/1000)%10 + '0';	
//		BLUETOOTH_TxMessage[0] = ((TempRA)/10000)%10 + '0';		
//		BLUETOOTH_TxMessage[6] =',';
//		for (i=0;i<=6;i++)
//		{
//		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
//		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
//		}
//	}
/**************************Total.A*****************************/
	if (TempA < 0)
	{	
		BLUETOOTH_TxMessage[6] = (~TempA)%10 + '0';	
		BLUETOOTH_TxMessage[5] = ((~TempA)/10)%10 + '0';
		BLUETOOTH_TxMessage[4] = '.';		
		BLUETOOTH_TxMessage[3] = ((~TempA)/100)%10 + '0';
		BLUETOOTH_TxMessage[2] = ((~TempA)/1000)%10 + '0';	
		BLUETOOTH_TxMessage[1] = ((~TempA)/10000)%10 + '0';			
		BLUETOOTH_TxMessage[0] = '-';
		BLUETOOTH_TxMessage[7] = 0x0D;		
		for (i=0;i<=7;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
	else
	{
		BLUETOOTH_TxMessage[5] = TempA%10 + '0';	
		BLUETOOTH_TxMessage[4] = (TempA/10)%10 + '0';
		BLUETOOTH_TxMessage[3] = '.';
		BLUETOOTH_TxMessage[2] = (TempA/100)%10 + '0';		
		BLUETOOTH_TxMessage[1] = (TempA/1000)%10 + '0';	
		BLUETOOTH_TxMessage[0] = ((TempA)/10000)%10 + '0';
		
		BLUETOOTH_TxMessage[6] = 0x0D;
		for (i=0;i<=6;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
}


void PositionVelocity_print(void)
{
	int TempR,TempC,TempPR,TempPC;
	unsigned char i;
	TempR = (int)(Speed_Encoder.x*10);
	TempC = (int)(CMDVelocity.X*10);
	TempPR = (int)(Total.x);
	TempPC = (int)IpdAxisX.setpoint;//Pid

/**************************Total.R*****************************/		
	if (TempR < 0)
	{	

		BLUETOOTH_TxMessage[5] = (~TempR)%10 + '0';	
		BLUETOOTH_TxMessage[4] = '.';
		BLUETOOTH_TxMessage[3] = ((~TempR)/10)%10 + '0';	
		BLUETOOTH_TxMessage[2] = ((~TempR)/100)%10 + '0';
		BLUETOOTH_TxMessage[1] = ((~TempR)/1000)%10 + '0';
		BLUETOOTH_TxMessage[0] = '-';
		BLUETOOTH_TxMessage[6] = ',';
		for (i=0;i<=6;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
	else
	{

		BLUETOOTH_TxMessage[4] = TempR%10 + '0';	
		BLUETOOTH_TxMessage[3] = '.';
		BLUETOOTH_TxMessage[2] = (TempR/10)%10 + '0';	
		BLUETOOTH_TxMessage[1] = ((TempR)/100)%10 + '0';
		BLUETOOTH_TxMessage[0] = (TempR/1000)%10 + '0';
		BLUETOOTH_TxMessage[5] =',';
		for (i=0;i<=5;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
///**************************Total.C*****************************/
	if (TempC < 0)
	{	
		BLUETOOTH_TxMessage[5] = (~TempC)%10 + '0';
		BLUETOOTH_TxMessage[4] = '.';
		BLUETOOTH_TxMessage[3] = ((~TempC)/10)%10 + '0';	
		BLUETOOTH_TxMessage[2] = ((~TempC)/100)%10 + '0';
		BLUETOOTH_TxMessage[1] = ((~TempC)/1000)%10 + '0';
		BLUETOOTH_TxMessage[0] = '-';
		BLUETOOTH_TxMessage[6] = ',';
		for (i=0;i<=6;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
	else
	{

		BLUETOOTH_TxMessage[4] = TempC%10 + '0';
		BLUETOOTH_TxMessage[3] = '.';
		BLUETOOTH_TxMessage[2] = (TempC/10)%10 + '0';
		BLUETOOTH_TxMessage[1] = ((TempC)/100)%10 + '0';
		BLUETOOTH_TxMessage[0] = (TempC/1000)%10 + '0';
		BLUETOOTH_TxMessage[5] = ',';
		for (i=0;i<=5;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
/***********************************************************************/
if (TempPR < 0)
	{	
		BLUETOOTH_TxMessage[3] = (~TempPR)%10 + '0';	
		BLUETOOTH_TxMessage[2] = ((~TempPR)/10)%10 + '0';
		BLUETOOTH_TxMessage[1] = ((~TempPR)/100)%10 + '0';		
		BLUETOOTH_TxMessage[0] = '-';
		BLUETOOTH_TxMessage[4] = ',';//0x0D;//';';//
		for (i=0;i<=4;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
	else
	{
		BLUETOOTH_TxMessage[2] = TempPR%10 + '0';	
		BLUETOOTH_TxMessage[1] = (TempPR/10)%10 + '0';
		BLUETOOTH_TxMessage[0] = (TempPR/100)%10 + '0';		
		BLUETOOTH_TxMessage[3] = ',';//';';//0x0D;//';';//
		for (i=0;i<=3;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
/************************************************************************/
if (TempPC < 0)
	{	
		BLUETOOTH_TxMessage[3] = (~TempPC)%10 + '0';	
		BLUETOOTH_TxMessage[2] = ((~TempPC)/10)%10 + '0';
		BLUETOOTH_TxMessage[1] = ((~TempPC)/100)%10 + '0';		
		BLUETOOTH_TxMessage[0] = '-';
		BLUETOOTH_TxMessage[4] = 0x0D;//';';//
		for (i=0;i<=4;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
	else
	{
		BLUETOOTH_TxMessage[2] = TempPC%10 + '0';	
		BLUETOOTH_TxMessage[1] = (TempPC/10)%10 + '0';
		BLUETOOTH_TxMessage[0] = (TempPC/100)%10 + '0';		
		BLUETOOTH_TxMessage[3] = 0x0D;//';';//
		for (i=0;i<=3;i++)
		{
		USART_SendData(USART2, BLUETOOTH_TxMessage[i]);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
		}
	}
}
