#include "stdio.h"
#include "stdlib.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "tsensor.h"
#include "remote.h"   


#include "key.h"
#include "exti.h" 
#include "zzz.h" 
//最后修改于12.26 21：05
void copy(int fromarr[16][12],int toarr[16][12]);//声明复制方法
void jiangluo(int thearray[16][12]);
//Lab12

int fangkuai_arr[16][12];	
int cur_fangkuai_arr[16][12];	


int fangkuai_arr_next[16][12];	
int finalarray[16][12]; 
int finalarray_next[16][12]; 

int mycolor=1;


	 struct Fangkuai fangkuai;
 int main(void)
 { 
	u8 key;
	u16 adcx;
	int mode=1;
	 int dead=0;//0没死 1死了
	float temp;
	float temperate;	 
	float temperate2; 
	float temperate3;
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
 	Adc_Init(); 		//ADC初始化	    
	Remote_Init();	
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	EXTIX_Init();		//外部中断初始化 
	
	 
	 
	 
	 
	memset(fangkuai_arr, 0, sizeof(int)*192);
	memset(fangkuai_arr_next, 0, sizeof(int)*192);
	memset(cur_fangkuai_arr, 0, sizeof(int)*192);
	memset(finalarray, 0, sizeof(int)*192);
	memset(finalarray_next, 0, sizeof(int)*192);
	 
	 
	while(1)
	{
		
		
		
	memset(fangkuai_arr, 0, sizeof(int)*192);
	memset(fangkuai_arr_next, 0, sizeof(int)*192);
	memset(cur_fangkuai_arr, 0, sizeof(int)*192);
		
		
		fangkuai.type=1;
		fangkuai.zhizhen_arr=fangkuai_arr;

	  newfangkuai();//随机生成方块
		
	  copy(fangkuai_arr,cur_fangkuai_arr);
	  copy(fangkuai_arr,fangkuai_arr_next);
			
		 
		if(bijiao()==0) //刚初始化的方块与背景冲突 游戏结束
			{dead=1;}
		
		if(dead==1)
		{
			//LCD_ShowString(60,80,200,16,16,"GG");
			break;
		}
		
		
		while(1)
		{
			
			
			
			
			
			
			
			copy(fangkuai_arr,fangkuai_arr_next);
			jiangluo(fangkuai_arr_next);
			
			
			getfinal_next();//得到finalnext final_next=final+fangkuai_next
			
			if(bijiao2()==0) //下一刻方块与背景冲突
			{
			refreshfinal();//final =final+fangkuai
			LCD_Clear(WHITE);
			refresh(finalarray);//刚冲突
			
			xiaochu();//消除底部
			LCD_Clear(WHITE);	
			refresh(finalarray);	//刷新
			//LCD_ShowString(60,50,200,16,16,"zhuang qiang le");//撞墙有两种情况 1.撞背景墙 2.撞屏幕最下面
				break;
			}
			
			else
			{
			jiangluo(fangkuai_arr);
				//LCD_ShowString(60,80,200,16,16,"jiangluoing");
				//delay_ms(20);
			}
			
			LCD_Clear(WHITE);
			refresh(fangkuai.zhizhen_arr);

			refresh(finalarray);
			//printf(finalarray);
			delay_ms(300);//降落速度
		}
		
		
		LED0=!LED0;
		delay_ms(250);
		
		
	}		

		

	
}	



void Draw_Block(int x,int y)
{
	
	int realx=x*20;
	int realy=y*20;
	
	for(int i=realy+1;i<realy+20-1;i++) //此处+1 -1 是为了每块之间有间隔
	{
		
		/*
		switch(mycolor)
		{
			
		
			case 1:POINT_COLOR=BLACK; break;
			case 2:POINT_COLOR=BLUE; break;
			case 3:POINT_COLOR=YELLOW; break;
			case 4:POINT_COLOR=GREEN; break;
			case 5:POINT_COLOR=RED; break;
		}*/
		LCD_DrawLine(realx+1,i,realx+19,i);	
	}
	
		
}
void refresh(int array[16][12])	//刷新函数
{
	for(int y=0;y<16;y=y+1)
	 {
		for(int x=0;x<12;x=x+1)
		{
			if(array[y][x]==1)
				
			{
				
				Draw_Block(x,y);//y是纵坐标 x是横坐标
			
			}
		}
	}
}



void jiangluo(int thearray[16][12])	//降落函数 方块所有点降落一次
{ 
	
	

	for(int y=15;y>=0;y=y-1)
	 {
		for(int x=0;x<12;x=x+1)
		{
			if(thearray[y][x]==1)
				
			{
				if(y+1<=15)
				{
					thearray[y+1][x]=1;
					thearray[y][x]=0;
					
				}
				
			
			}
		}
	}
	 
}










