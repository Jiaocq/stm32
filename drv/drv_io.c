/**for mc74 */
#include "drv_time.h"
#include "drv_uart.h"
#include "drv_io.h"
#include "main.h"
#include "drv_time.h"

/** set all of leds to off  */
void LEDInit()
{
    /**change a led state  */
    HAL_GPIO_WritePin(MCU_1_POINT_LED_D_GPIO_Port, MCU_1_POINT_LED_D_Pin, 0);
    HAL_GPIO_WritePin(MCU_MAIN_EN_POINT_LED_GPIO_Port, MCU_MAIN_EN_POINT_LED_Pin, 0);
    HAL_GPIO_WritePin(MCU_TB_EN_POINT_LED_GPIO_Port, MCU_TB_EN_POINT_LED_Pin, 0);
    /**enable le */
    HAL_GPIO_WritePin(MCU_DIC1_EN_POINT_LED_GPIO_Port, MCU_DIC1_EN_POINT_LED_Pin, 0);
    HAL_GPIO_WritePin(MCU_DIC2_EN_POINT_LED_GPIO_Port, MCU_DIC2_EN_POINT_LED_Pin, 0);
    HAL_GPIO_WritePin(MCU_DOC1_EN_POINT_LED_GPIO_Port, MCU_DOC1_EN_POINT_LED_Pin, 0);
    HAL_GPIO_WritePin(MCU_DOC2_EN_POINT_LED_GPIO_Port, MCU_DOC2_EN_POINT_LED_Pin, 0);
    HAL_GPIO_WritePin(MCU_AIC_EN_POINT_LED_GPIO_Port, MCU_AIC_EN_POINT_LED_Pin, 0);
    HAL_GPIO_WritePin(MCU_HIOC1_EN_POINT_LED_GPIO_Port, MCU_HIOC1_EN_POINT_LED_Pin, 0);
    HAL_GPIO_WritePin(MCU_HIOC2_EN_POINT_LED_GPIO_Port, MCU_HIOC2_EN_POINT_LED_Pin, 0);
    /**let all led off */
    for (uint8_t pins = 8; pins--;)
    {
        HAL_GPIO_WritePin(MCU_1_POINT_LED_A0_GPIO_Port, MCU_1_POINT_LED_A0_Pin, pins & 0x1UL << 0);
        HAL_GPIO_WritePin(MCU_1_POINT_LED_A1_GPIO_Port, MCU_1_POINT_LED_A1_Pin, pins & 0x1UL << 1);
        HAL_GPIO_WritePin(MCU_1_POINT_LED_A2_GPIO_Port, MCU_1_POINT_LED_A2_Pin, pins & 0x1UL << 2);
        DelayUs(2);
    }
    /**disable le */
    HAL_GPIO_WritePin(MCU_MAIN_EN_POINT_LED_GPIO_Port, MCU_MAIN_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_TB_EN_POINT_LED_GPIO_Port, MCU_TB_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_DIC1_EN_POINT_LED_GPIO_Port, MCU_DIC1_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_DIC2_EN_POINT_LED_GPIO_Port, MCU_DIC2_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_DOC1_EN_POINT_LED_GPIO_Port, MCU_DOC1_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_DOC2_EN_POINT_LED_GPIO_Port, MCU_DOC2_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_AIC_EN_POINT_LED_GPIO_Port, MCU_AIC_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_HIOC1_EN_POINT_LED_GPIO_Port, MCU_HIOC1_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_HIOC2_EN_POINT_LED_GPIO_Port, MCU_HIOC2_EN_POINT_LED_Pin, 1);
    /**change state to high */
    HAL_GPIO_WritePin(MCU_1_POINT_LED_D_GPIO_Port, MCU_1_POINT_LED_D_Pin, 1);
    HAL_GPIO_WritePin(MCU_1_POINT_LED_A0_GPIO_Port, MCU_1_POINT_LED_A0_Pin, 1);
    HAL_GPIO_WritePin(MCU_1_POINT_LED_A1_GPIO_Port, MCU_1_POINT_LED_A1_Pin, 1);
    HAL_GPIO_WritePin(MCU_1_POINT_LED_A2_GPIO_Port, MCU_1_POINT_LED_A2_Pin, 1);
    DelayUs(2);
}

/**write a led 
 * ledId
 * ledState : 0 1
 */
