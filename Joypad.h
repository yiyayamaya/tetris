#ifndef __JOYPAD_H__
#define __JOYPAD_H__

#include "sys.h"

#define JOYPAD_LAT 	PCout(8)
#define JOYPAD_CLK 	PCout(12)
#define JOYPAD_DAT	PCin(9)

void Joypad_Init(void);
u8 Joypad_Read(void);

#endif
