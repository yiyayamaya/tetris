#ifndef __24Cxx_H__
#define __24Cxx_H__

#include "sys.h"

#define AT24C01 128
#define AT24C02 256
#define AT24C04 512
#define AT24C08 1024
#define AT24C16 2048
#define AT24C32 4096
#define AT24C64 8192
#define AT24C128 16384
#define AT24C256 32768

#define EE_Type AT24C02

void AT24CXX_Init(void);
u8 AT24CXX_Read_One_Byte(u16 ReadAddr);
void AT24CXX_Write_One_Byte(u16 WriteAddr,u8 data);
void AT24CXX_WriteData(u16 WritAddr,u8 *data,u16 len);
void AT24CXX_ReadData(u16 ReadAddr,u8 *ReadBuf,u16 len);
void AT24CXX_WriteLenData(u16 WritAddr,u16 DataToWrite);
u16 AT24CXX_ReadLenData(u16 ReadAddr);
void AT24CXX_ClearData(u16 WritAddr,u16 len);

#endif
