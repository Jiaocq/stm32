#include "gpio.h"
#include "stm32f4xx_hal.h"

int getModeValue()
{
    int mode =0;
    if(HAL_GPIO_ReadPin(MCU_MAIN_DITEST_GPIO_Port, MCU_MAIN_DITEST_Pin)){
        mode |= 1;
    }
    if(HAL_GPIO_ReadPin(MCU_MAIN_DOTEST_GPIO_Port, MCU_MAIN_DOTEST_Pin)){
        mode |= 2;
    }
    if(HAL_GPIO_ReadPin(MCU_MAIN_AITEST_GPIO_Port, MCU_MAIN_AITEST_Pin)){
        mode |= 4;
    }
    if(HAL_GPIO_ReadPin(MCU_MAIN_HIOTEST_GPIO_Port,MCU_MAIN_HIOTEST_Pin)){
        mode |= 8;
    }
    return mode;
}