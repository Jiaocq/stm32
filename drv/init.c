#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "main.h"

extern void SystemClock_Config(void);

int HardwareInit()
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_TIM5_Init();
    MX_TIM2_Init();
    MX_SPI2_Init();
    MX_SPI3_Init();
    MX_SPI4_Init();
    MX_SPI5_Init();
    MX_UART5_Init();
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim5);
    return 0;
}
