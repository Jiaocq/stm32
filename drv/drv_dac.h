#ifndef _DRV_DAC_H_
#define _DRV_DAC_H_

int WriteAD5686AllCh(uint32_t data);
int WriteDAC8568AllCh(uint32_t data);
int WriteDAC8568Value(uint32_t channel, uint32_t data);
int WriteAD5686Value(uint32_t channel, uint32_t data);
int AD5686Init();
int DAC8568Init();


#endif 