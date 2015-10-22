#include "main.h"
#include <ipd.h>

volatile unsigned short int PID_VFLAG = 0;
volatile unsigned short int PID_PFLAG = 0;

pidObj PidAxisX;
pidObj PidAxisY;
pidObj PidAngle;

ipdObj IpdAxisX;
ipdObj IpdAxisY;
ipdObj IpdAngle;

float Distance;

volatile SpeedType LastCMDVelocity = {0};
volatile SpeedType CMDVelocity = {0};
volatile SpeedType CMDPosition = {0};
volatile SpeedType Velocity = {0};
volatile SpeedType LastVelocity = {0};

volatile wheelSpeedType wheelRead = {0};
wheelSpeedType wheelsStop = {0};         /*�������ڴ洢3�������ٶȵ��ڲ�����*/
wheelSpeedType WheelSpeed= {0};

KalmanFilterType EncoderX = {0.05,0.2,0,0,0,0,0};
KalmanFilterType EncoderY = {0.05,0.2,0,0,0,0,0};
KalmanFilterType EncoderA = {0.05,0.2,0,0,0,0,0};

// float Q=0.05;
// float R=0.1;
// float Cov = 0;
// float Next_Cov = 0;
// float Kg = 0;
// int LAST_EstX = 0;
// int EstX = 0;
// int LAST_EstY = 0;
// int EstY = 0;
// int LAST_EstA = 0;
// int EstA = 0;

float conMatrix[3][3] = {
  {0.66666666667,0,2},
  {-0.33333333333,0.5773502691,2},
  {-0.33333333333,-0.5773502691,2}
};

/*******************************************************************************
��鸳���������ӵ��ٶ��Ƿ񳬹������������ṩ������ٶȣ�
����������Ͷ����ӵ��ٶ�������Ӧ�Ĵ���
*******************************************************************************/
void limitCheck(wheelSpeedType *output,int maxIn)
{
  long speedMax,speedMin;
  speedMax = output->speed1;
  speedMin = output->speed1;
  if (speedMax < output->speed2){
    speedMax = output->speed2;
  }
  if (speedMax < output->speed3){
    speedMax = output->speed3;
  }
  if (speedMin > output->speed2){
    speedMin = output->speed2;
  }
  if (speedMin > output->speed3){
    speedMin = output->speed3;
  }

  if ((speedMax > maxIn ) && (speedMax >= (0 - speedMin))){
    output->speed1 = output->speed1 * maxIn / speedMax;
    output->speed2 = output->speed2 * maxIn / speedMax;
    output->speed3 = output->speed3 * maxIn / speedMax;
  }
  else if (((0 - speedMin) > maxIn ) && (speedMax <= (0 - speedMin))){
    output->speed1 = output->speed1 * maxIn / (0 - speedMin);
    output->speed2 = output->speed2 * maxIn / (0 - speedMin);
    output->speed3 = output->speed3 * maxIn / (0 - speedMin);
  }
  return;
}
/*******************************************************************************
�����˶����ƣ�ʹ�����������̬
*******************************************************************************/
void MoveLock(void)
{
	Elmo_Write(&elmo[0],0x01,0x02,0x00); //�ͷŵ��
  Elmo_Write(&elmo[1],0x01,0x02,0x00);
  Elmo_Write(&elmo[2],0x01,0x02,0x00);
}
/*******************************************************************************
�ر��˶����ƣ�ʹ�����������̬
*******************************************************************************/
void MoveUnlock(void)
{
	Elmo_Write(&elmo[0],0x01,0x03,0x00); //�ͷŵ��
  Elmo_Write(&elmo[1],0x01,0x03,0x00);
  Elmo_Write(&elmo[2],0x01,0x03,0x00);
}
/*******************************************************************************
�˶�ִ�к�������wheelSpeedType���ٶ�д��elmo
*******************************************************************************/
void moveApply(wheelSpeedType *output)
{
  Elmo_Write(&elmo[0],0x01,0x01,output->speed1);
	Elmo_Write(&elmo[1],0x01,0x01,output->speed2);
	Elmo_Write(&elmo[2],0x01,0x01,output->speed3);
}

/*******************************************************************************
�ٶ����㺯����ʹÿ�����ӵ��ٶȹ���
*******************************************************************************/
void moveClear(wheelSpeedType *output)
{
  output->speed1 = 0;
  output->speed2 = 0;
  output->speed3 = 0;
}

