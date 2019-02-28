/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.1.2
  * @date    09/28/2009
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "printf.h"
#include "app.h"
__IO int sys_count=0;

/** @addtogroup STM32F10x_StdPeriph_Examples
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
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
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
  * @brief  This function handles PendSV_Handler exception.
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

#include "key.h"
__IO int key1_count=0;
__IO int key2_count=0;
__IO int key3_count=0;
__IO int key4_count=0;
void SysTick_Handler(void)
{
	sys_count+=10;
	if(K1())
		key1_count+=10;
	else key1_count=0;

	if(K2())
		key2_count+=10;
	else  key2_count=0;

	if(K3())
		key3_count+=10;
	else  key3_count=10;

	if(K4())
		key4_count+=10;
	else key4_count=0;
}
/*
 *	@brief	: 	Usart 1 interrupt progrom.
 *	@param	:	None
 *	@return	:	None
 *	@others	:
 */
void USART1_IRQHandler(void)
{
  u8 ch;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
  	  ch=USART_ReceiveData(USART1); 
	  USART1->DR = (ch & (uint16_t)0x01FF);
	  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
	  {
	  }
	  USART_ClearFlag(USART1,USART_IT_RXNE);  
  }	   
}
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {

	//Printf("\r\nKey 1 Pressed");
	//LED_TURN;
    /* Clear the Key Button EXTI line pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
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

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
