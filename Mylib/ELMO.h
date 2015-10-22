#ifndef _ELMO_H
#define _ELMO_H
#include "main.h"

#define ELMO_NUM 3
/*******************************************************************************
                            ���ú궨��
*******************************************************************************/
#define CANBAUD_SET         CANBAUD_1M        //  ����CANͨ�ŵĲ�����
#define MOTION_PROFILE_TYPE 0                 //  ƽ���˶���ʽ;0:linear ramp
#define MAX_F_ERR           1000000           //  ����������
#define MIN_P_LIMIT        -1000000000        //  ��Сλ�ü���
#define MAX_P_LIMIT         1000000000        //  ���λ�ü���
#define MAX_SPEED           (8000*100/3)     //  ��������ٶ�
#define MAX_QDEC            1000000000        //  ������ֹͣ���ٶ�
#define MAX_ACC             160000            //  �����ٶ�
#define POLARITY            0xc0              //  0x00: �ٶ�λ�ö�����  1
                                              //  0xc0: �ٶ�λ�ö����� -1
                                              //  0x80: �ٶȳ���  1��λ�ó��� -1
                                              //  0x40: �ٶȳ��� -1��λ�ó���  1
/*******************************************************************************
                             ���ú궨��
*******************************************************************************/
#define ABS_POS             0x1f              //  PPMODE�����з�ʽ(runMode):����λ��
#define ABS_POS_IMM         0x3f              //  PPMODE�����з�ʽ(runMode):����λ��,��������3
#define REL_POS_IMM         0x7f              //  PPMODE�����з�ʽ(runMode):���λ��,��������7
#define REL_POS             0x5f              //  PPMODE�����з�ʽ(runMode):���λ��

/*******************************************************************************
                           �ڲ��궨��
*******************************************************************************/
#define Delay1              4                //  ��ʱ400us
#define Delay2              8                //  ��ʱ800us
#define Delay3              20               //  ��ʱ2ms
#define Delay_Read          15


/*******************************************************************************
                 Elmo��ؽṹ��д��ͬEpos
*******************************************************************************/

//  ƽ���ٶ�ģʽ�ṹ��
typedef struct _tPVMode
{
  long Speed;             //  ƽ���ٶ�ģʽ�����ٶ�ֵ
  long Acc;               //  ƽ���ٶ�ģʽ���ٶ�ֵ
  long Dec;               //  ƽ���ٶ�ģʽ���ٶ�ֵ
  long QSDec;             //  ƽ���ٶ�ģʽ��ͣ���ٶ�ֵ
}tPVMode;

//  ƽ��λ��ģʽ�ṹ��
typedef struct _tPPMode
{
  long Position;          //  ƽ��λ��ģʽ����λ��ֵ
  long Speed;             //  ƽ��λ��ģʽ�ٶ�
  long Acc;               //  ƽ��λ��ģʽ���ٶ�
  long Dec;               //  ƽ��λ��ģʽ���ٶ�
  long QSDec;             //  ƽ��λ��ģʽ��ͣ���ٶ�
}tPPMode;

//  ƽ��Ť��ģʽ�ṹ��
typedef struct _tPTMode
{
  long Torque;            //  ƽ��Ť����������ֵ
}tPTMode;

//  ����ģʽ�ܺͽṹ��
typedef struct _tMode
{
  tPPMode    PPMode;       //  ƽ��λ��ģʽ
  tPVMode    PVMode;       //  ƽ���ٶ�ģʽ
  tPTMode    PTMode;       //  ƽ��Ť��ģʽ
  void*     CurMode;       //  ָ��ǰģʽ��ָ��
}tMode;

//  Elmo�ṹ��,ÿ��Elmo��Ӧһ���ýṹ��
typedef struct _Elmo
{
  unsigned long ulNodeID; //  elmo����
  CanTxMsg     elmoCAN;  //  elmo���Ľṹ��,������elmoд������
  tMode         Mode;     //  elmo����ģʽ
}Elmo;

/*******************************************************************************
                               ��������
*******************************************************************************/
extern  Elmo      elmo[ELMO_NUM];
/*******************************************************************************  
                               �������� 
*******************************************************************************/
extern void Elmo_Init(Elmo* elmo, unsigned long elmoNum);	  /* ����ELMO�ĳ�ʼ�� ������һ��������*/
extern void Elmo_Write(Elmo* elmo, unsigned char Index, unsigned char SubIndex, int Param);
extern void Elmo_Read(Elmo* elmo, unsigned char Index, unsigned char SubIndex);
//extern void Elmo_RunPVM(Elmo* elmo, long speed, long acc, long dec, long QSDec);
//extern void Elmo_RunPPM(Elmo* elmo, long speed, long position, long acc, long dec, long runMode);
//extern void Elmo_QuickStop(Elmo* elmo);
#endif
