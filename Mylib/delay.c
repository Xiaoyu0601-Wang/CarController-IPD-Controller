#include "main.h"

void Delay_ms(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=24030; //at 168MHz 24030 is ok
 		while(a--);
	}
}

void Delay_us(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=21;  //at 168MHz 21 is ok,the higher the number the more timing precise
		while(a--);
	}
}
