#include "delay.h"

#ifdef CCSTMF1

#include "stm32f1xx.h"

void delay_us(uint32_t udelay)
{
  uint32_t startval,tickn,delays,wait;
 
  startval = SysTick->VAL;
  tickn = HAL_GetTick();
  delays =udelay * CC_CLK_MHZ; //sysc / 1000 * udelay;
  if(delays > startval)
    {
      while(HAL_GetTick() == tickn)
        {
 
        }
      wait = CC_CLK_MHZ * 1000 + startval - delays;
      while(wait < SysTick->VAL)
        {
 
        }
    }
  else
    {
      wait = startval - delays;
      while(wait < SysTick->VAL && HAL_GetTick() == tickn)
        {
 
        }
    }
}
#else
void delay_us(unsigned long udelay)
{
  volatile long Delay = udelay * CC_CLK_MHZ / 8;//(SystemCoreClock / 8U / 1000000U)
  while (Delay--);
}
#endif