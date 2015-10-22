#include "main.h"

KalmanFilterType KF_Para = {0.035,0.009,0,0,0,0,0};



#define dt 0.004
float A[2][2]={{1,dt},{0,1}};
float H[2]={1,0};
float X_ko[2]={0,0};
float X_kt[2];
float K_kt[2];
float E_kt;
float P_ko[2][2]={{0.01,0},{0,0.01}};
float P_k[2][2];
float P_kt[2][2];
float Q_ko[2][2]={{0.03,0},{0,0.03}};
//float Q_kt[2][2];
float R_ko=0.045;
//float R_kt;
float  kalman(float Z_kt){
    int n;
    int i;
    int j;
    float buf[2][2]={{0,0},{0,0}};
    float X_k[2];
    float sum=0;

    //X_k//
    for(i=0;i<2;i++){
	     for(j=0;j<2;j++){
		    sum+=A[i][j]*X_ko[j];
	     }
	     X_k[i]=sum;
	     sum=0;
	     }

    //P_k//
    for(n=0;n<2;n++){
        for(i=0;i<2;i++){
  	     for(j=0;j<2;j++){
  		    sum+=A[n][j]*P_ko[j][i];  //A*P_ko
  	     }
  	     buf[n][i]=sum;
  	     sum=0;
  	     }
    }
    for(n=0;n<2;n++){
        for(i=0;i<2;i++){
  	     for(j=0;j<2;j++){
  		    sum+=buf[n][j]*P_ko[i][j];//A*P_ko*A'
  	     }
  	     P_k[n][i]=sum+Q_ko[n][i];  //P_k=A*P_ko*A'+Q
  	     sum=0;
  	     }
    }

  //K_kt//
	for(j=0;j<2;j++){
	   K_kt[j]=P_k[j][0]/(P_k[0][0]+R_ko);
	 }

//P_kt//
	buf[0][0]=1-K_kt[0];
	buf[0][1]=0;
	buf[1][0]=0-K_kt[1];
	buf[1][1]=1;//buf[][]=I-K_kt*H;
    for(n=0;n<2;n++){
        for(i=0;i<2;i++){
  	     for(j=0;j<2;j++){
  		    sum+=buf[n][j]*P_k[j][i];  //(I-K_kt*H)*P_k
  	     }
  	     P_kt[n][i]=sum;
  	     sum=0;
  	     }
    }

//X_kt//
	for(j=0;j<2;j++){
	   X_kt[j]=X_k[j]+K_kt[j]*(Z_kt-X_kt[0]);
	 }


//update//
	for(j=0;j<2;j++){
	  X_ko[j]=X_kt[j];
	}
	for(i=0;i<2;i++){
      for(j=0;j<2;j++){
    	  P_ko[i][j]=P_kt[i][j];
      }
	}
 return X_kt[0];
}


/*
 * kalman.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: michael
 */
/*
 * kalman.cpp
 *
 *  Created on: 2014-4-2
 *      Author: citeace
 */

#define A 1
#define H 1

float P_kol=0.01;
float Q_kol=0.1;//0.035;
float R_kol=0.2;//0.04;
float K_ktl;
float X_kol=0;
float r_kol=0;//.2227437;
float q_kol=0;


void KalmanFilter_Init(void)
{

}

float KalmanFilter(float Z_kt)
{
	float P_kl;
	float P_ktl;

	float X_kl;
	float X_ktl=0;
	//Time Update(Predict)
	X_kl = A*X_kol + q_kol;
	P_kl = A*P_kol*A + KF_Para.Q;
	//Measurement Update(Correct)
	KF_Para.Kg = P_kl*H / (H*P_kl*H + KF_Para.R);
	P_ktl = (1-K_ktl*H) * P_kl;
	X_ktl = X_kl + KF_Para.Kg * (Z_kt-H*X_kl-KF_Para.R);
  //update 
	X_kol = X_ktl;
	P_kol = P_ktl;
	
	return X_ktl;
}

float K=0.5951695f;
float simplekalman(float X_ko,float Z_kt){

 return X_ko+K*(Z_kt-X_ko);
	
}

