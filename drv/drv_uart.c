#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "usart.h"
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

#define UART huart5

/*redefine printf to UART */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
PUTCHAR_PROTOTYPE {
    HAL_UART_Transmit(&UART, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
int _write(int file, char *ptr, int len)
{
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++) {
        __io_putchar(*ptr++);
    }
    return len;
}
#endif


/*define debug mythod*/
#define CONSOLEBUF_SIZE 128
static char  log_buf[CONSOLEBUF_SIZE];
void osprintf(const char *fmt, ...)
{
    va_list args;
    uint32_t length;

    va_start(args, fmt);
    length = vsnprintf(log_buf, sizeof(log_buf) - 1, fmt, args);
    if (length > CONSOLEBUF_SIZE - 1)
        length = CONSOLEBUF_SIZE - 1;
    HAL_UART_Transmit(&UART, (uint8_t *)log_buf, length, 1000);
    va_end(args);

}

