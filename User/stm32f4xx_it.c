/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/Src/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    26-February-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32f4xx_it.h"
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	//LED_FLAG++;
	//PID_FLAG++;
	//MAPAN_FLAG++;
}
/**
  * @brief  This function handles USB Low Priority or CAN RX0 interrupts 
  *   requests.
  * @param  None
  * @retval : None
  */
void CAN2_RX0_IRQHandler(void)
{
  CAN_RxMessage.StdId=0x00;
  CAN_RxMessage.ExtId=0x00;
  CAN_RxMessage.IDE=0;
  CAN_RxMessage.DLC=0;
  CAN_RxMessage.Data[0]=0x00;
  CAN_RxMessage.Data[1]=0x00;
  CAN_RxMessage.Data[2]=0x00;
  CAN_RxMessage.Data[3]=0x00;
  CAN_RxMessage.Data[4]=0x00;
  CAN_RxMessage.Data[5]=0x00;
  CAN_Receive(CAN2, CAN_FIFO0, &CAN_RxMessage);
  CAN_FLAG = 1;	  		    
}
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */ 
void USART2_IRQHandler(void)
{
	if (BLUETOOTH_RXFLAG == 0)
	{
		BLUETOOTH_RxMessage[BLUETOOTH_RxMessagePosion] = USART_ReceiveData(USART2);
		BLUETOOTH_RxMessagePosion++;		
		if(BLUETOOTH_RxMessage[BLUETOOTH_RxMessagePosion-1] == 0x0D)   //13:"/n"
		{
			BLUETOOTH_RXFLAG = 1;
			BLUETOOTH_RxMessageSize = BLUETOOTH_RxMessagePosion;
			BLUETOOTH_RxMessagePosion = 0;
		}

	}
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)                   //这段是为了避免STM32 USART 第一个字节发不出去的BUG 
	{ 
		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);					     //禁止发缓冲器空中断， 
	}	
	
}
/**
  * @}
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
	IMU_Cal();
	MPU_FLAG = 1;
	TIM_ClearFlag(TIM1,TIM_FLAG_Update);  
}
void TIM2_IRQHandler(void)
{
	MAPAN_FLAG = 1;
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
}
void TIM3_IRQHandler(void)
{
	PID_PFLAG = 1;
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
}
void TIM4_IRQHandler(void)
{
	LED_FLAG = 1;
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);  
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
