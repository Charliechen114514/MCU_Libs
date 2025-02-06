#include "Graphic/base/CCGraphic_Ellipse/CCGraphic_Ellipse.h"

void CCGraphic_init_ellipse(
    CCGraphic_Ellipse*          handle, 
    CCGraphic_Point             center,
    PointBaseType               X_Radius,
    PointBaseType               Y_Radius 
)
{
    handle->center = center;
    handle->X_Radius = X_Radius;
    handle->Y_Radius = Y_Radius;
}

#define DRAW_OFFSET_POINT(offsetx, offsety) \
    do{\
        point.x = ellipse->center.x + (offsetx);\
        point.y = ellipse->center.y + (offsety);\
        CCGraphic_draw_point(handler, &point);\
    }while(0)

#define SQUARE(X) ((X) * (X))

void CCGraphic_draw_ellipse(
    CCDeviceHandler* handler,
    CCGraphic_Ellipse* ellipse
)
{
    const int16_t x_radius = ellipse->X_Radius;
    const int16_t y_radius = ellipse->Y_Radius;

    // Bresenham's Ellipse Algorithm to avoid costly floating point calculations
    // Reference: https://blog.csdn.net/myf_666/article/details/128167392

    int16_t x = 0;
    int16_t y = y_radius;
    const int16_t y_radius_square = SQUARE(y_radius);
    const int16_t x_radius_square = SQUARE(x_radius);

    // Initial decision variable for the first region of the ellipse
    float d1 = y_radius_square + x_radius_square * (-y_radius + 0.5);

    // Draw initial points on the ellipse (4 points due to symmetry)
    CCGraphic_Point point;
    DRAW_OFFSET_POINT(x, y);
    DRAW_OFFSET_POINT(-x, -y);
    DRAW_OFFSET_POINT(-x, y);
    DRAW_OFFSET_POINT(x, -y);

    // Draw the middle part of the ellipse (first region)
    while (y_radius_square * (x + 1) < x_radius_square * (y - 0.5)) {
        if (d1 <= 0) {  // Next point is to the east of the current point
            d1 += y_radius_square * (2 * x + 3);
        } else {  // Next point is southeast of the current point
            d1 += y_radius_square * (2 * x + 3) + x_radius_square * (-2 * y + 2);
            y--;
        }
        x++;

        // Draw ellipse arc for each point in the current region
        DRAW_OFFSET_POINT(x, y);
        DRAW_OFFSET_POINT(-x, -y);
        DRAW_OFFSET_POINT(-x, y);
        DRAW_OFFSET_POINT(x, -y);
    }

    // Draw the two sides of the ellipse (second region)
    float d2 = SQUARE(y_radius * (x + 0.5)) + SQUARE(x_radius * (y - 1)) - x_radius_square * y_radius_square;

    while (y > 0) {
        if (d2 <= 0) {  // Next point is to the east of the current point
            d2 += y_radius_square * (2 * x + 2) + x_radius_square * (-2 * y + 3);
            x++;
        } else {  // Next point is southeast of the current point
            d2 += x_radius_square * (-2 * y + 3);
        }
        y--;

        // Draw ellipse arc for each point on the sides
        DRAW_OFFSET_POINT(x, y);
        DRAW_OFFSET_POINT(-x, -y);
        DRAW_OFFSET_POINT(-x, y);
        DRAW_OFFSET_POINT(x, -y);
    }
}

void CCGraphic_drawfilled_ellipse(
    CCDeviceHandler* handler,
    CCGraphic_Ellipse* ellipse
)
{
    const int16_t x_radius = ellipse->X_Radius;
    const int16_t y_radius = ellipse->Y_Radius;

    // Bresenham's Ellipse Algorithm to avoid costly floating point calculations
    // Reference: https://blog.csdn.net/myf_666/article/details/128167392

    int16_t x = 0;
    int16_t y = y_radius;
    const int16_t y_radius_square = SQUARE(y_radius);
    const int16_t x_radius_square = SQUARE(x_radius);

    // Initial decision variable for the first region of the ellipse
    float d1 = y_radius_square + x_radius_square * (-y_radius + 0.5);
    CCGraphic_Point point;
    // Fill the ellipse by drawing vertical lines in the specified range (filled area)
    for (int16_t j = -y; j < y; j++) {
        // Draw vertical lines to fill the area of the ellipse
        DRAW_OFFSET_POINT(0, j);
        DRAW_OFFSET_POINT(0, j);
    }

    // Draw initial points on the ellipse (4 points due to symmetry)
    DRAW_OFFSET_POINT(x, y);
    DRAW_OFFSET_POINT(-x, -y);
    DRAW_OFFSET_POINT(-x, y);
    DRAW_OFFSET_POINT(x, -y);

    // Draw the middle part of the ellipse (first region)
    while (y_radius_square * (x + 1) < x_radius_square * (y - 0.5)) {
        if (d1 <= 0) {  // Next point is to the east of the current point
            d1 += y_radius_square * (2 * x + 3);
        } else {  // Next point is southeast of the current point
            d1 += y_radius_square * (2 * x + 3) + x_radius_square * (-2 * y + 2);
            y--;
        }
        x++;

        // Fill the ellipse by drawing vertical lines in the current range
        for (int16_t j = -y; j < y; j++) {
            DRAW_OFFSET_POINT(x, j);
            DRAW_OFFSET_POINT(-x, j);
        }

        // Draw ellipse arc for each point in the current region
        DRAW_OFFSET_POINT(x, y);
        DRAW_OFFSET_POINT(-x, -y);
        DRAW_OFFSET_POINT(-x, y);
        DRAW_OFFSET_POINT(x, -y);
    }

    // Draw the two sides of the ellipse (second region)
    float d2 = SQUARE(y_radius * (x + 0.5)) + SQUARE(x_radius * (y - 1)) - x_radius_square * y_radius_square;

    while (y > 0) {
        if (d2 <= 0) {  // Next point is to the east of the current point
            d2 += y_radius_square * (2 * x + 2) + x_radius_square * (-2 * y + 3);
            x++;
        } else {  // Next point is southeast of the current point
            d2 += x_radius_square * (-2 * y + 3);
        }
        y--;

        // Fill the ellipse by drawing vertical lines in the current range
        for (int16_t j = -y; j < y; j++) {
            DRAW_OFFSET_POINT(x, j);
            DRAW_OFFSET_POINT(-x, j);
        }

        // Draw ellipse arc for each point on the sides
        DRAW_OFFSET_POINT(x, y);
        DRAW_OFFSET_POINT(-x, -y);
        DRAW_OFFSET_POINT(-x, y);
        DRAW_OFFSET_POINT(x, -y);
    }
}

#undef DRAW_OFFSET_POINT
#undef SQUARE