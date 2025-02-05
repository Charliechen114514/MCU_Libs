#include "Graphic/device_adapter/CCGraphic_device_oled_adapter.h"
#include "Graphic/CCGraphic_device_adapter.h"


void __register_paintdevice(
    CCDeviceHandler* blank_handler, 
    CCDeviceRawHandle raw_handle, 
    CCDeviceRawHandleConfig config, 
    CCDeviceType type)
{
    blank_handler->handle = raw_handle;
    blank_handler->device_type = type;
    switch(type)
    {
        case OLED_Type:
        {
            blank_handler->operations.init_function = 
                (Initer)init_device_oled;
            blank_handler->operations.clear_device_function =
                clear_device_oled;
            blank_handler->operations.set_pixel_device_function = 
                setpixel_device_oled;
            blank_handler->operations.update_device_function = 
                update_device_oled;
            blank_handler->operations.clearArea_function =
                clear_area_device_oled;
            blank_handler->operations.reverse_device_function =
                reverse_device_oled;
            blank_handler->operations.reverseArea_function = 
                reversearea_device_oled;
            blank_handler->operations.updateArea_function = 
                update_area_device_oled;
            blank_handler->operations.draw_area_device_function =
                draw_area_device_oled;
            blank_handler->operations.property_function = 
                property_fetcher_device_oled;
        }
        break;
    }
    blank_handler->operations.init_function(blank_handler, config);
}

static uint32_t g_fac_us = 0;            /* us 延时倍乘数 */
static void inline __delay_init()
{
	g_fac_us = HAL_RCC_GetHCLKFreq() / 1000000;   //获取MCU的主频
}

static void __soft_iic_delay_us(uint32_t nus)
{
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

void __device_delayclock_enabled()
{
    __delay_init();
}

void __device_usdelay(uint16_t  usec)
{
    __soft_iic_delay_us(usec);
}

void __device_delay(uint16_t    sec)
{
    HAL_Delay(sec);
}