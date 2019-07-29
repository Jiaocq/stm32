#ifndef _DRV_UART_H_
#define _DRV_UART_H_

void osprintf(const char *fmt, ...);
#define DEBUG osprintf
#define ERROR osprintf

#endif