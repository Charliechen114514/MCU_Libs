#include "common.h"

#ifdef CCSTMF1
#include "stm32f1xx.h"
#endif

void createDelayTime(DelayTime* delayTime, int sec, int mili)
{
    delayTime->milisecond = mili;
    delayTime->second = sec;
}

void tidyDelayTime(DelayTime* wait_tidy)
{
    wait_tidy->second += wait_tidy->milisecond / 1000;
    wait_tidy->milisecond = wait_tidy->milisecond % 1000;
}

void systemGlobalDelay(DelayTime* delayTime)
{
    /* first, gain ms delay supported by HAL */
    int real_time = delayTime->second * 1000 + delayTime->milisecond;
    if(real_time < 0) return; // overflow reject
    HAL_Delay(real_time);
}