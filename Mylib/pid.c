#include  "main.h"
/*
 *  ������  :	    pid_init 
 *  ����    :	 	*pid         λ��ʽPID�ṹ��ָ��
 *                  setpoint        Ŀ��ֵ
 *					P	     ����ϵ��
 *					I	     ����ϵ��
 *					D	     ΢��ϵ��
 *  ����ֵ  :	 	��
 *  ˵��    :	    λ��ʽPID�ṹ���ʼ��                                       
 */
void pid_init(pidObj *pid, float setpoint,float P,float I,float D)
{
    pid->setpoint   = setpoint;                                                      
    pid->P = P;                                                   
    pid->I = I;                                                     
    pid->D = D;                                                  
    pid->lasterror  = 0;                                                            
    pid->sumerror   = 0;
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
void ipid_init(ipidObj *pid,float P,float I,float D)
{
	pid->P = P;                                                   
	pid->I = I;                                                      
	pid->D = D;                                                   
	pid->lasterror = 0;                                                            
	pid->preverror = 0;                                                           
}
/*
 *   ������   :		 pid_calc
 *   ����     :      *pid                �������õ�λ��ʽPID�ṹ��ָ��
 *                   currentpoint  		 ��ǰ����ֵ
 *   ����ֵ   : 	 ���������
 *   ˵��     ��	 λ��ʽPID���㲿��
 *   �޸�˵�� ��     ΢������ṹ������˥����������С������������ľ������
 */
float pid_calc(pidObj *pid, float currentpoint)
{
	float derr,err;
	err            = pid->setpoint - currentpoint; ///ƫ��
	pid->sumerror += err;                          ///����
	derr           = err - pid->lasterror;         ///��ǰ΢��
	pid->lasterror = err;

	return (pid->P * err +              ///������
					pid->I * pid->sumerror +    ///������
					pid->D * derr);             ///΢����
}

/*
 *   ������   :		 ipid_calc
 *   ����     :      *pid            �������õ�����ʽPID�ṹ��ָ��
 *                   err  		     ��ǰ���ֵ
 *   ����ֵ   : 	 ���������
 *   ˵��     ��	 ����ʽʽPID���㲿��
 *   �޸�˵�� ��     ΢������ṹ������˥����������С������������ľ������
 */
float ipid_calc(ipidObj *pid,float err)
{
	float outdelta;                                                     
	outdelta       = pid->P * (err - pid->lasterror) + 
									pid->I * err +
									pid->D * (err - 2 * pid->lasterror + pid->preverror);	 /*����������*/
	pid->preverror = pid->lasterror;                                        /*e(k-2)*/
	pid->lasterror = err;                                                   /*e(k-1)*/

	return outdelta;                                             /*����˥��*/
}
