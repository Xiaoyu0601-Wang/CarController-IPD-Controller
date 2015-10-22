#ifndef _MAPAN_H_
#define _MAPAN_H_
#include "main.h"

extern volatile unsigned short int MAPAN_FLAG;
extern int SPEED_Test;

#define pi 3.1415926

#define c 50.8//С�����ܳ� mm
#define r 101.4//   //27*128*4/C 

#define RotConst 0.0010358056039219f//0.000065732670637f//0.0037662046036244f//(float)0.00179843298141786/5*3
#define DisConst 0.0076964171876138f    //pi*50.8(mm)/(128*4*27)
#define XDisFix 1//(float)0.96
#define YDisFix 1//(float)0.96  //0.0126278570526582
#define ADisPosFix 1.02448f//(float)0.85
#define ADisNegFix 1//(float)0.85

/*���̼���ṹ��*/
typedef struct _mapanCalcType
{
	float x;
	float y;
  float angle; //������ĽǶ����� ������
  float theta; //������ĽǶ����� �Ƕ���
}mapanCalcType;

/*���̼������ṹ��*/
extern volatile mapanCalcType Speed_Encoder;
extern volatile mapanCalcType Speed;
extern volatile mapanCalcType Total;

extern void MapanTask(void);
extern void Encoder_Clear(void);
#endif
