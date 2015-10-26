//#include<stdio.h>
//#include <string.h>
//#include <stdarg.h>
//#include "simple_uart.h"
#include <stdarg.h>
#include <string.h>

#include "sys_main.h"
#define SYS_STRING_BUFFER 128



void sys_UartPutCh(char cr)
{
    NRF_UART0->TXD = (uint8_t)cr;

    while (NRF_UART0->EVENTS_TXDRDY != 1)
    {
        // Wait for TXD data to be sent.
    }

    NRF_UART0->EVENTS_TXDRDY = 0;
}


void sys_UartPutStr(char *ucPt)
{
  while(*ucPt) sys_UartPutCh(*ucPt++);
}

void sys_printf(char *ucFmt,...)
{
   va_list ap;
  

  	char sys_string[SYS_STRING_BUFFER];
	memset(sys_string,0x00,SYS_STRING_BUFFER);

	va_start(ap,ucFmt);
	vsprintf(sys_string,ucFmt,ap);
	sys_UartPutStr(sys_string);

	
	 va_end(ap);
}

