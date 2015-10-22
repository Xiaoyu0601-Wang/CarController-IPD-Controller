#include "main.h"

volatile unsigned short int MAPAN_FLAG = 0;

/*三个码盘的读取数据的结构体*/

volatile mapanCalcType Speed_Encoder = {0};
volatile mapanCalcType Speed = {0};
volatile mapanCalcType Total = {0};
float DeltaT = 4;

static float conInvMatrix[3][3] = {
	{1,-0.5,-0.5},
  {0,0.866025403784439,-0.866025403784439},
  {0.166666666666667,0.166666666666667,0.166666666666667},
};

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void MapanTask(void)
{    
	/*读出码盘的值*/
	
	CAN_FLAG = 0;
	Elmo_Read(&elmo[0],0x02,0x00);
	while (!CAN_FLAG);
	wheelRead.speed1 = CAN_RxMessage.Data[2]|(CAN_RxMessage.Data[3]<<8)
									 |(CAN_RxMessage.Data[4]<<16)|(CAN_RxMessage.Data[5]<<24);
	CAN_FLAG = 0;
	Elmo_Read(&elmo[1],0x02,0x00);
	while (!CAN_FLAG);
	wheelRead.speed2 = CAN_RxMessage.Data[2]|(CAN_RxMessage.Data[3]<<8)
									 |(CAN_RxMessage.Data[4]<<16)|(CAN_RxMessage.Data[5]<<24);
	
	CAN_FLAG = 0;
	Elmo_Read(&elmo[2],0x02,0x00);
	while (!CAN_FLAG);
	wheelRead.speed3 = CAN_RxMessage.Data[2]|(CAN_RxMessage.Data[3]<<8)
									 |(CAN_RxMessage.Data[4]<<16)|(CAN_RxMessage.Data[5]<<24);
	CAN_FLAG = 0;
	
	/*计算单位时间内三角码盘运动的xy坐标以及旋转的角度*/
	Speed_Encoder.x = conInvMatrix[0][0] * wheelRead.speed1 
					+ conInvMatrix[0][1] * wheelRead.speed2 
					+ conInvMatrix[0][2] * wheelRead.speed3;
	Speed_Encoder.x *= DisConst * XDisFix;
	Speed.x = Speed_Encoder.x * DeltaT;
	Speed_Encoder.x *= 100;//mm/Second
	Speed_Encoder.y = conInvMatrix[1][0] * wheelRead.speed1 
					+ conInvMatrix[1][1] * wheelRead.speed2 
					+ conInvMatrix[1][2] * wheelRead.speed3;
	Speed_Encoder.y *= DisConst * YDisFix;
	Speed.y = Speed_Encoder.y * DeltaT;
	Speed_Encoder.y *= 100;  //mm/Second
	Speed.angle = conInvMatrix[2][0] * wheelRead.speed1 
							+ conInvMatrix[2][1] * wheelRead.speed2 
							+ conInvMatrix[2][2] * wheelRead.speed3;
//	if (Speed.angle >0)
//	{
//		Speed.angle *= RotConst * ADisPosFix;
//	}
//	else
//	{
//		Speed.angle *= RotConst * ADisNegFix;
//	}
//	Speed_Encoder.theta = Speed.angle*57.2957795f;
	
	/*将计算出的值积分便得到路程*/
		Speed_Encoder.theta = AngularV[2]*200;  //Degree/Second
		Speed.theta = AngularV[2];
		Total.theta = Angle[2];
		Total.angle = Total.theta	/ 57.295779513f;

	Total.x += (Speed.x * cos(Total.angle) - Speed.y * sin(Total.angle));
	Total.y += (Speed.x * sin(Total.angle) + Speed.y * cos(Total.angle));
}
void Encoder_Clear(void)
{
	CAN_FLAG = 0;
	Elmo_Read(&elmo[0],0x02,0x00);
	while (!CAN_FLAG);
	CAN_FLAG = 0;
	Elmo_Read(&elmo[1],0x02,0x00);
	while (!CAN_FLAG);
	CAN_FLAG = 0;
	Elmo_Read(&elmo[2],0x02,0x00);
	while (!CAN_FLAG);
	CAN_FLAG = 0;
}
/*================END OF FILE=======================================================*/
