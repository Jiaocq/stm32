#ifndef _DRV_ADC_H
#define _DRV_ADC_H

#include "stm32f4xx_hal.h"

int32_t AIAdcInit();
int32_t DIGAdcInit();
int32_t HIOAdcInit();
int32_t AIReadCh(uint8_t channel);
int32_t HIOReadCh(uint8_t channel);
int32_t DIGReadCh(uint8_t channel);

#endif 