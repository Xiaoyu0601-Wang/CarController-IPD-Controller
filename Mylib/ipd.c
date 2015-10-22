#include  "main.h"
#include <mapan.h>

/*****************************************************************/
/*
 *   函数名  :		 ipid_init
 *   参数    :       *pid                增量式PID结构体指针  
 *                   P          比例系数
 *                   I            积分系数
 *                   D          微分系数
 *   返回值  : 		 无
 *   说明    ：		 增量式PID结构体初始化
 */
void ipd_init(ipdObj *ipd, float setpoint, float I, float P, float D)
{
	ipd->I = I;
	ipd->P = P;
	ipd->D = D;
	ipd->setpoint = setpoint;
	ipd->sumerror = 0;
	ipd->lastcurrentpoint = 0;
}
/*****************************************************************/
/*
 *   函数名  :		 ipid_init
 *   参数    :       *pid                增量式PID结构体指针  
 *                   P          比例系数
 *                   I            积分系数
 *                   D          微分系数
 *   返回值  : 		 无
 *   说明    ：		 增量式PID结构体初始化
 */
float ipd_calc(ipdObj *ipd, float currentpoint)
{
	float dpointerr,err;
//	float weight;
	err            = ipd->setpoint - currentpoint;          //偏差
	dpointerr      = currentpoint - ipd->lastcurrentpoint;  //当前微分
	ipd->sumerror += err;                                   //积分
	ipd->lastcurrentpoint = currentpoint;
//	
//	if(err < 0.1f*ipd->setpoint)
//	{
//		weight = 1;
//	}
//	else if(err < 0.4f*ipd->setpoint)
//			 {
//				 weight = 0.98;
//			 }
//			 else if(err < 0.8f*ipd->setpoint)
//						{
//							weight = 1.03;
//						}
//						else {weight = 1.07;}
	
	return (ipd->I * ipd->sumerror     //积分项
					- ipd->P * currentpoint    //比例项
					- ipd->D * dpointerr);     //微分项
}

/*****************************************************************/
/******************************************File_End**************************************/
//	float derr,err,ierr;

//	err            = ipd->setpoint - currentpoint; ///偏差
//	

//	
//	ierr            = ipd->dofb * ipd->setpoint - currentpoint; ///偏差
//	ipd->sumerror += err;                          ///积分
//	derr           = ipd->dofc * (ipd->setpoint - ipd->lastsetpoint)
//								 - (currentpoint - ipd->lastcurrentpoint);         ///当前微分
//	ipd->lastsetpoint = ipd->setpoint;
//	ipd->lastcurrentpoint = currentpoint;

//	return (ipd->P * ierr +              ///比例项
//					ipd->I * ipd->sumerror +    ///积分项
//					ipd->D * derr);             ///微分项
