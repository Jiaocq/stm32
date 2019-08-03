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

/*
 * Hardware init
 *
 * return value:
 * 0: hardware initi successfully.
 * others: hardware init failed.
 */
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
    WriteLED(LED5, 1); /**power led on*/
    DEBUG("hard init result : %d\r\n",ret);
    return ret;
}

/*
 * Get current time in units of ms
 */
unsigned long long get_time_ms()
{
    return (unsigned long long)TimeMs();
}

/*
 * Get test module indication.
 *
 * return value:
 * 0: no module being selected
 * 1: test DI module
 * 2: test DO module
 * 3: test AI module
 * 4: test HIO module
 * -1: failed to get indication or invalid indication.
 *
 */
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

/*
 * get start event
 *
 * return value:
 * 1: start signal arrived
 * 0: no start signal
 * single trigger 
 * */
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
            keepTime = 0;
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
            keepTime = 0;
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
    uint32_t ledNum = 0;
    blinkState = (uint8_t)(TimeMs() / (uint64_t)50 % (uint64_t)2);
    switch (module)
    {
    case 1:
        for (ledNum = 16; ledNum--;)
        {
            if (ledNum <= 15)
                WriteLED(LEDDI(ledNum), *(result + ledNum) < 0 ? blinkState : *(result + ledNum));
            if (ledNum <= 15)
                WriteLED(LEDDO(ledNum), 0);
            if (ledNum <= 8)
                WriteLED(LEDAI(ledNum), 0);
            if (ledNum <= 12)
                WriteLED(LEDHIO(ledNum), 0);
        }
        break;
    case 2:
        for (ledNum = 16; ledNum--;)
        {
            if (ledNum <= 15)
                WriteLED(LEDDI(ledNum), 0);
            if (ledNum <= 15)
                WriteLED(LEDDO(ledNum), *(result + ledNum) < 0 ? blinkState : *(result + ledNum));
            if (ledNum <= 8)
                WriteLED(LEDAI(ledNum), 0);
            if (ledNum <= 12)
                WriteLED(LEDHIO(ledNum), 0);
        }
        break;
    case 4:
        for (ledNum = 16; ledNum--;)
        {
            if (ledNum <= 15)
                WriteLED(LEDDI(ledNum), 0);
            if (ledNum <= 15)
                WriteLED(LEDDO(ledNum), 0);
            if (ledNum <= 8)
                if(ledNum == 2) 
                    WriteLED(3, *(result + ledNum) < 0 ? blinkState : *(result + ledNum));
                if(ledNum == 2) 
                    WriteLED(2, *(result + ledNum) < 0 ? blinkState : *(result + ledNum));
                else
                    WriteLED(LEDAI(ledNum), *(result + ledNum) < 0 ? blinkState : *(result + ledNum));
            if (ledNum <= 12)
                WriteLED(LEDHIO(ledNum), 0);
        }
        break;
    case 8:
        for (ledNum = 16; ledNum--;)
        {
            if (ledNum <= 15)
                WriteLED(LEDDI(ledNum), 0);
            if (ledNum <= 15)
                WriteLED(LEDDO(ledNum), 0);
            if (ledNum <= 8)
                WriteLED(LEDAI(ledNum), 0);
            if (ledNum <= 12)
                WriteLED(LEDHIO(ledNum), *(result + ledNum) < 0 ? blinkState : *(result + ledNum));
        }
        break;
    default:
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        break;
    }
}

/*
 * Set normal running indication.
 */
void set_normal_run_flag()
{
    uint8_t blinkState = (uint8_t)(TimeMs() / (uint64_t)500 % (uint64_t)2);
    WriteLED(LED7, blinkState); /**state */
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
    case 1:                                                /**DI */
        WriteDIDOPin(TODI, 16 - channel, !(uint8_t)value); /**output 0 will get 1 */
        break;
    case 2: /**DO */
        WriteDIDOPin(TODO, channel - 1, (uint8_t)value);
        break;
    case 3: /**AI */
        break;
    case 4: /**HIO */
        if (channel <= 8 && channel >= 1)
            WriteAIHIOPin(TOFROMHIO, channel + 3, !((uint8_t)value)); /**output 0 will get 1 */
        break;
    default:
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
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
        if (channel >= 1 && channel <= 4)
            value = ReadAIHIOPin(TOFROMHIO, channel - 1);
        if (channel >= 5 && channel <= 8)
            value = ReadAIHIOPin(FROMHIO, 12 - channel);
        break;
    default:
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        break;
    }
    return value;
}

