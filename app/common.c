#include "stm32f4xx_hal.h"
#include "init.h"
#include "drv_adc.h"
#include "drv_dac.h"
#include "drv_io.h"
#include "drv_key.h"
#include "drv_mode.h"
#include "drv_spiio.h"
#include "drv_time.h"
#include "drv_uart.h"
#include "common.h"

int hw_init()
{
    int ret = 0;
    ret -= HardwareInit();
    ret -= AIAdcInit();
    ret -= DIGAdcInit();
    ret -= HIOAdcInit();
    ret -= AD5686Init();
    ret -= DAC8568Init();
    LEDInit();
    ret -= SpiioDeinit();
    WriteLED(LED5, 1); /**power */
    return ret;
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
    uint8_t blinkState = 0;
    if (state)
        blinkState = (uint8_t)(TimeMs() / (uint64_t)100 % (uint64_t)2);
    else
        blinkState = (uint8_t)(TimeMs() / (uint64_t)500 % (uint64_t)2);
    switch (module)
    {
    case 1:
        WriteLED(LED11, 0);
        WriteLED(LED13, 0);
        WriteLED(LED15, 0);
        WriteLED(LED17, blinkState);
        break;
    case 2:
        WriteLED(LED11, 0);
        WriteLED(LED13, 0);
        WriteLED(LED15, blinkState);
        WriteLED(LED17, 0);
        break;
    case 4:
        WriteLED(LED11, blinkState);
        WriteLED(LED13, 0);
        WriteLED(LED15, 0);
        WriteLED(LED17, 0);
        break;
    case 8:
        WriteLED(LED11, 0);
        WriteLED(LED13, blinkState);
        WriteLED(LED15, 0);
        WriteLED(LED17, 0);
        break;
    default:
        break;
    }
}

/*
 * Set test result for specified module
 * input parameters:
 *  module: 1,2,4,8 for DI/DO/AI/HIO respectively.
 *  result: an int-type array with up to 16 items.
 *
 * The LEDs of the module should follow the definition below.
 *  -1: failed, blink quickly.
 *  0 : testing, turn off
 *  1 : pass, turn on.
 */
void set_module_testing_result(int module, int *result)
{
    uint8_t blinkState = 0;
    switch (*result)
    {
    case 0:
        blinkState = 0;
        break;
    case 1:
        blinkState = 1;
        break;
    case -1:
        blinkState = (uint8_t)(TimeMs() / (uint64_t)50 % (uint64_t)2);
        break;
    default:
        DEBUG("error parameter for set_module_testing_result : *result = %d \r\n", *result);
        return;
    }
    switch (module)
    {
    case 1:
        WriteLED(LED16, blinkState);
        break;
    case 2:
        WriteLED(LED14, blinkState);
        break;
    case 4:
        WriteLED(LED10, blinkState);
        break;
    case 8:
        WriteLED(LED12, blinkState);
        break;
    default:
        DEBUG("error parameter for set_module_testing_result : module = %d \r\n", module);
        break;
    }
}

/*
 * Set normal running indication.
 */
void set_normal_run_flag()
{
    uint8_t blinkState = (uint8_t)(TimeMs() / (uint64_t)500 % (uint64_t)2);

    WriteLED(LED8, blinkState); /**state */
    WriteLED(LED6, 0);          /**err */
}

/*
 * set error indication.
 * error_num: one of ERROR_INIT, ERROR_MODULE, ERROR_TEST_FATAL.
 */
void set_error_indication(int error_num)
{
    uint64_t time = (TimeMs() % (uint64_t)1000);
    uint8_t ledState = 0;
    switch (error_num)
    {
    case ERROR_INIT:
        if (time < 500UL)
            ledState = 1;
        else if (time < 550UL)
            ledState = 0;
        else if (time < 600UL)
            ledState = 1;
        else
            ledState = 0;
        break;
    case ERROR_MODULE:
        if (time < 500UL)
            ledState = 1;
        else if (time < 550UL)
            ledState = 0;
        else if (time < 600UL)
            ledState = 1;
        else if (time < 650UL)
            ledState = 0;
        else if (time < 700UL)
            ledState = 1;
        else
            ledState = 0;
        break;
    case ERROR_TEST_FATAL:
        if (time < 500UL)
            ledState = 1;
        else if (time < 550UL)
            ledState = 0;
        else if (time < 600UL)
            ledState = 1;
        else if (time < 650UL)
            ledState = 0;
        else if (time < 700UL)
            ledState = 1;
        else if (time < 750UL)
            ledState = 0;
        else if (time < 800UL)
            ledState = 1;
        else
            ledState = 0;
        break;
    case ERROR_NONE:
        ledState = 0;
    default:
        break;
    }
    WriteLED(LED6, ledState); /**err */
}

/*
 * Set stimulation for terminal board
 *
 * parameters:
 * tb_type  DI~HIO (1~4)
 * channel  1~16 for DI/DO, 1~8 for AI, 1~12 for HIO
 * value    0,1 for DI/DO,
 */
void set_tb_digital_stimulation(int tb_type, int channel, int value)
{
    switch (tb_type)
    {
    case 1: /**DI */
        WriteDIDOPin(TODI, channel - 1, (uint8_t)value);
        break;
    case 2: /**DO */
        WriteDIDOPin(TODO, channel - 1, (uint8_t)value);
        break;
    case 3: /**AI */
        break;
    case 4: /**HIO */
        if (channel <= 8 && channel >= 1)
            WriteAIHIOPin(TOFROMHIO, channel + 3, (uint8_t)value); /**DI */
        break;
    default:
        DEBUG("error parameter for set_tb_digital_stimulation : tb_type = %d \r\n", tb_type);
        break;
    }
}

/*
 * Get output from terminal board by specified channel
 *
 */
int get_tb_digital_output(int tb_type, int channel)
{
    int value = 0;
    switch (tb_type)
    {
    case 1: /**DI */
        value = ReadDIDOPin(FROMDI, channel - 1);
        break;
    case 2: /**DO */
        value = ReadDIDOPin(FROMDO, channel - 1);
        break;
    case 3: /**AI */
        break;
    case 4: /**HIO */
        if (channel >= 0 && channel <= 4)
            value = ReadAIHIOPin(TOFROMHIO, channel - 1);
        if (channel >= 5 && channel <= 8)
            value = ReadAIHIOPin(FROMHIO, channel - 1);
        break;
    default:
        DEBUG("error parameter for set_tb_digital_stimulation : tb_type = %d \r\n", tb_type);
        break;
    }
    return value;
}
