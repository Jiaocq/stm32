#ifndef _DRV_ADC_H
#define _DRV_ADC_H

#include "stm32f4xx_hal.h"

/**return 0 for no err */
int32_t AIAdcInit();
int32_t DIGAdcInit();
int32_t HIOAdcInit();

/**read ADCs' channels
 * AIReadCh : u88 channel 0-7 for tb AI 0-7(0-7) full voltage
 * DIGReadCh : u91 channel 0-7 for tb AI 0-7(0-7) half voltage
 * HIOReadCh : u111 channel 0-5 for tb HIO 8-9(0-12) full voatage ,8-9 half voltage and 10-11 ao voltage
 * channel : 0-7
 * return 0-65535 or -1 for correct value and err
  */
int32_t AIReadCh(uint8_t channel);
int32_t DIGReadCh(uint8_t channel);
int32_t HIOReadCh(uint8_t channel);

#endif