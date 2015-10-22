#ifndef __HEAD_TASK_RACING_
#define __HEAD_TASK_RACING_
#include "main.h"
#include <ipd.h>

extern volatile unsigned short int PID_VFLAG;
extern volatile unsigned short int PID_PFLAG;

/*设置最大速度*/
#define VMAX 														100//pulse
//#define AMAX 														 5//mm

#define WHEEL_1                         0x01
#define WHEEL_2                         0x02
#define WHEEL_3                         0x04

#define CAR_STOP()											moveApply(&wheelsStop)

/*定义用于储存3个轮子速度的结构体*/
typedef struct _wheelSpeedType{
  int speed1;                              /*0度方向轮子（正前方）*/
  int speed2;                              /*120度方向轮子*/
  int speed3;                              /*240度方向轮子*/
}wheelSpeedType;

typedef struct _SpeedType
{
	float X;
	float Y;
  float A; //计算出的角度数据 角度制
}SpeedType;

extern pidObj PidAxisX;
extern pidObj PidAxisY;
extern pidObj PidAngle;

extern ipdObj IpdAxisX;
extern ipdObj IpdAxisY;
extern ipdObj IpdAngle;


extern volatile SpeedType LastCMDVelocity;
extern volatile SpeedType CMDVelocity;
extern volatile SpeedType CMDPosition;
extern volatile SpeedType Velocity;
extern volatile SpeedType LastVelocity;

extern volatile wheelSpeedType wheelRead;
extern wheelSpeedType wheelsStop;
extern wheelSpeedType WheelSpeed;

extern void limitCheck(wheelSpeedType *,int maxIn);
extern void AcceCheck(void);
extern void moveClear(wheelSpeedType *);
extern void moveCal(wheelSpeedType *output,float x, float y, float a);
extern void MoveLock(void);
extern void MoveUnlock(void);
extern void moveApply(wheelSpeedType *);
extern void PositionPID_Init(void);
extern void PositionPIDCal(void);
extern void PositionIPD_Init(void);
extern void PositionIPDCal(void);
extern void VelocityTransform(void);

#endif
//extern void VelocityPID_Init(void);
