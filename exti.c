#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "zzz.h" 
//最后修改于12.26 21：05
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//外部中断 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/01  
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved	  
////////////////////////////////////////////////////////////////////////////////// 	  
 extern int  fangkuai_arr[16][12]; 
 extern int  finalarray[16][12]; 
 extern struct Fangkuai fangkuai;
//外部中断初始化函数
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
		
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟

	  KEY_Init();//初始化按键对应io模式

    //GPIOC.5 中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOA.15	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOA.0	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
 
   	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
}

 
void EXTI0_IRQHandler(void)
{
  delay_ms(10);    //消抖
	if(WK_UP==1)
	{	  
		
		
		int i=0;
		int x1,x2,x3,x4,y1,y2,y3,y4;
		
		
		
		
		
		
		for(int y=0;y<16;y++)
			{
					for(int x=0;x<12;x++)//
							{
							if(fangkuai_arr[y][x]==1)
								{
									i=i+1;
									switch(i)
										{
										case 1:		x1=x;y1=y;break;
										case 2:		x2=x;y2=y;break;
										case 3:		x3=x;y3=y;break;
										case 4:		x4=x;y4=y;break;
									  }
								}
							}
					}
			
					switch(fangkuai.type)
		{
			
							case 1:
							{
									
									
									fangkuai.type=1;
									break;
							}
							
							
							case 2:
							{
								
									
								if(chongtu3(y1+1,x1-1,y2,x2,y3-1,x3+1,y4-2,x4+2)==1)
								{
										fangkuai_arr[y1][x1]=0;
										fangkuai_arr[y2][x2]=0;
										fangkuai_arr[y3][x3]=0;
										fangkuai_arr[y4][x4]=0;

										fangkuai_arr[y1+1][x1-1]=1;
										fangkuai_arr[y2][x2]=1;
										fangkuai_arr[y3-1][x3+1]=1;
										fangkuai_arr[y4-2][x4+2]=1;
																	
									fangkuai.type=3;
									
								}
								
								break;
							}
							case 3:
							{
								
								
							if(chongtu3(y1-2,x1+1,y2-1,x2,y3,x3-1,y4+1,x4-2)==1)
								{
							fangkuai_arr[y1][x1]=0;
							fangkuai_arr[y2][x2]=0;
							fangkuai_arr[y3][x3]=0;
							fangkuai_arr[y4][x4]=0;

							fangkuai_arr[y1-2][x1+1]=1;
							fangkuai_arr[y2-1][x2]=1;
							fangkuai_arr[y3][x3-1]=1;
							fangkuai_arr[y4+1][x4-2]=1;
									
									fangkuai.type=2;
								}
									break;
							}
							case 4:
							{
								
								if(chongtu3(y1,x1,y2+1,x2+1,y3,x3,y4,x4)==1)
								{
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y2+1][x2+1]=1;
									
									fangkuai.type=5;
								}
									break;
							}
							case 5:
							{
								
								if(chongtu3(y1+1,x1-1,y2,x2,y3,x3,y4,x4)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y1+1][x1-1]=1;
																		
									
									fangkuai.type=6;
								}
									break;
							}
							case 6:
							{
								if(chongtu3(y1,x1,y2,x2,y3-1,x3-1,y4,x4)==1)
								{
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y3-1][x3-1]=1;
									
									fangkuai.type=7;
								}
									break;
							}
							case 7:
							{
								
								if(chongtu3(y1,x1,y2,x2,y3,x3,y4-1,x4+1)==1)
								{
									fangkuai_arr[y4][x4]=0;
									fangkuai_arr[y4-1][x4+1]=1;
									
									fangkuai.type=4;
								}
									break;
							}
							case 8:
							{
								if(chongtu3(y1-1,x1+1,y2,x2,y3-1,x3-1,y4,x4-2)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1-1][x1+1]=1;
									fangkuai_arr[y2][x2]=1;
									fangkuai_arr[y3-1][x3-1]=1;
									fangkuai_arr[y4][x4-2]=1;
									
									fangkuai.type=9;
								}
									break;
							}
							case 9:
							{
								
								if(chongtu3(y1+1,x1-1,y2+1,x2+1,y3,x3,y4,x4+2)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1+1][x1-1]=1;
									fangkuai_arr[y2+1][x2+1]=1;
									fangkuai_arr[y3][x3]=1;
									fangkuai_arr[y4][x4+2]=1;
									fangkuai.type=8;
								}
									break;
									
							}
							case 10:
							{
								
								if(chongtu3(y1,x1,y2+1,x2-1,y3,x3+2,y4+1,x4+1)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1][x1]=1;
									fangkuai_arr[y2+1][x2-1]=1;
									fangkuai_arr[y3][x3+2]=1;
									fangkuai_arr[y4+1][x4+1]=1;
									fangkuai.type=11;
								}
									break;
							}
							case 11:
							{
								
								if(chongtu3(y1+1,x1+1,y2,x2,y3+1,x3-1,y4,x4-2)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1+1][x1+1]=1;
									fangkuai_arr[y2][x2]=1;
									fangkuai_arr[y3+1][x3-1]=1;
									fangkuai_arr[y4][x4-2]=1;

									
									fangkuai.type=10;
								}
									break;
							}
							case 12://6.1开始
							{
								if(chongtu3(y1+1,x1+1,y2,x2,y3-1,x3-1,y4,x4-2)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1+1][x1+1]=1;
									fangkuai_arr[y2][x2]=1;
									fangkuai_arr[y3-1][x3-1]=1;
									fangkuai_arr[y4][x4-2]=1;
									fangkuai.type=13;
								}
									break;
							}
							case 13:
							{
								if(chongtu3(y1-1,x1+1,y2,x2,y3+1,x3-1,y4-2,x4)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1-1][x1+1]=1;
									fangkuai_arr[y2][x2]=1;
									fangkuai_arr[y3+1][x3-1]=1;
									fangkuai_arr[y4-2][x4]=1;

									fangkuai.type=14;
								}
									break;
							}
							case 14:
							{
								if(chongtu3(y1,x1+2,y2+1,x2+1,y3,x3,y4-1,x4-1)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1][x1+2]=1;
									fangkuai_arr[y2+1][x2+1]=1;
									fangkuai_arr[y3][x3]=1;
									fangkuai_arr[y4-1][x4-1]=1;
									
									fangkuai.type=15;
								}
									break;
							}
							case 15:
							{
								if(chongtu3(y1+2,x1,y2-1,x2+2,y3,x3,y4+1,x4-1)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1+2][x1]=1;
									fangkuai_arr[y2-1][x2+1]=1;
									fangkuai_arr[y3][x3]=1;
									fangkuai_arr[y4+1][x4-1]=1;									
									
									fangkuai.type=12;
								}
									break;
							}
							
							case 16:
							{
								if(chongtu3(y1+1,x1+1,y2,x2,y3-2,x3,y4-1,x4-1)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1+1][x1+1]=1;
									fangkuai_arr[y2][x2]=1;
									fangkuai_arr[y3-2][x3]=1;
									fangkuai_arr[y4-1][x4-1]=1;						
									
									
									fangkuai.type=17;
								}
									break;
							}
							
							
							case 17:
							{
								
								if(chongtu3(y1,x1+1,y2-1,x2+2,y3,x3,y4+1,x4-1)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1][x1+1]=1;
									fangkuai_arr[y2-1][x2+2]=1;
									fangkuai_arr[y3][x3]=1;
									fangkuai_arr[y4+1][x4-1]=1;							
									
									fangkuai.type=18;
								}
									break;
							}
							
							
							case 18:
							{
								if(chongtu3(y1+1,x1+1,y2+2,x2,y3,x3,y4-1,x4-1)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1+1][x1+1]=1;
									fangkuai_arr[y2+2][x2]=1;
									fangkuai_arr[y3][x3]=1;
									fangkuai_arr[y4-1][x4-1]=1;
									fangkuai.type=19;
								}
									break;
							}
							
							case 19:
							{
								if(chongtu3(y1-1,x1+1,y2,x2,y3+1,x3-1,y4,x4-2)==1)
								{
									fangkuai_arr[y1][x1]=0;
									fangkuai_arr[y2][x2]=0;
									fangkuai_arr[y3][x3]=0;
									fangkuai_arr[y4][x4]=0;

									fangkuai_arr[y1-1][x1+1]=1;
									fangkuai_arr[y2][x2]=1;
									fangkuai_arr[y3+1][x3-1]=1;
									fangkuai_arr[y4][x4-2]=1;							
									
									fangkuai.type=16;
								}
									break;
							}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
				
		}
		
	}
	 
	
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}



