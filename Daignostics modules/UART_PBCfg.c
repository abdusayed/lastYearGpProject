
#include"UART_COMM.h"
#ifndef uart_h
#define uart_h
#include "UART.h"
#endif



/* #pragma location = 0x1800 */

const str_UartConfig_t  UartConfig [] = {
	{UART0,
	16000000,
	16,
	115200,
	LENGTH_8BIT ,
	System_clock,
	&RX_Cb,
	&TX_Cb,
	},
	
};