/*
 * Stimulation --> Terminal --> TerminalBoard --> DB50 --> Acquistion
 * Set AI tb stimulation with 2 lines mode.
 * parameters:
 * channel 1~8
 * value   0 disable, 1 enable
 */
void set_tb_ai_2lines_stimulation(int tb_type, int channel, int value)
{
    switch (tb_type)
    {
    case 1: /**DI */
        break;
    case 2: /**DO */
        break;
    case 3: /**AI */
        if (channel >= 1 && channel <= 8)
        {
            WriteAIHIOPin(TOAI, channel - 1, 0);              /**4line manage */
            WriteAIHIOPin(TOAI, channel + 7, (uint8_t)value); /**2lines manage */
        }
        break;
    case 4: /**HIO */
        if (channel >= 9 && channel <= 10)
        {
            WriteAIHIOPin(TOFROMHIO, channel + 3, 0);              /**4line */
            WriteAIHIOPin(TOFROMHIO, channel + 5, (uint8_t)value); /**2line */
        }
        break;
    default:
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        break;
    }
}

/*
 * Set AI tb stimulation by 4 lines mode.
 * parameters:
 *  channel 1~8
 *  value   0~2500, in units of mV
 */
void set_tb_ai_4lines_stimulation(int tb_type, int channel, int value)
{
    switch (tb_type)
    {
    case 1: /**DI */
        break;
    case 2: /**DO */
        break;
    case 3: /**AI */
        if (channel >= 1 && channel <= 8)
        {
            WriteAIHIOPin(TOAI, channel + 7, 0); /**2lines manage */
            WriteAIHIOPin(TOAI, channel - 1, 1); /**4line manage */
            WriteDAC8568Value(channel - 1, (uint32_t)value * 0xffffUL / 2500UL);
        }
        break;
    case 4: /**HIO */
        if (channel >= 9 && channel <= 10)
        {
            WriteAIHIOPin(TOFROMHIO, channel + 5, 0); /**2line */
            WriteAIHIOPin(TOFROMHIO, channel + 3, 1); /**4line */
            WriteAD5686Value(channel - 9, (uint32_t)value * 0xffffUL / 2500UL);
        }
        break;
    default:
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        break;
    }
}

/*
 * Set AI tb stimulation by 4 lines mode.
 * parameters:
 *  channel    1~8
 *  value_A1   voltage at A1 point, in units of mV
 *  value_A2   voltage at A2 point, in units of mV
 */
int get_tb_ai_output(int tb_type, int channel, int *value_A1, int *value_A2)
{
    switch (tb_type)
    {
    case 1: /**DI */
        break;
    case 2: /**DO */
        break;
    case 3: /**AI */
        if (channel >= 1 && channel <= 8)
        {
            *value_A1 = (int)(AIReadCh(channel - 1) * 2500L / 0xffL);
            *value_A2 = (int)(DIGReadCh(channel - 1) * 2500L / 0xffL);
        }
        break;
    case 4: /**HIO */
        if (channel >= 9 && channel <= 10)
        {
            *value_A1 = (int)(HIOReadCh(channel - 9) * 2500L / 0xffL);
            *value_A2 = (int)(HIOReadCh(channel - 7) * 2500L / 0xffL);
        }
        else if (channel >= 11 && channel <= 12)
        {
            *value_A1 = (int)(HIOReadCh(channel - 7) * 2500L / 0xffL);
            *value_A2 = (int)(HIOReadCh(channel - 7) * 2500L / 0xffL);
        }
        break;
    default:
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        break;
    }
    if (*value_A1 < 0 || *value_A2 < 0)
    {
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }
    return 0;
}

