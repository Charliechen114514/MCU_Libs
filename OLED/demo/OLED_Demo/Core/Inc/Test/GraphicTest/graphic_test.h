#ifndef GRAPHICS_TEST_H
#define GRAPHICS_TEST_H

#include "Graphic/CCGraphic_device_adapter.h"

/* device test */
void on_test_init_hardiic_oled(CCDeviceHandler* handle);
void on_test_init_softspi_oled(CCDeviceHandler* handle);
void on_test_init_hardspi_oled(CCDeviceHandler* handler);
/* base test */
void on_test_draw_points(CCDeviceHandler* handle);
void on_test_draw_line(CCDeviceHandler* handle);
void on_test_draw_circle(CCDeviceHandler* handle);
void on_test_draw_rectangle(CCDeviceHandler* handle);
void on_test_draw_triangle(CCDeviceHandler* handle);
void on_test_draw_ellipse(CCDeviceHandler* handle);
void on_test_draw_arc(CCDeviceHandler* handle);

/* widget test */
void on_test_draw_image(CCDeviceHandler* handle);
void on_test_draw_ascii(CCDeviceHandler* handle);

/* components test */
void on_test_component_textEdit_test(CCDeviceHandler* handle);
void on_test_component_frame_test(CCDeviceHandler* handle);
void on_test_component_menu(CCDeviceHandler* handler);
#endif