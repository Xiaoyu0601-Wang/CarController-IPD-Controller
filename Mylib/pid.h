#ifndef _PID_H_
#define _PID_H_

/*位置式PID*/
typedef struct _PID
{
  float  setpoint;   //设定目标
  float  P;          //比例常数 p 
  float  I;          //积分常数 I 
  float  D;          //微分常数 D 
  float  lasterror;  //Error[-1]
  long long sumerror;   //Sums of Errors
}pidObj;

/*增量式PID*/
typedef struct _QPID
{
  float  P;          //比例常数 p 
  float  I;          //积分常数 I 
  float  D;          //微分常数 D 
  float  lasterror;  //Error[-1]
  float  preverror;  //Error[-2]
}ipidObj;


/*声明外部函数*/
extern void pid_init(pidObj *pid, float setpoint,float P,float I,float D);
extern float pid_calc(pidObj *pid, float nextPoint);
extern void ipid_init(ipidObj *ipid,float P,float I,float D);
extern float ipid_calc(ipidObj *ipid,float err);

#endif
