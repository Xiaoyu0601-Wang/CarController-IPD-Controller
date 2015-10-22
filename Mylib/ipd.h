#ifndef _IPD_H_
#define _IPD_H_

#include  "main.h"
#include <mapan.h>

/*λ��ʽIPD*/
typedef struct _IPD
{
  float  setpoint;   //�趨Ŀ��
  float  P;          //�������� p 
  float  I;          //���ֳ��� I 
  float  D;          //΢�ֳ��� D 
  float  lastcurrentpoint;  //Error[-1]
  long long sumerror;   //Sums of Errors
}ipdObj;


/*�����ⲿ����*/
extern void ipd_init(ipdObj *ipd, float setpoint, float I, float P, float D);
extern float ipd_calc(ipdObj *ipd, float currentpoint);

#endif
