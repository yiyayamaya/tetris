/*
 *	@	File name	:
 *	@	Function	:
 *	@	Author		: 	Mr Qiu,QQ:309284701
 *	@	Data		:
 *	@	Others		:
 */
#define __RUSSIAGAME_C
#include "RussiaGame.h"
#include "lcd.h"
#include "stdio.h"
#include "string.h"
#include "printf.h"
#include "app.h"
extern const unsigned char gImage_block[800];
extern const unsigned char gImage_block_back[800];
extern const unsigned char gImage_back[153600];
const char IconList[20]={
					1,2,3,1,3,
					4,0,1,2,3,
					2,3,0,1,1,
					1,3,3,2,1};

MoveIcon moveIcon={
	0,
	4,15,
	{{  {1,0,0,},
		{1,0,0,},
		{1,1,0,}	   	//0
	}}
};
//定义全局图标
const ICON globalIcon[5]={
	{{
		{1,0,0,},
		{1,0,0,},
		{1,1,0,}	   	//0
	}},
	{{
		{1,0,0,},
		{1,0,0,},
		{1,0,0,}		//1
	}},
	{{
		{0,0,0,},
		{1,1,0,},
		{1,1,0,}		//2
	}},
	{{
		{0,0,0,},
		{1,0,0,},
		{1,1,0,}		//3
	}},
	{{
		{0,1,0,},
		{0,1,0,},
		{1,1,0,}		//4
	}},
};
#define MAX_X	9
#define MAX_Y	17
/*
	x 0-8
	y 0-16  18
*/
__IO u8 dis_tab_now[19][9]={
	{1,0,0,0,1,0,1,0,0}, 			//0
	{0,1,0,1,1,1,0,0,0},			//1
	{0,0,1,0,0,0,0,0,0},			//2
	{0,0,1,0,0,0,0,0,0},			//3
	{0,0,1,0,0,0,0,0,0},			//4
	{0,0,0,0,0,0,0,0,0},			//5
	{0,0,0,0,0,0,0,0,0},			//6
	{0,0,0,0,0,0,0,0,0},			//7
	{0,0,0,0,0,0,0,0,0},			//8
	{0,0,0,0,0,0,0,0,0},			//9
	{0,0,0,0,0,0,0,0,0},			//10
	{0,0,0,0,0,0,0,0,0},			//11
	{0,0,0,0,0,0,0,0,0},			//12
	{0,0,0,0,0,0,0,0,0},			//13
	{0,0,0,0,0,0,0,0,0},			//14
	{0,0,0,0,0,0,0,0,0},			//15
	{0,0,0,0,0,0,0,0,0},			//16
	{0,0,0,0,0,0,0,0,0},			//17
	{0,0,0,0,0,0,0,0,0},			//18
};	
u8 dis_tab_new[19][9]={
	{0,0,0,0,0,0,0,0,0}, 			//0
	{0,0,0,0,0,0,0,0,0},			//1
	{0,0,0,0,0,0,0,0,0},			//2
	{0,0,0,0,0,0,0,0,0},			//3
	{0,0,0,0,0,0,0,0,0},			//4
	{0,0,0,0,0,0,0,0,0},			//5
	{0,0,0,0,0,0,0,0,0},			//6
	{0,0,0,0,0,0,0,0,0},			//7
	{0,0,0,0,0,0,0,0,0},			//8
	{0,0,0,0,0,0,0,0,0},			//9
	{0,0,0,0,0,0,0,0,0},			//10
	{0,0,0,0,0,0,0,0,0},			//11
	{0,0,0,0,0,0,0,0,0},			//12
	{0,0,0,0,0,0,0,0,0},			//13
	{0,0,0,0,0,0,0,0,0},			//14
	{0,0,0,0,0,0,0,0,0},			//15
	{0,0,0,0,0,0,0,0,0},			//16
	{0,0,0,0,0,0,0,0,0},			//17
	{0,0,0,0,0,0,0,0,0},			//18
};	   
int score=0;   						//分数
void GetNewMoveIcon(void)
{	
	 static int count=0;
	 moveIcon.IconID=IconList[(count++)%20];
	 moveIcon.x=4;
	 moveIcon.y=15;
	 memcpy(&moveIcon.icon,&globalIcon[moveIcon.IconID],sizeof(ICON));
}
void RussiaGameInit(void)
{
	//u8 soureArr[5];
	LCD_Clear(Black);
	LCD_WriteBMPMy(0, 0, 240,320,(u8 *)gImage_back);
	//LCD_WriteBMPMy(40,300, 20,20,(u8 *)gImage_block);
	//DisBlock(0,15,1);
	ScoreRefush();
	BlockRefush();
	memcpy(&moveIcon.icon,&globalIcon[0],sizeof(ICON));
/*	LocalIcon(0,0,(ICON *)&globalIcon[0]);
	LocalIcon(2,0,(ICON *)&globalIcon[1]);
	LocalIcon(4,0,(ICON *)&globalIcon[2]);
	LocalIcon(6,0,(ICON *)&globalIcon[3]);
	LocalIcon(6,5,(ICON *)&globalIcon[4]);
  */
}
void ScoreRefush()
{
	u8 soureArr[5];	 
	sprintf((char *)soureArr,"%03d",score);
	LCD_PutString(186,282,soureArr,0x0000,0xffff);
}
/*
 *	brief	:	display a block in the lcd
 *	param	:	x,0-8;y,0-15，左下为原点	
 */
