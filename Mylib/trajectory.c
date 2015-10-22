#include "main.h"

float theta = 0;
unsigned char TrackFLAG = 0;
/****************Circle********************/
void CircleTracking(void)
{
	
	if(theta==360)
	{
//		theta=0;
		IpdAxisX.setpoint = 0;
		IpdAxisY.setpoint = 0;
	}
	else
	{
		theta=theta+1;
		IpdAxisX.setpoint = 300*cos(theta/57.2957795f);
		IpdAxisY.setpoint = 300*sin(theta/57.2957795f);
	}
}
/****************Square********************/
void SquareTracking(void)
{
	if((Total.x>505)&&(Total.y<0))
	{TrackFLAG = 1;}
	if((Total.x>505)&&(Total.y>505))
	{TrackFLAG = 2;}
	if((Total.x<0)&&(Total.y>505))
	{TrackFLAG = 3;}

	switch(TrackFLAG)
	{
		case 0:	IpdAxisX.setpoint = 510;IpdAxisY.setpoint = 0;break;
		case 1:	IpdAxisX.setpoint = 510;IpdAxisY.setpoint = 510;break;
		case 2:	IpdAxisX.setpoint = 0;IpdAxisY.setpoint = 510;break;
		case 3:	IpdAxisX.setpoint = 0;IpdAxisY.setpoint = 0;break;
	}
}

void GoBack(void)
{
	if((Total.x>505)&&(Total.y<0))
	{TrackFLAG = 1;}
	if((Total.theta>178.5f))
	{TrackFLAG = 2;}

	switch(TrackFLAG)
	{
		case 0:	IpdAxisX.setpoint = 510;IpdAxisY.setpoint = 0;break;
		case 1:	IpdAngle.setpoint = 180;break;
		case 2:	IpdAxisX.setpoint = 0;IpdAxisY.setpoint = 0;break;
	}
}
void TrajectoryGeneration(trajectoryObj *traj, mapanCalcType *speed)
{
	traj->Xa0 = Total.x;
	traj->Xa1 = Speed_Encoder.x;
	traj->Xa2 = 3 * (traj->XFinal - traj->XInitial
									- speed->x * traj->XTf) / traj->XTf2;
	traj->Xa3 = -2 * (traj->XFinal - traj->XInitial
									- speed->x * traj->XTf) / traj->XTf3;
/*******************************************************/
	traj->Ya0 = Total.y;
	traj->Ya1 = Speed_Encoder.y;
	traj->Ya2 = 3 * (traj->YFinal - traj->YInitial
									- speed->y * traj->YTf) / traj->YTf2;
	traj->Ya3 = -2 * (traj->YFinal - traj->YInitial
									- speed->y * traj->YTf) / traj->YTf3;
}

void TrajectoryCal(trajectoryObj *traj, SpeedType *cmdV)
{
	cmdV->X = traj->Xa1 + 2 * traj->Xa2 * traj->Xt
				    +3 * traj->Xa3 * traj->Xt * traj->Xt;
	
}
/****************Square********************/
void SignalTracking(void)
{
		theta=theta+1;
		PidAxisX.setpoint = 300*sin(theta/57.2957795f)+400*sin(theta/2/57.2957795f)+100*sin(theta/4/57.2957795f);
}
/*************************************End_File*********************************/
///****************Square********************/


//void SquareTracking(void)
//{
//	if (TrackFLAG!=4)
//	{theta = theta+10;}
//	if((Total.x>500)&&(Total.y<10))
//	{TrackFLAG = 1;theta = 0;}
//	if((Total.x<500)&&(Total.y>500))
//	{TrackFLAG = 2;theta = 0;}
//	if((Total.x<10)&&(Total.y>500))
//	{TrackFLAG = 3;theta = 0;}
//	if((Total.y<-10)&&(Total.x<10))
//	{TrackFLAG = 4;theta = 0;}
//	
//	switch(TrackFLAG)
//	{
//		case 0:	IpdAxisX.setpoint = theta;IpdAxisY.setpoint = 0;break;
//		case 1:	IpdAxisX.setpoint = 500;IpdAxisY.setpoint = theta;break;
//		case 2:	IpdAxisX.setpoint = 500-theta;IpdAxisY.setpoint = 500;break;
//		case 3:	IpdAxisX.setpoint = 0;IpdAxisY.setpoint = 500-theta;break;
//		default: break;
//	}
//}
