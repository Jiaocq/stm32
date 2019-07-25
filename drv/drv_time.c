#include "time.h"

void delay_us(uint32_t us){
uint32_t timcount;

    __HAL_TIM_SetCounter(&htim7, 0);
    HAL_TIM_Base_Start_IT(&htim7);
 while(us > (timcount = __HAL_TIM_GetCounter(&htim7)))
 {
     
 }
    HAL_TIM_Base_Stop_IT(&htim7);
    printf("%ld\n",timcount);

}