#include "stm32f4xx_hal.h"
#include "drv_time.h"
#include "drv_mode.h"


int hw_init()
{
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


int get_start_event()
{
/*
 * get start event
 *
 * return value:
 * 1: start signal arrived
 * 0: no start signal
 */








}