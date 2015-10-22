#ifndef __LED_H__
#define __LED_H__

#define LED1 GPIO_Pin_0
#define LED2 GPIO_Pin_1
#define LED3 GPIO_Pin_2

#define LED_OFF(GPIO_Pin)  GPIO_SetBits(GPIOC,GPIO_Pin)
#define LED_ON(GPIO_Pin)   GPIO_ResetBits(GPIOC,GPIO_Pin)
#define LED_TOGGLE(GPIO_Pin)  GPIOC->ODR ^= GPIO_Pin

extern volatile unsigned short int LED_FLAG;

void LED_Configuration(void);

#endif 
