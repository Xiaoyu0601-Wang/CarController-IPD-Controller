#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

typedef struct _TRAJECTORY
{
	float Xa0;   //�趨Ŀ��
	float Xa1;   //�������� p 
	float Xa2;   //���ֳ��� I 
	float Xa3;   //΢�ֳ��� D 
	float XTf;
	float XTf2;
	float XTf3;
	float Xt;
	float XInitial;
	float XFinal;

	float Ya0;   //�趨Ŀ��
	float Ya1;   //�������� p 
	float Ya2;   //���ֳ��� I 
	float Ya3;   //΢�ֳ��� D 
	float YTf;
	float YTf2;
	float YTf3;
	float YInitial;
	float YFinal;
	
	float Aa0;   //�趨Ŀ��
	float Aa1;   //�������� p 
	float Aa2;   //���ֳ��� I 
	float Aa3;   //΢�ֳ��� D 
	float ATf;
	float ATf2;
	float ATf3;
	float AInitial;
	float AFinal;
	
	float flag;
}trajectoryObj;

extern float theta;
extern unsigned char TrackFLAG;

extern void CircleTracking(void);
extern void SquareTracking(void);
extern void GoBack(void);
extern void SignalTracking(void);

#endif