void DisBlock(int x,int y,int flag)
{
	if(x>8||y>15)  	return ;
	if(flag)
	LCD_WriteBMPMy((x)*20,(y)*20, 20,20,(u8 *)gImage_block);
	else
	LCD_WriteBMPMy((x)*20,(y)*20, 20,20,(u8 *)gImage_block_back);
}
/*
 *
 */
void BlockRefush(void)
{
	int x,y;
	for(x=0;x<9;x++)
	{
		//for(y=18;y>=3;y--)
		for(y=0;y<=15;y++)
		{
			if(dis_tab_now[y][x]==1)
				DisBlock(x,y,1);
			else
				DisBlock(x,y,0);	
		}
	}
}

/*
 *	brief	:	顺时针旋转图标
 * 	param	:	icon,Input icon;icon_ret output icon;
 *	return 	:
 */
void ChangIcon(ICON *icon,ICON *icon_ret)
{
	ICON temp;
	temp.icon_ar[0][0]=icon->icon_ar[2][0];
	temp.icon_ar[0][1]=icon->icon_ar[1][0];
	temp.icon_ar[0][2]=icon->icon_ar[0][0];

	temp.icon_ar[1][0]=icon->icon_ar[2][1];
	temp.icon_ar[1][1]=icon->icon_ar[1][1];
	temp.icon_ar[1][2]=icon->icon_ar[0][1];

	temp.icon_ar[2][0]=icon->icon_ar[2][2];
	temp.icon_ar[2][1]=icon->icon_ar[1][2];
	temp.icon_ar[2][2]=icon->icon_ar[0][2];
	memcpy(icon_ret,&temp,sizeof(ICON));
}
/*
 *	   x,0-8;y,0-15
 *
 */
void LocalIcon(int x,int y,ICON *icon)
{
	 int i,j;
	 for(i=2;i>=0;i--)
	 {
	 	for(j=0;j<3;j++)
		{
			if(icon->icon_ar[i][j])
			{//填充ICON
				DisBlock(x+j,y+i,1);
				//Printf("\r\nOn x+i:%d,y+j:%d",x+i,y+j);
			}
			else						
			{//填充空白
				//DisBlock(x+j,y+2-i,0);
				//Printf("\r\nOFF x+i:%d,y+j:%d",x+i,y+j);
			}
		}
	 }
}

/*
 *	   x,0-8;y,0-15，左下
 *
 */
void ClearIcon(int x,int y,ICON *icon)
{
	 int i,j;
	 for(i=2;i>=0;i--)
	 {
	 	for(j=0;j<3;j++)
		{
			if(icon->icon_ar[i][j])
			{//填充ICON
				DisBlock(x+j,y+i,0);
				//Printf("\r\nOn x+i:%d,y+j:%d",x+i,y+j);
			}
			else						
			{//填充空白
				//DisBlock(x+j,y+2-i,0);
				//Printf("\r\nOFF x+i:%d,y+j:%d",x+i,y+j);
			}
		}
	 }
}
void DisTabNowRefush(void)
{
	//dis_tab_now
	//
	int i,j;
	int posi,posj;
	for(i=2;i>=0;i--)
	{
	 	for(j=0;j<3;j++)
		{
			if(moveIcon.icon.icon_ar[i][j])
			{//填充ICON
				posi=moveIcon.x+j;
				posj=moveIcon.y+i;
				dis_tab_now[posj][posi]=1;
			}	
		}
	 }
	// return 1;
}
/*
 *  x,0-8,y,0-15 ,左下为原点
 */
int JugeIconLocal(int x,int y,ICON *icon)
{//判断该图标能否放下
	int i,j;
	int posi,posj;
	for(i=2;i>=0;i--)
	{
	 	for(j=0;j<3;j++)
		{
			if(icon->icon_ar[i][j])
			{//填充ICON
				posi=x+j;
				posj=y+i;
				if(posj>18||posi>8||posj<0||posi<0||dis_tab_now[posj][posi]==1)
					return 0;
			}	
		}
	 }
	 return 1;
}
static int ChicArr(__IO u8 *buf,u8 dat)
{
	if(*(buf+0)==dat&&*(buf+1)==dat&&*(buf+2)==dat&&\
		*(buf+3)==dat&&*(buf+4)==dat&&*(buf+5)==dat&&\
		*(buf+6)==dat&&*(buf+7)==dat&&*(buf+8)==dat)
		return 1;
	return 0;
}
const u8 compar[9]={1,1,1,1,1,1,1,1,1};
int ChickDisTable(void)	
{
	int i;
	for(i=0;i<18;i++)
	{
		//if(memcmp((const void *)dis_tab_now[i],compar,MAX_X)==0)
		if(ChicArr(dis_tab_now[i],1))
			goto move;
	}
	return 0;
move:
	for(;i<18;i++)
	{
		memcpy((void *)dis_tab_now[i],(const void *)dis_tab_now[i+1],MAX_X);
	}
	return 1;
}
int ChickDisTableAgain(void)
{
	if(ChicArr(dis_tab_now[17],0)!=1||\
	   ChicArr(dis_tab_now[18],0)!=1)
	   return 1;
	else
		return 0;

}
void ChicRusiaStatus(void)
{
	while(ChickDisTable()==1)
	{
		BlockRefush();
		score++;
		ScoreRefush();
		delay_ms(100);
	}
	if(ChickDisTableAgain()==1)
	{ //
	 	Printf("\r\nGeame over");
		LCD_PutString(70,200,"Game Over",0x0000,0xffff);
		while(1);	
	}
}


/*
 *	End of the file.
 */
