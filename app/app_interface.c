#include "stm32f4xx_hal.h"
#include "init.h"
#include "drv_time.h"
#include "drv_mode.h"
#include "drv_key.h"

int hw_init()
{
    systemInit();
    return 0;
}

unsigned long long get_time_ms()
{
    return (unsigned long long)TimeMs();
}

int get_test_module_flag()
{
    switch (getModeValue())
    {

    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 4:
        return 3;
    case 8:
        return 4;
    default:
        return -1;
    }
}
/*Continuous trigger */
int get_start_event()
{
    static int state = 0;
    static int lastState = 0;
    static uint64_t startTime = 0;
    static uint64_t keepTime = 0;
    static const uint64_t changeStateTime = 50;
    switch (getStartKey())
    {
    case 0:
        if (0 == lastState)
        {
            keepTime = TimeMs() - startTime;
        }
        else
        {
            startTime = TimeMs();
        }
        lastState = 0;
        if (changeStateTime < keepTime)
        {
            state = 0;
        }
        break;
    case 1:
        if (1 == lastState)
        {
            keepTime = TimeMs() - startTime;
        }
        else
        {
            startTime = TimeMs();
        }
        lastState = 1;
        if (0 == state && changeStateTime < keepTime)
        {
            state = 1;
            return 1;
        }
        break;
    }
 
    return 0;
}

/*
 * set specified module state.
 * The LED of the module should blink by 1/s for IDLE or 5/s for TESTING.
 *
 * input parameters:
 *  module: 1,2,4,8 for DI/DO/AI/HIO respectively.
 *  state : 0,1 for IDLE and TESTING.
 */
void set_module_state(int module, int state)
{
    


}




