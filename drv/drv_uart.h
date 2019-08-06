#ifndef _DRV_UART_H_
#define _DRV_UART_H_

#define DEBUG osprintf
#define INFO  osprintf
#define ERROR osprintf
/**out put data to uart */
void osprintf(const char *fmt, ...);

#endif