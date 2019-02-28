/*
 *	@File name	:
 *	@Function	:
 *	@Data		:
 *	@Author		:
 *	@Others		:
 */
#define PRINTF_C
#include "printf.h"
#include <stdarg.h>
const u8 Hex[] = "0123456789ABCDEF";
static void _outchar(char ch);
static void DoPrint( const char  *fmt, va_list ap );
/*
 *	@brief	:
 *	@param	:
 *	@return	:
 *	@others	:
 */
void InitUsart1(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|\
						RCC_APB2Periph_USART1, ENABLE);
	/* Configure USARTx_Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USARTx_Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*Config the VCC control pin,and the power control pin*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	/*STATUS Pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	/* Configure the USARTx */ 
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	/* Enable the USARTx */
	USART_Cmd(USART1, ENABLE);
}
/*
 *	@brief	:
 *	@param	:
 *	@return	:
 *	@others	:
 */
static void _outchar(char ch)
{
  /* Write a character to the USART */
  USART_SendData(USART1, (u8) ch);
  /* Loop until the end of transmission */
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {
  }
}
/*
 *	@brief	:
 *	@param	:
 *	@return	:
 *	@others	:
 */
#define KEILC
static void DoPrint( const char  *fmt, va_list ap )
{
	char  ch;
	char  i;
	long  value=0;
	//bit   fl_zero;
	//bit   fl_num;
	u8   fl_zero;
//	u8   fl_num;
	u8  fl_len;
	u8  cnt;
	u32 mask=1;

	#ifdef KEILC
	char *ptr;
	#endif

	while(1) {
		
		//----- Find Formatter % -----

		switch( ch = *fmt++ ) {
			case 0:		return;
			case '%':	if( *fmt != '%' ) break;
						fmt++;
			default:	_outchar( ch );
						continue;
		}

		//----- Get Count -------------
		
		fl_zero = 0;
//		fl_num = 0;
		cnt = 0;

		ch = *fmt++;

		if( ch=='0' ) {
			fl_zero = 1;
			ch = *fmt++;
			cnt = ch - '0';
			ch = *fmt++;
		}
		else if( ch>='0' && ch<='9' ) {
			cnt = ch - '0';
			ch = *fmt++;
		}

		//----- Get char(B) / int / long(L) ----------------

		fl_len = 2;

		switch(ch) {
		case 'l':
		case 'L':	ch = *fmt++;	fl_len = 4;		break;
		case 'b':
		case 'B':	ch = *fmt++;	fl_len = 1;		break;
		}		

		//----- Get Type Discriptor -----
		
		switch( ch ) {

			case 'd':
			case 'u':

				switch (fl_len) {
				case 1:
					if( ch=='d' )
						// value = (char)va_arg( ap, char );
						value = (char)va_arg(ap, int);
					else          
						//value = (u8)va_arg(ap,u8);
						value = (u8)va_arg(ap,unsigned int );
					break;

				case 2:
					if( ch=='d' ) 
						value = (int)va_arg( ap,  int );
					else          
						//value = (u16)va_arg( ap, u16 );
						value = (u16)va_arg( ap, unsigned int );
					break;

				case 4:
					if( ch=='d' ) value = (long)va_arg( ap, long );
					else          value = (u32)va_arg( ap, u32 );
					break;
				}

				if( value<0 ) {
					_outchar('-');
					value = value*(-1);
				}

				if(cnt==0) {
					if( value==0 ) { _outchar('0'); continue; }

					for(cnt=0, mask=1; cnt<10; cnt++) {
						if( (value/mask)==0 ) break;
						mask = mask*10;
					}
				}

				for(i=0, mask=1; i<cnt-1; i++) mask = mask*10;

				while(1) {
					ch = (value / mask) + '0';
					if( ch=='0' && fl_zero==0 && mask!=1 ) ch=' ';
					else fl_zero = 1;
					_outchar(ch);

					value = value % (mask);
					mask = mask / 10;
					
					if( mask==0 )
						break;
				}
				continue;
						  
			case 'x':
			case 'X':

				switch (fl_len) {
				case 1:	
					//value = (u8)va_arg( ap, u8 );		break;
					value = (u8)va_arg( ap, unsigned int );		break;
				case 2:	
					//value = (u16)va_arg( ap, u16 );		break;
					value = (u16)va_arg( ap, int );		break;
				case 4:	value = (u32)va_arg( ap, u32 );		break;
			//	case 8: value=va_arg( ap, unsigned long );		break;
				}


				if(cnt==0) cnt = fl_len*2;

				for(i=0; i<cnt; i++) {
					_outchar( Hex[(value >> (cnt-i-1)*4) & 0x000f] );
				}
				continue;

			case 's':

				#ifdef TASKINGC
				
				value = (u16)va_arg( ap, u16 );
				while(*(char CODE_P *)value!='\0')
					_outchar(*(char CODE_P *)value++);
				continue;

				#elif defined KEILC
				
				ptr = (char *)va_arg( ap, char* );
				while(*ptr!='\0')
					_outchar(*ptr++);
				continue;

				#endif


			case 'c':
				value = va_arg( ap, int );
					_outchar((u8)value);
				continue;

			default:
				value = (u16)va_arg( ap, int );
				continue;
		}
	}
}
/*
 *	@brief	:
 *	@param	:
 *	@return	:
 *	@others	:
 */
void Printf( const char  *fmt, ... )
{
	va_list ap;

	va_start(ap, fmt);
	DoPrint( fmt, ap );
	va_end( ap );
}

/*
*@	End of the file
*/
