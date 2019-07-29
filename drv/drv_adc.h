#ifndef _DRV_ADC_H
#define _DRV_ADC_H


int32_t AIAdcInit();
int32_t DIGAdcInit();
int32_t HIOAdcInit();
int32_t AIReadCh(uint32_t channel);
int32_t HIOReadCh(uint32_t channel);
int32_t DIGReadCh(uint32_t channel);




#endif 