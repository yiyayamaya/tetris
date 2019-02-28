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
//����޸���12.26 21��05
void copy(int fromarr[16][12],int toarr[16][12]);//�������Ʒ���
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
	 int dead=0;//0û�� 1����
	float temp;
	float temperate;	 
	float temperate2; 
	float temperate3;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();
 	Adc_Init(); 		//ADC��ʼ��	    
	Remote_Init();	
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	EXTIX_Init();		//�ⲿ�жϳ�ʼ�� 
	
	 
	 
	 
	 
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

	  newfangkuai();//������ɷ���
		
	  copy(fangkuai_arr,cur_fangkuai_arr);
	  copy(fangkuai_arr,fangkuai_arr_next);
			
		 
		if(bijiao()==0) //�ճ�ʼ���ķ����뱳����ͻ ��Ϸ����
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
			
			
			getfinal_next();//�õ�finalnext final_next=final+fangkuai_next
			
			if(bijiao2()==0) //��һ�̷����뱳����ͻ
			{
			refreshfinal();//final =final+fangkuai
			LCD_Clear(WHITE);
			refresh(finalarray);//�ճ�ͻ
			
			xiaochu();//�����ײ�
			LCD_Clear(WHITE);	
			refresh(finalarray);	//ˢ��
			//LCD_ShowString(60,50,200,16,16,"zhuang qiang le");//ײǽ��������� 1.ײ����ǽ 2.ײ��Ļ������
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
			delay_ms(300);//�����ٶ�
		}
		
		
		LED0=!LED0;
		delay_ms(250);
		
		
	}		

		

	
}	



void Draw_Block(int x,int y)
{
	
	int realx=x*20;
	int realy=y*20;
	
	for(int i=realy+1;i<realy+20-1;i++) //�˴�+1 -1 ��Ϊ��ÿ��֮���м��
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
void refresh(int array[16][12])	//ˢ�º���
{
	for(int y=0;y<16;y=y+1)
	 {
		for(int x=0;x<12;x=x+1)
		{
			if(array[y][x]==1)
				
			{
				
				Draw_Block(x,y);//y�������� x�Ǻ�����
			
			}
		}
	}
}



void jiangluo(int thearray[16][12])	//���亯�� �������е㽵��һ��
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










void jiangluo_next()	//���亯�� ��������һ��һʱ�� �������е㽵��һ��
{ 
	
	//float **pointoffangkuai;//�����άָ��

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






int bijiao()	//bijiao���� �ȽϷ�������ͱ��������Ƿ��ͻ ��ͻ����0 ����ͻ����1
{ 
	
	

	for(int y=15;y>=0;y=y-1) //��������ɨ��
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




int bijiao2()	//�ڶ���bijiao���� ɨ������final_next ��final��ͻ ���߽Ӵ��������淵��0 ����ͻ����1 
{ 
	
	

	for(int y=15;y>=0;y=y-1) //��������ɨ��
	 {
		for(int x=0;x<12;x=x+1)
		{
			if(finalarray_next[y][x]==2)//ɨ���Ƿ񱳾���ͻ
				
			{
				return 0;
				
			
			}
			
			if(fangkuai_arr[15][x]==1)// ɨ���Ƿ�Ӵ�������
				
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

void xiaochu()//���� 
{
	int numofy=15;//�ӵ�ʮ��㿪ʼ���
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
			{finalarray[numofy][i]=0;}//���������
		
		
			
			
			for(int y=numofy-1;y>=0;y=y-1)//�����������������½�
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



