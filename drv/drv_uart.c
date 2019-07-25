#include "stdio.h"
#include "uart.h"

#define UART huart2


/*redefine printf to UART */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&UART, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
int _write(int file, char *ptr, int len)
{
      int DataIdx;
      for (DataIdx = 0; DataIdx < len;DataIdx++)
     {
           __io_putchar(*ptr++);
     }
      return len;
}
#endif