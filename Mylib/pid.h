#ifndef _PID_H_
#define _PID_H_

/*λ��ʽPID*/
typedef struct _PID
{
  float  setpoint;   //�趨Ŀ��
  float  P;          //�������� p 
  float  I;          //���ֳ��� I 
  float  D;          //΢�ֳ��� D 
  float  lasterror;  //Error[-1]
  long long sumerror;   //Sums of Errors
}pidObj;

/*����ʽPID*/
typedef struct _QPID
{
  float  P;          //�������� p 
  float  I;          //���ֳ��� I 
  float  D;          //΢�ֳ��� D 
  float  lasterror;  //Error[-1]
  float  preverror;  //Error[-2]
}ipidObj;


/*�����ⲿ����*/
extern void pid_init(pidObj *pid, float setpoint,float P,float I,float D);
extern float pid_calc(pidObj *pid, float nextPoint);
extern void ipid_init(ipidObj *ipid,float P,float I,float D);
extern float ipid_calc(ipidObj *ipid,float err);

#endif
