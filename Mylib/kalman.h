#ifndef __KALMAN_H
#define __KALMAN_H

#include "main.h"

typedef struct _KalmanFilterType
{
	float Q;
	float R;
	float Cov;
	float Next_Cov;
	float Kg;
	float LAST_Est;
	float Est; 
}KalmanFilterType;

extern void KalmanFilter_Init(void);

extern float  kalman(float Z_kt);
extern float KalmanFilter(float Z_kt);
extern float simplekalman(float X_ko,float Z_kt);
#endif 