/*******************************************************************************
ƽ�ƺ���������ÿ��������Ӧ���ṩ���ٶ�
����ϵΪ��3�����ּ���������Ϊԭ�㣬��1��Y���������ϵı�׼�ѿ�������ϵ
����ϵ��Գ�����ֹ
*******************************************************************************/
void moveCal(wheelSpeedType *output,float x, float y, float w)
{
	output->speed1 = (int)(conMatrix[0][0] * x + conMatrix[0][1] * y + conMatrix[0][2] * w);
	output->speed2 = (int)(conMatrix[1][0] * x + conMatrix[1][1] * y + conMatrix[1][2] * w);
	output->speed3 = (int)(conMatrix[2][0] * x + conMatrix[2][1] * y + conMatrix[2][2] * w);
  return;
}
/********************************Controller_Initial*************************************/
void PositionPID_Init(void)
{
	pid_init(&PidAxisX,0,0.55,0.0006,0.002);//0,0.9,0.0002,0.06//0.9,0.005,0.01
	pid_init(&PidAxisY,0,0.55,0.0006,0.002);//0.9,0.001,0.05//0,0.7,0.0011,0.05//0.5,0.0008,0.008
	pid_init(&PidAngle,0,0.03,0.001,0.0002);//0.75,0.00003,0.05//0,0.7,0.0012,0.05//0.3,0.003,0.02
}
/***********************************************************************/
void PositionIPD_Init(void)
{
	ipd_init(&IpdAxisX,0,0.018,0.95,0.15);//
	ipd_init(&IpdAxisY,0,0.018,0.95,0.15);//
//	pid_init(&PidAngle,0,0.03,0.0008,0.001);//0.043,0.001,0.00005
	ipd_init(&IpdAngle,0,0.00155,0.088,0.009);//
}
/*********************************Position_Control**************************************/
void PositionPIDCal(void)
{
	CMDVelocity.X = pid_calc(&PidAxisX,Total.x);
	CMDVelocity.Y = pid_calc(&PidAxisY,Total.y);
	CMDVelocity.A = pid_calc(&PidAngle,Total.theta);
	
//	AcceCheck();
	
	LastCMDVelocity.A = CMDVelocity.A;
	LastCMDVelocity.X = CMDVelocity.X;
	LastCMDVelocity.Y = CMDVelocity.Y;
}

void PositionIPDCal(void)
{
	CMDVelocity.X = ipd_calc(&IpdAxisX,Total.x);
	CMDVelocity.Y = ipd_calc(&IpdAxisY,Total.y);
	CMDVelocity.A = ipd_calc(&IpdAngle,Total.theta);
}
//	LastCMDVelocity.A = CMDVelocity.A;
//	LastCMDVelocity.X = CMDVelocity.X;
//	LastCMDVelocity.Y = CMDVelocity.Y;
/**************************************************************************/
void VelocityTransform(void)
{
	float TempX, TempY;
	
	TempX = CMDVelocity.X * cos(Total.angle) + CMDVelocity.Y * sin(Total.angle);
	TempY = CMDVelocity.Y * cos(Total.angle) - CMDVelocity.X * sin(Total.angle);//����ת��������������ϵ�µ��ٶ�ת��Ϊ����������ϵ��

	moveCal(&WheelSpeed,TempX,TempY,CMDVelocity.A); //moveCal(&wheelFoo,0,0,velocityA);ƽ�ƺ���������ÿ��������Ӧ���ṩ���ٶ�
	limitCheck(&WheelSpeed,VMAX);	//��鸳���������ӵ��ٶ��Ƿ񳬹������������ṩ������ٶȣ�
	moveApply(&WheelSpeed);	//�˶�ִ�к�������wheelSpeedType���ٶ�д��elmo
}
	
//	LastVelocity.X = Velocity.X;
//	LastVelocity.Y = Velocity.Y;
//	LastVelocity.A = Velocity.A;
/******************************File-End****************************************/
//void VelocityPID_Init(void)
//{
//	ipid_init(&PidVelocityX,0.32,0.038,0.015);//0.3,0.03,0.015//0.25,0.07,0.015
//	ipid_init(&PidVelocityY,0.32,0.038,0.015);//0.25,0.07,0.015
//	ipid_init(&PidVelocityA,0.3,0.04,0.05);//0.3,0.12,0.05
//}
/*******************************************************************************
�����������ϵ�µ�ָ����ٶȣ�ƽ���������˶�
*******************************************************************************/
//void AcceCheck(void)
//{
//	float VMax=30;
//	float CVMax=100;	
//	if((CMDVelocity.X-LastCMDVelocity.X) > VMax)//X
//	{
//		CMDVelocity.X = LastCMDVelocity.X + VMax;
//	}
//	if((CMDVelocity.X-LastCMDVelocity.X) < -VMax)
//	{
//		CMDVelocity.X = LastCMDVelocity.X - VMax;
//	}
//	if((CMDVelocity.Y-LastCMDVelocity.Y) > VMax)//Y
//	{
//		CMDVelocity.Y = LastCMDVelocity.Y + VMax;
//	}
//	if((CMDVelocity.Y-LastCMDVelocity.Y) < -VMax)
//	{
//		CMDVelocity.Y = LastCMDVelocity.Y - VMax;
//	}
//	if((CMDVelocity.A-LastCMDVelocity.A) > VMax)//A
//	{
//		CMDVelocity.A = LastCMDVelocity.A + VMax;
//	}
//	if((CMDVelocity.A-LastCMDVelocity.A) < -VMax)
//	{
//		CMDVelocity.A = LastCMDVelocity.A - VMax;
//	}	
///****************************************************/
//	if(CMDVelocity.X > CVMax)//X
//	{
//		CMDVelocity.X = CVMax;
//	}
//	if(CMDVelocity.X < -CVMax)
//	{
//		CMDVelocity.X = -CVMax;
//	}
//	if(CMDVelocity.Y > CVMax)//Y
//	{
//		CMDVelocity.Y = CVMax;
//	}
//	if(CMDVelocity.Y < -CVMax)
//	{
//		CMDVelocity.Y = -CVMax;
//	}
//	if(CMDVelocity.A > CVMax)//A
//	{
//		CMDVelocity.A = CVMax;
//	}
//	if(CMDVelocity.A < -CVMax)
//	{
//		CMDVelocity.A = -CVMax;
//	}
//}
