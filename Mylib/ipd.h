#ifndef _IPD_H_
#define _IPD_H_

#include  "main.h"
#include <mapan.h>

/*位置式IPD*/
typedef struct _IPD
{
  float  setpoint;   //设定目标
  float  P;          //比例常数 p 
  float  I;          //积分常数 I 
  float  D;          //微分常数 D 
  float  lastcurrentpoint;  //Error[-1]
  long long sumerror;   //Sums of Errors
}ipdObj;


/*声明外部函数*/
extern void ipd_init(ipdObj *ipd, float setpoint, float I, float P, float D);
extern float ipd_calc(ipdObj *ipd, float currentpoint);

#endif
