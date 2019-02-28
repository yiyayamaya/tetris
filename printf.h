/*
*@	Function 
*/
#ifndef PRINTF_H
#define PRINTF_H
#ifdef PRINTF_C
#define PRI_EXT
#else
#define PRI_EXT	extern 
#endif
#include "stm32f10x.h"
#include <stdarg.h>
PRI_EXT void InitUsart1(void);
PRI_EXT void Printf( const char  *fmt, ... );
#endif
/*
*@		End of the file
*/
