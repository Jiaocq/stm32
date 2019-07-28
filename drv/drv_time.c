#include "tim.h"
#include "common.h"

#define TIMMs htim5 // can only use 32bit times TIM2 or TIM5
#define TIMUs htim2

static uint64_t timeMsHigh32b = 0;
static uint64_t timeMsStartSav = 0;

static uint64_t timeUsHigh32b = 0;
static uint64_t timeUsStartSav = 0;

uint64_t TimeMs(void)
{
    return (uint64_t)(timeMsHigh32b | (TIMMs.Instance->CNT));
}

void TimeMsStart()
{
    timeMsStartSav = TimeMs();
}

uint64_t TimeMsStop()
{
    return (TimeMs() - timeMsStartSav);
}

uint64_t TimeUs()
{
    return (uint64_t)(timeUsHigh32b | (TIMUs.Instance->CNT));
}

void TimeUsStart()
{
    timeUsStartSav = TimeUs();
}

uint64_t TimeUsStop()
{
    return (TimeUs() - timeUsStartSav);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    if (htim == (&htim5))
    {
        timeMsHigh32b += (uint64_t)0x100000000;
    }
    if (htim == (&htim2))
    {
        timeUsHigh32b += (uint64_t)0x100000000;
    }
}

void DelayUs(uint64_t us)
{
    TimeUsStart();
    while (us > TimeUsStop())
    {
    }
}
