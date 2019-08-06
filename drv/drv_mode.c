#include "gpio.h"
#include "main.h"


/**return : key state 0x0-0xf */
int getModeValue()
{
    int mode = 0;
    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(MCU_MAIN_DITEST_GPIO_Port, MCU_MAIN_DITEST_Pin))
    {
        mode |= 1;
    }
    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(MCU_MAIN_DOTEST_GPIO_Port, MCU_MAIN_DOTEST_Pin))
    {
        mode |= 2;
    }
    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(MCU_MAIN_AITEST_GPIO_Port, MCU_MAIN_AITEST_Pin))
    {
        mode |= 4;
    }
    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(MCU_MAIN_HIOTEST_GPIO_Port, MCU_MAIN_HIOTEST_Pin))
    {
        mode |= 8;
    }
    return mode;
}