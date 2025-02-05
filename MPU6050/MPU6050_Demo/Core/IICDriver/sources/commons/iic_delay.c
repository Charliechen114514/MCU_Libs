#include "IICDriver/include/common_iic.h"

static uint32_t g_fac_us = 0;            /* us 延时倍乘数 */
static void inline __delay_init()
{
	g_fac_us = HAL_RCC_GetHCLKFreq() / 1000000;   //获取MCU的主频
}

void __soft_iic_delay_us(uint32_t nus)
{
    __delay_init();
	uint32_t ticks;
	uint32_t told,tnow,tcnt = 0;
	uint32_t reload = SysTick->LOAD;    /*LOAD的值*/
	ticks = nus * g_fac_us;             /*需要的节拍数*/

	told = SysTick->VAL;                /*刚进入时的计数器值*/
	while(1)
	{
		tnow = SysTick->VAL;
		if(tnow != told)
		{
			if(tnow < told)
			{
				tcnt += told - tnow; /*注意一下SYSTICK是一个递减的计数器*/ 
			}
			else
			{
				tcnt += reload - tnow + told;
			}
			told = tnow;
			if(tcnt >= ticks)
			{
				break;            /*时间超过/等于要延时的时间，则退出*/
			}
		}
	}
}