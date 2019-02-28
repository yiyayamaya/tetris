/*
 * @
 */

#include "stm32f10x.h"
#include "stm32_eval.h"
#ifndef __APP_H
#define __APP_H
#ifdef __APP_C
#define  APP_EXT	
#else
#define APP_EXT	extern
#endif
#define LED_TURN 		GPIOF->ODR^=(GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10)
#define LED_ON			GPIOF->ODR|=(GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10)
#define LED_OFF			GPIOF->ODR&=(~(GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10))

 extern __IO int sys_count;
APP_EXT void delay_us(int a);
APP_EXT void delay_ms(int a);
APP_EXT void LedInit(void);
APP_EXT void BoardInit(void);
APP_EXT void SecondHandle(void);
APP_EXT void KeyHandle(void);
#endif
/*
 *	@ End of the file.
 */
