/*
 *	@	File name	:
 *	@	Function	:
 *	@	Author		: 	Mr Qiu,QQ:309284701
 *	@	Data		:
 *	@	Others		:
 */

#ifndef __RUSSIAGAME_H
#define __RUSSIAGAME_H
#ifdef __RUSSIAGAME_C
#define RUSSIA_EXT	
#else
#define RUSSIA_EXT	extern 
#endif
#include "stm32f10x.h"
typedef struct{
	u8 icon_ar[3][3];		//二维数组
}ICON;
typedef struct{
	int IconID;				//指示图标ID0-4
	int x;int y;			//当前的坐标
	ICON icon;				//当前图标
}MoveIcon;


extern __IO int sys_count;
extern MoveIcon moveIcon;

RUSSIA_EXT void RussiaGameInit(void);
RUSSIA_EXT void ScoreRefush(void);
RUSSIA_EXT void DisBlock(int x,int y,int flag);	
RUSSIA_EXT void BlockRefush(void);
RUSSIA_EXT void LocalIcon(int x,int y,ICON *icon);
RUSSIA_EXT int JugeIconLocal(int x,int y,ICON *icon);
RUSSIA_EXT void ClearIcon(int x,int y,ICON *icon); 
RUSSIA_EXT void DisTabNowRefush(void);
RUSSIA_EXT void GetNewMoveIcon(void);
RUSSIA_EXT void ChangIcon(ICON *icon,ICON *icon_ret);
RUSSIA_EXT int ChickDisTable(void);
RUSSIA_EXT void ChicRusiaStatus(void);

#endif
/*
 *	End of the file.
 */
