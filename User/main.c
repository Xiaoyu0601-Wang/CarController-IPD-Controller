/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/Src/main.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    26-February-2014
  * @brief   This example describes how to configure and use GPIOs through 
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
	
	
int main(void)
{
	while (1);
	/* Configuration */
  SystemInit();
	LED_Configuration();
	BUZZ_Configuration();
	//ADC_Configuration();
	CAN_Configuration();
/****************************µ◊≈Ã≥ı ºªØ******************************/
	Elmo_Init(elmo, 3);
//	PositionPID_Init();
	PositionIPD_Init();
	MoveLock();
	Delay_ms(100);
	BLUETOOTH_Configuration();
	Delay_ms(100);
	Encoder_Clear();
	Delay_ms(1000);
  MPU6500_init();
	TIM1_Configuration();
	TIM2_Configuration();
	TIM3_Configuration();
	TIM4_Configuration();

	if (SysTick_Config(SystemCoreClock / 1000))    /* Setup SysTick Timer for 1 msec interrupts  */
	{
		while(1){LED_ON(LED2);}/* Capture error */
	}
//	IpdAxisX.setpoint = 200;
//	IpdAngle.setpoint = 90;
//	PidAxisX.setpoint = 200;
//	CMDVelocity.X = 10; 
//	CMDVelocity.Y = 0;
//	CMDVelocity.A = 0;//Degree/Second
//  Elmo_Write(&elmo[0],0x01,0x01,50);	
  while (1)
  {	
		if(MPU_FLAG == 1)
		{
			MPU_FLAG = 0;
		}
		if(MAPAN_FLAG == 1)
		{
			MAPAN_FLAG = 0;
//			LED_TOGGLE(LED1);	
			MapanTask();//¬Î≈Ã	
	  }
		if(PID_PFLAG ==1)
		{
			PID_PFLAG = 0;
//			PositionPIDCal();
			PositionIPDCal();
			VelocityTransform();				
//			LED_TOGGLE(LED2);
		}
		if (LED_FLAG == 1)
		{
			LED_FLAG = 0;	
//			SquareTracking();
//			CircleTracking();
//			GoBack();
//			LED_TOGGLE(LED3);
//			SignalTracking();
//			angle_print();
//			PositionVelocity_print();
		}
  }
}


/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
