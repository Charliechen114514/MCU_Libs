#include "Graphic/base/CCGraphic_Arc/CCGraphic_Arc.h"
#include <math.h>

void CCGraphic_init_CCGraphic_Arc(
    CCGraphic_Arc*      handle,
    CCGraphic_Point     center,
    PointBaseType       radius,
    int16_t             start_degree,
    int16_t             end_degree  
)
{
    handle->center          = center;
    handle->end_degree      = end_degree;
    handle->start_degree    = start_degree;
    handle->radius          = radius;
}


static uint8_t __pvt_is_in_angle(int16_t x, int16_t y, int16_t start, int16_t end)
{
    int16_t point_angle = (atan2(y, x) / 3.14 * 180);

	// if (start < end)	//起始角度小于终止角度的情况
	// {
	// 	/*如果指定角度在起始终止角度之间，则判定指定点在指定角度*/
	// 	if (point_angle >= start && point_angle <= end)
	// 	{
	// 		return 1;
	// 	}
	// }
	// else			//起始角度大于于终止角度的情况
	// {
	// 	/*如果指定角度大于起始角度或者小于终止角度，则判定指定点在指定角度*/
	// 	if (point_angle >= start || point_angle <= end)
	// 	{
	// 		return 1;
	// 	}
	// }
	// return 0;	
    return start < end ?
        (start < point_angle && point_angle < end):
        (start > point_angle || point_angle > end);
}

#define DRAW_OFFSET_POINT(offsetx, offsety) \
    do{\
        point.x = handle->center.x + (offsetx);\
        point.y = handle->center.y + (offsety);\
        CCGraphic_draw_point(handler, &point);\
    }while(0)

#define DRAW_IF_IN(offsetx, offsety) \
    do{\
        if (__pvt_is_in_angle((offsetx), (offsety), start_angle, end_angle))	{\
            DRAW_OFFSET_POINT(offsetx, offsety);\
        }\
    }while(0)   

void CCGraphic_draw_arc(
    CCDeviceHandler* handler,
    CCGraphic_Arc* handle
)
{
	/*此函数借用Bresenham算法画圆的方法*/	
	int16_t x = 0;
	int16_t y = handle->radius;
    int16_t d = 1 - y;

    CCGraphic_Point point;
	const int16_t start_angle = handle->start_degree;
    const int16_t end_angle = handle->end_degree;
	/*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
    DRAW_IF_IN(x, y);
    DRAW_IF_IN(-x, -y);
    DRAW_IF_IN(y, x);
    DRAW_IF_IN(-y, -x);
	
	while (x < y)		//遍历X轴的每个点
	{
		x ++;
		if (d < 0)		//下一个点在当前点东方
		{
			d += 2 * x + 1;
		}
		else			//下一个点在当前点东南方
		{
			y --;
			d += 2 * (x - y) + 1;
		}
		
		/*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
        DRAW_IF_IN(x, y);
        DRAW_IF_IN(y, x);
        DRAW_IF_IN(-x, -y);
        DRAW_IF_IN(-y, -x);
        DRAW_IF_IN(x, -y);
        DRAW_IF_IN(y, -x);
        DRAW_IF_IN(-x, y);
        DRAW_IF_IN(-y, x);
	}
}

void CCGraphic_drawfilled_arc(
    CCDeviceHandler* handler,
    CCGraphic_Arc* handle
)
{
	/*此函数借用Bresenham算法画圆的方法*/	
	int16_t x = 0;
	int16_t y = handle->radius;
    int16_t d = 1 - y;

    CCGraphic_Point point;
	const int16_t start_angle = handle->start_degree;
    const int16_t end_angle = handle->end_degree;
    point.x = x;
    point.y = y;
	
	/*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
    DRAW_IF_IN(x, y);
    DRAW_IF_IN(-x, -y);
    DRAW_IF_IN(y, x);
    DRAW_IF_IN(-y, -x);

	/*遍历起始点Y坐标*/
	for (int16_t j = -y; j < y; j ++)
	{
		/*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
		DRAW_IF_IN(0, j);
	}
	
	while (x < y)		//遍历X轴的每个点
	{
		x ++;
		if (d < 0)		//下一个点在当前点东方
		{
			d += 2 * x + 1;
		}
		else			//下一个点在当前点东南方
		{
			y --;
			d += 2 * (x - y) + 1;
		}
		
		/*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
        DRAW_IF_IN(x, y);
        DRAW_IF_IN(y, x);
        DRAW_IF_IN(-x, -y);
        DRAW_IF_IN(-y, -x);
        DRAW_IF_IN(x, -y);
        DRAW_IF_IN(y, -x);
        DRAW_IF_IN(-x, y);
        DRAW_IF_IN(-y, x);

		/*遍历中间部分*/
		for (int16_t j = -y; j < y; j ++)
		{
				/*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
			DRAW_IF_IN(x, j);
            DRAW_IF_IN(-x, j);
		}
			
		/*遍历两侧部分*/
		for (int16_t j = -x; j < x; j ++)
		{
			/*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
			DRAW_IF_IN(y, j);
            DRAW_IF_IN(-y, j);
		}
	}
}

#undef DRAW_OFFSET_POINT
#undef DRAW_IF_IN