void EXTI9_5_IRQHandler(void)//右移 mode设为1
{		
	u16 led0pwmval=0;	
	delay_ms(10);   //消抖			 
	if(KEY0==0)	{
		
		if(chongtu2(1)==1)
		{
		
			for(int y=0;y<16;y++)
			{
					for(int x=12;x>=0;x--)//从右向左遍历
							{
							if(fangkuai_arr[y][x]==1)
								{
									fangkuai_arr[y][x+1]=1;
									fangkuai_arr[y][x]=0;
								}
							}
					}
		
			}
	}
 	 EXTI_ClearITPendingBit(EXTI_Line5);    //清除LINE5上的中断标志位  
}


void EXTI15_10_IRQHandler(void)//左移  mode设为-1
{
  delay_ms(10);    //消抖			 
  if(KEY1==0)	{
		
		if(chongtu2(-1)==1)
		{	
			for(int y=0;y<16;y++)
			{
				for(int x=0;x<12;x++)//从左向右遍历
							{
							if(fangkuai_arr[y][x]==1)
								{
									fangkuai_arr[y][x-1]=1;
									fangkuai_arr[y][x]=0;
								}
							}
			}
		}
	}
	 EXTI_ClearITPendingBit(EXTI_Line15);  //清除LINE15线路挂起位
}




int chongtu2(int mode)//mode：-1 左移动；1右移动  判断是否可以移动
	
{

	for(int y=0;y<16;y++)
		{
			for(int x=0;x<12;x++)
						{
						if(fangkuai_arr[y][x]==1)//遍历方块的每个点
							{
								if(finalarray[y][x+mode]==1||x+mode<0||x+mode>11)//和背景或出界 有冲突
								{
									return 0;//冲突返回0
								}
								
								
								
							}
						}
						
						
				}
	
	
		return 1;//不冲突 可以移动
	
	
	
}









int chongtu3(int ny1,int nx1,int ny2,int nx2,int ny3,int nx3,int ny4,int nx4)//  判断是否可以旋转  返回1可以 返回0不可以
	
{

		if(finalarray[ny1][nx1]==0&&ny1>=0&&ny1<=15&&nx1>=0&&nx1<=11)
		{
		
			if(finalarray[ny2][nx2]==0&&ny2>=0&&ny2<=15&&nx2>=0&&nx2<=11)
			{
				if(finalarray[ny3][nx3]==0&&ny3>=0&&ny3<=15&&nx3>=0&&nx3<=11)
				{
						if(finalarray[ny4][nx4]==0&&ny4>=0&&ny4<=15&&nx4>=0&&nx4<=11)
						{
						return 1;
						
						}
				
				}
			
			}
		
		
		}
		
		
		
		return 0;
	
			

	
	
	
}
