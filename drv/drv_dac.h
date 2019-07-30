#ifndef _DRV_DAC_H_
#define _DRV_DAC_H_

int32_t WriteAD5686AllCh(uint32_t data);
int32_t WriteDAC8568AllCh(uint32_t data);
int32_t WriteDAC8568Value(uint32_t channel, uint32_t data);
int32_t WriteAD5686Value(uint32_t channel, uint32_t data);
int32_t AD5686Init();
int32_t DAC8568Init();


#endif 