/*
 * Stimulation --> DB50 --> TerminalBoard --> Terminal --> Acquistion
 * Set AI tb stimulation by 4 lines mode.
 * parameters:
 *  channel 1~8
 *  value   0~2500, in units of mV
 */
void set_tb_hio_ai_4lines_stimulation(int tb_type, int channel, int value)
{
    switch (tb_type)
    {
    case 1: /**DI */
        break;
    case 2: /**DO */
        break;
    case 3: /**AI */
        break;
    case 4: /**HIO */
        if (channel >= 9 && channel <= 10)
        {
            WriteAIHIOPin(TOFROMHIO, channel + 3, 1); /**4line */
            WriteAIHIOPin(TOFROMHIO, channel + 5, 0); /**2line */
            WriteAD5686Value(channel - 9, (uint32_t)value * 0xffffUL / 2500UL);
        }
        if (channel >= 11 && channel <= 12)
        {
            WriteAD5686Value(channel - 9, (uint32_t)value * 0xffffUL / 2500UL);
        }
        break;
    default:
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        break;
    }
}

/*
 * Set AI tb stimulation by 4 lines mode.
 * parameters:
 *  channel    1~8
 *  value_A1   voltage at A1 point, in units of mV
 *  value_A2   voltage at A2 point, in units of mV
 */
int get_tb_hio_ai_output(int tb_type, int channel, int *value_A1, int *value_A2)
{
    switch (tb_type)
    {
    case 1: /**DI */
        break;
    case 2: /**DO */
        break;
    case 3: /**AI */
        if (channel >= 1 && channel <= 8)
        {
            *value_A1 = (int)(AIReadCh(channel - 1) * 2500L / 0xffL);
            *value_A2 = (int)(DIGReadCh(channel - 1) * 2500L / 0xffL);
        }
        break;
    case 4: /**HIO */
        if (channel >= 9 && channel <= 10)
        {
            *value_A1 = (int)(HIOReadCh(channel - 9) * 2500L / 0xffL);
            *value_A2 = (int)(HIOReadCh(channel - 7) * 2500L / 0xffL);
        }
        else if (channel >= 11 && channel <= 12)
        {
            *value_A1 = (int)(HIOReadCh(channel - 7) * 2500L / 0xffL);
            *value_A2 = (int)(HIOReadCh(channel - 7) * 2500L / 0xffL);
        }
        break;
    default:
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        break;
    }
    if (*value_A1 < 0 || *value_A2 < 0)
    {
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }
    return 0;
}
/*
 * Set HIO-AO tb stimulation by 4 lines mode.
 * parameters:
 *  channel    1~8
 *  value_A1   voltage at A1 point, in units of mV
 *  value_A2   voltage at A2 point, in units of mV
 */
int set_tb_ao_stimulation(int tb_type, int channel, int value)
{
    int ret = 0;
    switch (tb_type)
    {
    case 1: /**DI */
        break;
    case 2: /**DO */
        break;
    case 3: /**AI */
        break;
    case 4: /**HIO */
        if (channel >= 11 && channel <= 12)
        {
            WriteAD5686Value(channel - 9, (uint32_t)value * 0xffffUL / 2500UL);
        }
        break;
    default:
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        break;
    }
    return ret;
}

/*
 * Set AI tb stimulation by 4 lines mode.
 * parameters:
 *  channel    1~8
 *  value_A1   voltage at A1 point, in units of mV
 *  value_A2   voltage at A2 point, in units of mV
 */
int get_tb_ao_output(int tb_type, int channel, int *value)
{
    switch (tb_type)
    {
    case 1: /**DI */
        break;
    case 2: /**DO */
        break;
    case 3: /**AI */
        break;
    case 4: /**HIO */
        if (channel >= 11 && channel <= 12)
        {
            *value = (int)(HIOReadCh(channel - 7) * (int32_t)2500 / (int32_t)0xff);
        }
        break;
    default:
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        break;
    }
    if (*value < 0)
    {
        DEBUG("Error : %s(%d)-<%s> \r\n", __FILE__, __LINE__, __FUNCTION__);
        return -1;
    }
    return 0;
}