void jiangluo_next()	//降落函数 操作方块一下一时刻 方块所有点降落一次
{ 
	
	//float **pointoffangkuai;//定义二维指针

	for(int y=15;y>=0;y=y-1)
	 {
		for(int x=0;x<12;x=x+1)
		{
			if(fangkuai_arr_next[y][x]==1)
				
			{
				if(y+1<=15)
				{
					fangkuai_arr_next[y+1][x]=1;
					fangkuai_arr_next[y][x]=0;
					
				}
				
			
			}
		}
	}
	 
}






int bijiao()	//bijiao函数 比较方块数组和背景数组是否冲突 冲突返回0 不冲突返回1
{ 
	
	

	for(int y=15;y>=0;y=y-1) //从下至上扫描
	 {
		for(int x=0;x<12;x=x+1)
		{
			if(fangkuai_arr[y][x]+finalarray[y][x]==2)
				
			{
				return 0;
				
			
			}
		}
	}
	 return 1;
}


















void getfinal_next() // final_next=final+fangkuai_next
	
{
	
	for(int y = 0; y< 16; y++) {
		
		
		for(int x=0;x<12;x++)
     { 
		 
		 finalarray_next[y][x]= finalarray[y][x]+fangkuai_arr_next[y][x];
		 
		 
		 }
			
		 }
	
	





}




int bijiao2()	//第二个bijiao函数 扫描所有final_next 与final冲突 或者接触到最下面返回0 不冲突返回1 
{ 
	
	

	for(int y=15;y>=0;y=y-1) //从下至上扫描
	 {
		for(int x=0;x<12;x=x+1)
		{
			if(finalarray_next[y][x]==2)//扫描是否背景冲突
				
			{
				return 0;
				
			
			}
			
			if(fangkuai_arr[15][x]==1)// 扫描是否接触最下面
				
			{
				return 0;
				
			
			}
			
		}
	}
	 return 1;
}



void refreshfinal() // final=final+fangkuai_arr
	
{
	
	for(int y = 0; y< 16; y++) {
		
		
		for(int x=0;x<12;x++)
     { 
		 
		 finalarray[y][x]= finalarray[y][x]+fangkuai_arr[y][x];
		 
		 
		 }
			
		 }
	
	





}






