#include "main.h"

lpfObj GyroZLPF;

void LPF_Initial(void)
{
	
	GyroZLPF.Output = 0;
	GyroZLPF.DynamicRange = 700;
}

short int LPF_Calculation(lpfObj *lpf)
{
	short int gap=0; 
	gap = abs(lpf->Output-lpf->Input);
	lpf->DynamicPara = (float)gap/(lpf->DynamicRange);
	lpf->Output = (short int)(lpf->DynamicPara*lpf->Input
									+ (1-lpf->DynamicPara)*lpf->Output);
	return lpf->Output;
}


