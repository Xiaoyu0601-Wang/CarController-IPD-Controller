#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

typedef struct _TRAJECTORY
{
	float Xa0;   //设定目标
	float Xa1;   //比例常数 p 
	float Xa2;   //积分常数 I 
	float Xa3;   //微分常数 D 
	float XTf;
	float XTf2;
	float XTf3;
	float Xt;
	float XInitial;
	float XFinal;

	float Ya0;   //设定目标
	float Ya1;   //比例常数 p 
	float Ya2;   //积分常数 I 
	float Ya3;   //微分常数 D 
	float YTf;
	float YTf2;
	float YTf3;
	float YInitial;
	float YFinal;
	
	float Aa0;   //设定目标
	float Aa1;   //比例常数 p 
	float Aa2;   //积分常数 I 
	float Aa3;   //微分常数 D 
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