void newfangkuai()
	{
	int suijishu=rand()%19+1;
	mycolor=rand()%5+1;
	fangkuai.type=suijishu;	
		switch(suijishu)
			
		
		{
			case 1://1*4
				
			fangkuai_arr[0][5]=1;
			fangkuai_arr[0][6]=1;
			fangkuai_arr[1][5]=1;
			fangkuai_arr[1][6]=1;
			
			//LCD_ShowString(60,80,200,16,16,"11111");
			delay_ms(300);
			fangkuai.type=1;
			break;
			
			case 2://
				
			
			fangkuai_arr[0][5]=1;
			fangkuai_arr[1][5]=1;
			fangkuai_arr[2][5]=1;
			fangkuai_arr[3][5]=1;			
		
			//LCD_ShowString(60,80,200,16,16,"22222");
			delay_ms(300);
			fangkuai.type=2;
			break;
			case 3:
				
			fangkuai_arr[0][5]=1;
			fangkuai_arr[0][6]=1;
			fangkuai_arr[0][7]=1;
			fangkuai_arr[0][8]=1;
				
			
			
			//LCD_ShowString(60,80,200,16,16,"33333");
			delay_ms(300);
			fangkuai.type=3;
			break;
			case 4:
				
			
			fangkuai_arr[0][6]=1;
			fangkuai_arr[1][5]=1;
			fangkuai_arr[1][6]=1;
			fangkuai_arr[1][7]=1;
			//LCD_ShowString(60,80,200,16,16,"44444");
			delay_ms(300);
			fangkuai.type=4;
			break;
			case 5:
				
			
			fangkuai_arr[0][6]=1;
			fangkuai_arr[1][6]=1;
			fangkuai_arr[2][6]=1;
			fangkuai_arr[1][7]=1;
			//LCD_ShowString(60,80,200,16,16,"5555");
			delay_ms(300);
			fangkuai.type=5;
			break;
			
			
			
			case 6:
				
			
			fangkuai_arr[0][5]=1;
			fangkuai_arr[0][6]=1;
			fangkuai_arr[0][7]=1;
			fangkuai_arr[1][6]=1;
			//LCD_ShowString(60,80,200,16,16,"6666");
			delay_ms(300);
			fangkuai.type=6;
			break;
			
			
			case 7:
				
			
			fangkuai_arr[0][6]=1;
			fangkuai_arr[1][6]=1;
			fangkuai_arr[2][6]=1;
			fangkuai_arr[1][5]=1;
			//LCD_ShowString(60,80,200,16,16,"7777");
			delay_ms(300);
			fangkuai.type=7;
			break;
			
			case 8:
				
			
			fangkuai_arr[0][5]=1;
			fangkuai_arr[0][6]=1;
			fangkuai_arr[1][6]=1;
			fangkuai_arr[1][7]=1;
			//LCD_ShowString(60,80,200,16,16,"8888");
			delay_ms(300);
			fangkuai.type=8;
			break;
			
			
			case 9:
				
			
			fangkuai_arr[0][6]=1;
			fangkuai_arr[1][5]=1;
			fangkuai_arr[1][6]=1;
			fangkuai_arr[2][5]=1;
			//LCD_ShowString(60,80,200,16,16,"999");
			delay_ms(300);
			fangkuai.type=9;
			break;
			
			case 10:
				
			
			fangkuai_arr[0][6]=1;
			fangkuai_arr[0][7]=1;
			fangkuai_arr[1][5]=1;
			fangkuai_arr[1][6]=1;
			//LCD_ShowString(60,80,200,16,16,"101010");
			delay_ms(300);
			fangkuai.type=10;
			break;
			
			case 11:
				
			
			fangkuai_arr[0][5]=1;
			fangkuai_arr[1][5]=1;
			fangkuai_arr[1][6]=1;
			fangkuai_arr[2][6]=1;
			//LCD_ShowString(60,80,200,16,16,"eleven");
			delay_ms(300);
			fangkuai.type=11;
			break;
			
			case 12:
				
			
			fangkuai_arr[0][5]=1;
			fangkuai_arr[1][5]=1;
			fangkuai_arr[2][5]=1;
			fangkuai_arr[2][6]=1;
			//LCD_ShowString(60,80,200,16,16,"1212");
			delay_ms(300);
			fangkuai.type=12;
			break;
			
			
			case 13:
				
			
			fangkuai_arr[0][5]=1;
			fangkuai_arr[0][6]=1;
			fangkuai_arr[0][7]=1;
			fangkuai_arr[1][5]=1;
			//LCD_ShowString(60,80,200,16,16,"1313");
			delay_ms(300);
			fangkuai.type=13;
			break;
			
			
			
			
			case 14:
				
			
			fangkuai_arr[0][5]=1;
			fangkuai_arr[0][6]=1;
			fangkuai_arr[1][6]=1;
			fangkuai_arr[2][6]=1;
			//LCD_ShowString(60,80,200,16,16,"14");
			delay_ms(300);
			fangkuai.type=14;
			break;
			
			
			case 15:
				
			
			fangkuai_arr[0][7]=1;
			fangkuai_arr[1][5]=1;
			fangkuai_arr[1][6]=1;
			fangkuai_arr[1][7]=1;
			//LCD_ShowString(60,80,200,16,16,"15");
			delay_ms(300);
			fangkuai.type=15;
			break;
			
			
			case 16:
				
			
			fangkuai_arr[0][6]=1;
			fangkuai_arr[1][6]=1;
			fangkuai_arr[2][6]=1;
			fangkuai_arr[2][5]=1;
			//LCD_ShowString(60,80,200,16,16,"16");
			delay_ms(300);
			fangkuai.type=16;
			break;
			
			
			case 17:
				
			
			fangkuai_arr[0][5]=1;
			fangkuai_arr[1][5]=1;
			fangkuai_arr[1][6]=1;
			fangkuai_arr[1][7]=1;
			//LCD_ShowString(60,80,200,16,16,"17");
			delay_ms(300);
			fangkuai.type=17;
			break;
			
			
			case 18:
				
			
			fangkuai_arr[0][5]=1;
			fangkuai_arr[1][5]=1;
			fangkuai_arr[2][5]=1;
			fangkuai_arr[0][6]=1;
			//LCD_ShowString(60,80,200,16,16,"18");
			delay_ms(300);
			fangkuai.type=18;
			break;
			
			
			case 19:
				
			
			fangkuai_arr[0][5]=1;
			fangkuai_arr[0][6]=1;
			fangkuai_arr[0][7]=1;
			fangkuai_arr[1][7]=1;
			//LCD_ShowString(60,80,200,16,16,"19");
			delay_ms(300);
			fangkuai.type=19;
			break;
			
			
			
			
			
		}
		


}

void xiaochu()//消除 
{
	int numofy=15;//从第十五层开始检测
	while(numofy>=0)	
	{	
	int count =0;
	
	for(int i=0;i<12;i++)
			{
				if(finalarray[numofy][i]!=0)
				{
				count=count+1;
				}				
			}										
	if(count==12)
	{
	
		
		for(int i=0;i<12;i++)
			{finalarray[numofy][i]=0;}//最下面清空
		
		
			
			
			for(int y=numofy-1;y>=0;y=y-1)//满的那排以上整体下降
	 {
		for(int x=0;x<12;x=x+1)
		{
			if(finalarray[y][x]==1)
				
			{
				
					finalarray[y+1][x]=1;
					finalarray[y][x]=0;
					
				
				
			
			}
		}
	}
			
				
			
		count=0;
	delay_ms(300);
	}
	
	else
	{
	numofy=numofy-1;
	
	}
	
	
	
}//end while
	
}




void copy(int fromarr[16][12],int toarr[16][12]) //to=from;
{

		
	
		
    for (int y =0;y<16;y++)

    {
        for(int x=0;x<12;x++)
        {
				
            toarr[y][x]=fromarr[y][x];
				
        }
    }
	
   
}



