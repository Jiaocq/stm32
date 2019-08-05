#ifndef _DRV_DAC_H_
#define _DRV_DAC_H_

#include "stm32f4xx_hal.h"

int32_t AD5686Init();
int32_t DAC8568Init();

/**write adc all channel 
 * data : channel value ranged to 0-65535
 */
int32_t WriteAD5686AllCh(uint32_t data);
int32_t WriteDAC8568AllCh(uint32_t data);

/**write adc one channel 
 * ad5686 channel 0-3 for tb HIO ch 8-11(0-11)
 * dac568 channel 0-8 for tb AI ch 0-7(0-7)
 * data : channel value ranged to 0-65535
 */
int32_t WriteAD5686Value(uint32_t channel, uint32_t data);
int32_t WriteDAC8568Value(uint32_t channel, uint32_t data);


#endif