#include "main.h"
float LinearFitting(uint32_t smpl_data){
	float voltage;
	float trnslt=0.000806;
	float a=-3.3705;
	float b=24.5120;
	float c=-68.2864;
	float d=92.4644;
	float e=-65.3627;
	float f=25.0225;
  float distance=0;
  float buf2=0;
  float buf3=0;
  float buf4=0;
  float buf5=0;
	
  voltage = (float)(smpl_data)*trnslt;//translate the value of sampling to real voltage
  buf2 = voltage*voltage;
  buf3 = buf2*voltage;
  buf4 = buf3*voltage;
  buf5 = buf4*voltage;
  distance = a*buf5+b*buf4+c*buf3+d*buf2+e*voltage+f;
  return distance;
	
}
