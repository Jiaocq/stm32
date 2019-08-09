#include "gpio.h"
#include "main.h"


/**return : 0,1 for releset or press */
int getStartKey()
{

    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(MCU_TEST_START_GPIO_Port, MCU_TEST_START_Pin))
    {
        return 1;
    }
    return 0;
}

/**return 0,1 for closed or open */
int getOpenClosedKey()
{
    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(MCU_MODE_SWITCH_GPIO_Port, MCU_MODE_SWITCH_Pin))
    {
        return 0;
    }
    return 1;

}
