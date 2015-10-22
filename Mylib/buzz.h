#ifndef __BUZZ_H__
#define __BUZZ_H__

#define BUZZ GPIO_Pin_13

#define BUZZ_OFF(GPIO_Pin)  GPIO_SetBits(GPIOC,GPIO_Pin)
#define BUZZ_ON(GPIO_Pin)   GPIO_ResetBits(GPIOC,GPIO_Pin)
#define BUZZ_TOGGLE(GPIO_Pin)  GPIOC->ODR ^= GPIO_Pin

void BUZZ_Configuration(void);

#endif 
