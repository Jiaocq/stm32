#ifndef _DRV_TIME_H_
#define _DRV_TIME_H_

uint64_t TimeMs(void);
void TimeMsStart();
uint64_t TimeMsStop();

uint64_t TimeUs();
void TimeUsStart();
uint64_t TimeUsStop();

void DelayUs(uint64_t us);

#endif