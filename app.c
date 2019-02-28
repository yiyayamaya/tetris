/*
 *	@	File name	:
 *	@	Function	:
 *	@	Author	:
 *	@	Data	:
 *	@	Others	:
 */

#define __APP_C
#include "app.h"
#include "printf.h"
#include "key.h"
#include "RussiaGame.h"
#include "string.h"

static void NVIC_Configuration(void);
static void KeyChangeDeal(void);

/*
 *	@	brief:
 *	@	param:
 *	@	retururn:
 *	@	others:
 */
void  delay_ms(int a)
{
	int i,j;
	for(i=0;i<a;i++)
	for(j=0;j<8083;j++);
}
/*
 *	@	brief:
 *	@	param:
 *	@	retururn:
 *	@	others:
 */
void delay_us(int a)
{
	int i,j;
	for(i=0;i<a;i++)
	for(j=0;j<8;j++);
}
void LedInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  /* Enable the GPIO_LED Clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);		 
  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
}
/*
 *	@	brief:
 *	@	param:
 *	@	retururn:
 *	@	others:
 */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

 
}
/*
 *	@	brief:
 *	@	param:
 *	@	retururn:
 *	@	others:
 */
void BoardInit(void)
{
	SystemInit();
	LedInit();
	NVIC_Configuration();
	InitUsart1();
	KeyInit();
}
extern int score; 
void SecondHandle(void)
{
	static int secondCount=0;
	if(sys_count-secondCount>1000)
	{
		 secondCount=sys_count;
		 if(JugeIconLocal(moveIcon.x,moveIcon.y-1,&moveIcon.icon))
		 {
		 	 Printf("\r\nIcon down a step");
			 ClearIcon(moveIcon.x,moveIcon.y,&moveIcon.icon);
			 moveIcon.y--;
			 LocalIcon(moveIcon.x,moveIcon.y,&moveIcon.icon); 
		 }
		 else
		 {
		 	Printf("\r\nIcon in possition");
		 	DisTabNowRefush();
			BlockRefush();
			
			GetNewMoveIcon();
		 }
		 //Printf("\r\nOne second On");
	}
}
void KeyHandle(void)
{
	int keyFlag;
	keyFlag=ReadKey();
	switch (keyFlag)
	{
	 	case KEY_RIGHT:
			Printf("\r\nRight key down ");
		    if(JugeIconLocal(moveIcon.x+1,moveIcon.y,&moveIcon.icon))
		    {
		 	 ClearIcon(moveIcon.x,moveIcon.y,&moveIcon.icon);
			 moveIcon.x++;
			 LocalIcon(moveIcon.x,moveIcon.y,&moveIcon.icon); 
		    }
			break;
		case KEY_DOWN:
			Printf("\r\nDown key down ");
			if(JugeIconLocal(moveIcon.x,moveIcon.y-1,&moveIcon.icon))
		    {
		 	 ClearIcon(moveIcon.x,moveIcon.y,&moveIcon.icon);
			 moveIcon.y--;
			 LocalIcon(moveIcon.x,moveIcon.y,&moveIcon.icon); 
		    }
			else
		 	{
		 	Printf("\r\nIcon in possition");
		 	DisTabNowRefush();
			BlockRefush();
			GetNewMoveIcon();
		 	}
			break;
		case KEY_LEFT:			
			Printf("\r\nLeft key down ");
			if(JugeIconLocal(moveIcon.x-1,moveIcon.y,&moveIcon.icon))
		    {
		 	 ClearIcon(moveIcon.x,moveIcon.y,&moveIcon.icon);
			 moveIcon.x--;
			 LocalIcon(moveIcon.x,moveIcon.y,&moveIcon.icon); 
		    }
			break;
		case KEY_CHANGE:
			KeyChangeDeal();
			Printf("\r\nChange key down ");
			break;
		default:
			break;
	}
	keyFlag=0;
}
/*
 *
 */
static void KeyChangeDeal(void)
{
	  ICON temp;
	  ChangIcon(&moveIcon.icon,&temp);
	  if(JugeIconLocal(moveIcon.x,moveIcon.y,&temp))
	  {
	  	   ClearIcon(moveIcon.x,moveIcon.y,&moveIcon.icon);
		   memcpy(&moveIcon.icon,&temp,sizeof(ICON));
		   LocalIcon(moveIcon.x,moveIcon.y,&moveIcon.icon); 
	  }
}


/*
 *	End of the file.
 */
