#ifndef _ELMO_H
#define _ELMO_H
#include "main.h"

#define ELMO_NUM 3
/*******************************************************************************
                            配置宏定义
*******************************************************************************/
#define CANBAUD_SET         CANBAUD_1M        //  设置CAN通信的波特率
#define MOTION_PROFILE_TYPE 0                 //  平滑运动方式;0:linear ramp
#define MAX_F_ERR           1000000           //  最大允许误差
#define MIN_P_LIMIT        -1000000000        //  最小位置极限
#define MAX_P_LIMIT         1000000000        //  最大位置极限
#define MAX_SPEED           (8000*100/3)     //  最大运行速度
#define MAX_QDEC            1000000000        //  最大出错停止减速度
#define MAX_ACC             160000            //  最大加速度
#define POLARITY            0xc0              //  0x00: 速度位置都乘以  1
                                              //  0xc0: 速度位置都乘以 -1
                                              //  0x80: 速度乘以  1，位置乘以 -1
                                              //  0x40: 速度乘以 -1，位置乘以  1
/*******************************************************************************
                             调用宏定义
*******************************************************************************/
#define ABS_POS             0x1f              //  PPMODE的运行方式(runMode):绝对位置
#define ABS_POS_IMM         0x3f              //  PPMODE的运行方式(runMode):绝对位置,立即运行3
#define REL_POS_IMM         0x7f              //  PPMODE的运行方式(runMode):相对位置,立即运行7
#define REL_POS             0x5f              //  PPMODE的运行方式(runMode):相对位置

/*******************************************************************************
                           内部宏定义
*******************************************************************************/
#define Delay1              4                //  延时400us
#define Delay2              8                //  延时800us
#define Delay3              20               //  延时2ms
#define Delay_Read          15


/*******************************************************************************
                 Elmo相关结构体写法同Epos
*******************************************************************************/

//  平滑速度模式结构体
typedef struct _tPVMode
{
  long Speed;             //  平滑速度模式期望速度值
  long Acc;               //  平滑速度模式加速度值
  long Dec;               //  平滑速度模式减速度值
  long QSDec;             //  平滑速度模式急停减速度值
}tPVMode;

//  平滑位置模式结构体
typedef struct _tPPMode
{
  long Position;          //  平滑位置模式期望位置值
  long Speed;             //  平滑位置模式速度
  long Acc;               //  平滑位置模式加速度
  long Dec;               //  平滑位置模式减速度
  long QSDec;             //  平滑位置模式急停减速度
}tPPMode;

//  平滑扭矩模式结构体
typedef struct _tPTMode
{
  long Torque;            //  平滑扭矩期望电流值
}tPTMode;

//  各种模式总和结构体
typedef struct _tMode
{
  tPPMode    PPMode;       //  平滑位置模式
  tPVMode    PVMode;       //  平滑速度模式
  tPTMode    PTMode;       //  平滑扭矩模式
  void*     CurMode;       //  指向当前模式的指针
}tMode;

//  Elmo结构体,每个Elmo对应一个该结构体
typedef struct _Elmo
{
  unsigned long ulNodeID; //  elmo结点号
  CanTxMsg     elmoCAN;  //  elmo报文结构体,用于向elmo写入数据
  tMode         Mode;     //  elmo各种模式
}Elmo;

/*******************************************************************************
                               变量声明
*******************************************************************************/
extern  Elmo      elmo[ELMO_NUM];
/*******************************************************************************  
                               函数声明 
*******************************************************************************/
extern void Elmo_Init(Elmo* elmo, unsigned long elmoNum);	  /* 所有ELMO的初始化 调用这一个就行了*/
extern void Elmo_Write(Elmo* elmo, unsigned char Index, unsigned char SubIndex, int Param);
extern void Elmo_Read(Elmo* elmo, unsigned char Index, unsigned char SubIndex);
//extern void Elmo_RunPVM(Elmo* elmo, long speed, long acc, long dec, long QSDec);
//extern void Elmo_RunPPM(Elmo* elmo, long speed, long position, long acc, long dec, long runMode);
//extern void Elmo_QuickStop(Elmo* elmo);
#endif
