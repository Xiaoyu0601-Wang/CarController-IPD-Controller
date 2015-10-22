#include  "main.h"
#include <mapan.h>

/*****************************************************************/
/*
 *   ������  :		 ipid_init
 *   ����    :       *pid                ����ʽPID�ṹ��ָ��  
 *                   P          ����ϵ��
 *                   I            ����ϵ��
 *                   D          ΢��ϵ��
 *   ����ֵ  : 		 ��
 *   ˵��    ��		 ����ʽPID�ṹ���ʼ��
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
 *   ������  :		 ipid_init
 *   ����    :       *pid                ����ʽPID�ṹ��ָ��  
 *                   P          ����ϵ��
 *                   I            ����ϵ��
 *                   D          ΢��ϵ��
 *   ����ֵ  : 		 ��
 *   ˵��    ��		 ����ʽPID�ṹ���ʼ��
 */
float ipd_calc(ipdObj *ipd, float currentpoint)
{
	float dpointerr,err;
//	float weight;
	err            = ipd->setpoint - currentpoint;          //ƫ��
	dpointerr      = currentpoint - ipd->lastcurrentpoint;  //��ǰ΢��
	ipd->sumerror += err;                                   //����
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
	
	return (ipd->I * ipd->sumerror     //������
					- ipd->P * currentpoint    //������
					- ipd->D * dpointerr);     //΢����
}

/*****************************************************************/
/******************************************File_End**************************************/
//	float derr,err,ierr;

//	err            = ipd->setpoint - currentpoint; ///ƫ��
//	

//	
//	ierr            = ipd->dofb * ipd->setpoint - currentpoint; ///ƫ��
//	ipd->sumerror += err;                          ///����
//	derr           = ipd->dofc * (ipd->setpoint - ipd->lastsetpoint)
//								 - (currentpoint - ipd->lastcurrentpoint);         ///��ǰ΢��
//	ipd->lastsetpoint = ipd->setpoint;
//	ipd->lastcurrentpoint = currentpoint;

//	return (ipd->P * ierr +              ///������
//					ipd->I * ipd->sumerror +    ///������
//					ipd->D * derr);             ///΢����
