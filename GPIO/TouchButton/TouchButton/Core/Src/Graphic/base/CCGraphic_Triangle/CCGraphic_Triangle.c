#include "Graphic/base/CCGraphic_Triangle/CCGraphic_Triangle.h"
#include "Graphic/base/CCGraphic_Line/CCGraphic_Line.h"
#include "Graphic/CCGraphic_device_adapter.h"
#include "Graphic/common/CCGraphic_Utils.h"

void CCGraphic_init_triangle(
    CCGraphic_Triangle* triangle, 
    CCGraphic_Point     p1,
    CCGraphic_Point     p2,
    CCGraphic_Point     p3
)
{
    triangle->p1 = p1;
    triangle->p2 = p2;
    triangle->p3 = p3;
}

void CCGraphic_draw_triangle(
    CCDeviceHandler*    handle,
    CCGraphic_Triangle* triangle
)
{
    CCGraphic_Line  line;
    CCGraphic_init_line(&line, triangle->p1, triangle->p2);
    CCGraphic_draw_line(handle, &line);
    handle->operations.update_device_function(handle);
    CCGraphic_init_line(&line, triangle->p2, triangle->p3);
    CCGraphic_draw_line(handle, &line);
    handle->operations.update_device_function(handle);
    CCGraphic_init_line(&line, triangle->p1, triangle->p3);
    CCGraphic_draw_line(handle, &line);
}

static uint8_t __pvt_is_in_triangle(
    int16_t* triangles_x,
    int16_t* triangles_y,
    CCGraphic_Point* p)
{
    uint8_t is_in = 0;
	/*此算法由W. Randolph Franklin提出*/
	/*参考链接：https://wrfranklin.org/Research/Short_Notes/pnpoly.html*/
	for (uint8_t i = 0, j = 2; i < 3; j = i++)
	{
		if (((triangles_y[i] > p->y) != (triangles_y[j] > p->y)) &&
			(p->x < (triangles_x[j] - triangles_x[i]) * 
            (p->y - triangles_y[i]) / (triangles_y[j] - triangles_y[i]) + 
                triangles_x[i]))
		{
			is_in = !is_in;
		}
	}
	return is_in;
}

void CCGraphic_drawfilled_triangle(
    CCDeviceHandler*    handle,
    CCGraphic_Triangle* triangle
)
{
    int16_t triangles_x[] = 
        {triangle->p1.x, triangle->p2.x, triangle->p3.x};

    int16_t triangles_y[] = 
        {triangle->p1.y, triangle->p2.y, triangle->p3.y};

    int16_t minX = find_int16min(triangles_x, 3);
    int16_t minY = find_int16min(triangles_y, 3);

    int16_t maxX = find_int16max(triangles_x, 3);
    int16_t maxY = find_int16max(triangles_y, 3);
    
    CCGraphic_Point p;
    p.x = minX;
    p.y = minY;
    for(int16_t i = minX; i < maxX; i++)
    {
        for(int16_t j = minY; j < maxY; j++)
        {
            p.x = i;
            p.y = j;
            if(__pvt_is_in_triangle(triangles_x, triangles_y, &p))
            {
                CCGraphic_draw_point(handle, &p);
            }
        }
    }

}