void WriteLED(uint32_t ledId, uint8_t ledState)
{
    /**change a led state  */
    HAL_GPIO_WritePin(MCU_1_POINT_LED_D_GPIO_Port, MCU_1_POINT_LED_D_Pin, (0 ^ ledState));
    HAL_GPIO_WritePin(MCU_1_POINT_LED_A0_GPIO_Port, MCU_1_POINT_LED_A0_Pin, ledId & 0x1UL << 0);
    HAL_GPIO_WritePin(MCU_1_POINT_LED_A1_GPIO_Port, MCU_1_POINT_LED_A1_Pin, ledId & 0x1UL << 1);
    HAL_GPIO_WritePin(MCU_1_POINT_LED_A2_GPIO_Port, MCU_1_POINT_LED_A2_Pin, ledId & 0x1UL << 2);
    /**enable le */
    HAL_GPIO_WritePin(MCU_MAIN_EN_POINT_LED_GPIO_Port, MCU_MAIN_EN_POINT_LED_Pin, ledId & 0x1UL << 3);
    HAL_GPIO_WritePin(MCU_TB_EN_POINT_LED_GPIO_Port, MCU_TB_EN_POINT_LED_Pin, ledId & 0x1UL << 4);
    HAL_GPIO_WritePin(MCU_DIC1_EN_POINT_LED_GPIO_Port, MCU_DIC1_EN_POINT_LED_Pin, ledId & 0x1UL << 5);
    HAL_GPIO_WritePin(MCU_DIC2_EN_POINT_LED_GPIO_Port, MCU_DIC2_EN_POINT_LED_Pin, ledId & 0x1UL << 6);
    HAL_GPIO_WritePin(MCU_DOC1_EN_POINT_LED_GPIO_Port, MCU_DOC1_EN_POINT_LED_Pin, ledId & 0x1UL << 7);
    HAL_GPIO_WritePin(MCU_DOC2_EN_POINT_LED_GPIO_Port, MCU_DOC2_EN_POINT_LED_Pin, ledId & 0x1UL << 8);
    HAL_GPIO_WritePin(MCU_AIC_EN_POINT_LED_GPIO_Port, MCU_AIC_EN_POINT_LED_Pin, ledId & 0x1UL << 9);
    HAL_GPIO_WritePin(MCU_HIOC1_EN_POINT_LED_GPIO_Port, MCU_HIOC1_EN_POINT_LED_Pin, ledId & 0x1UL << 10);
    HAL_GPIO_WritePin(MCU_HIOC2_EN_POINT_LED_GPIO_Port, MCU_HIOC2_EN_POINT_LED_Pin, ledId & 0x1UL << 11);
    DelayUs(2);
    /**set high all of pins */
    /**disable le */
    HAL_GPIO_WritePin(MCU_MAIN_EN_POINT_LED_GPIO_Port, MCU_MAIN_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_TB_EN_POINT_LED_GPIO_Port, MCU_TB_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_DIC1_EN_POINT_LED_GPIO_Port, MCU_DIC1_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_DIC2_EN_POINT_LED_GPIO_Port, MCU_DIC2_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_DOC1_EN_POINT_LED_GPIO_Port, MCU_DOC1_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_DOC2_EN_POINT_LED_GPIO_Port, MCU_DOC2_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_AIC_EN_POINT_LED_GPIO_Port, MCU_AIC_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_HIOC1_EN_POINT_LED_GPIO_Port, MCU_HIOC1_EN_POINT_LED_Pin, 1);
    HAL_GPIO_WritePin(MCU_HIOC2_EN_POINT_LED_GPIO_Port, MCU_HIOC2_EN_POINT_LED_Pin, 1);
    /**change state to high */
    HAL_GPIO_WritePin(MCU_1_POINT_LED_D_GPIO_Port, MCU_1_POINT_LED_D_Pin, 1);
    HAL_GPIO_WritePin(MCU_1_POINT_LED_A0_GPIO_Port, MCU_1_POINT_LED_A0_Pin, 1);
    HAL_GPIO_WritePin(MCU_1_POINT_LED_A1_GPIO_Port, MCU_1_POINT_LED_A1_Pin, 1);
    HAL_GPIO_WritePin(MCU_1_POINT_LED_A2_GPIO_Port, MCU_1_POINT_LED_A2_Pin, 1);
    DelayUs(2);
}
