#ifndef __LOWPASSFILTER_H__
#define __LOWPASSFILTER_H__

typedef struct _LPF
{
  short int Output;   //
  short int Input;          //
  float DynamicPara;          //
	short int DynamicRange;
}lpfObj;

extern lpfObj GyroZLPF;

void LPF_Initial(void);
short int LPF_Calculation(lpfObj *lpf);

#endif
