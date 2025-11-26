/**
 * @file ssd1306_graphics.h
 * @author Iván Santiago (https://github.com/ivansntg)
 * @brief This file provides functions for drawing lines, polygons and circles
 *        to the SSD1306 display.
 */

#include "ssd1306/ssd1306_graphics.h"

void ssd1306_draw_line(ssd1306_bitmap_t *bitmap, int8_t x1, int8_t y1,
                       int8_t x2, int8_t y2)
{
    if (x1 < 0)
        x1 = 0;
    if (y1 < 0)
        y1 = 0;
    if (x1 >= bitmap->width)
        x1 = bitmap->width - 1;
    if (y1 >= bitmap->height)
        y1 = bitmap->height - 1;
    if (x2 < 0)
        x2 = 0;
    if (y2 < 0)
        y2 = 0;
    if (x2 >= bitmap->width)
        x2 = bitmap->width - 1;
    if (y2 >= bitmap->height)
        y2 = bitmap->height - 1;

    int16_t dx = x2 - x1;
    int16_t dy = y2 - y1;
    int16_t sx = 1;
    int16_t sy = 1;

    if (dx < 0)
    {
        dx = -dx;
        sx = -1;
    }

    if (dy < 0)
    {
        dy = -dy;
        sy = -1;
    }

    dy = -dy;
    int16_t e = dx + dy;
    int16_t de;

    for (;;)
    {
        ssd1306_set_pixel(bitmap, x1, y1);
        de = 2 * e;

        if (de >= dy)
        {
            if (x1 == x2)
                break;
            e += dy;
            x1 += sx;
        }

        if (de <= dx)
        {
            if (y1 == y2)
                break;
            e += dx;
            y1 += sy;
        }
    }
}

void ssd1306_draw_circle(ssd1306_bitmap_t *bitmap, int8_t cx, int8_t cy,
                         int8_t r)
{
    int16_t x = -r;
    int16_t y = 0;
    int16_t e = 2 - 2 * r;

    do
    {
        ssd1306_set_pixel(bitmap, cx - x, cy + y);
        ssd1306_set_pixel(bitmap, cx - y, cy - x);
        ssd1306_set_pixel(bitmap, cx + x, cy - y);
        ssd1306_set_pixel(bitmap, cx + y, cy + x);

        r = e;

        if (r <= y)
            e += ++y * 2 + 1;

        if (r > x || e > y)
            e += ++x * 2 + 1;
    } while (x < 0);
}

void ssd1306_draw_polygon(ssd1306_bitmap_t *bitmap, int8_t *x, int8_t *y,
                          uint16_t n)
{
    for (uint16_t i = 0; i < n - 1; i++)
    {
        ssd1306_draw_line(bitmap, x[i], y[i], x[i + 1], y[i + 1]);
    }
    ssd1306_draw_line(bitmap, x[n - 1], y[n - 1], x[0], y[0]);
}

void ssd1306_draw_polyline(ssd1306_bitmap_t *bitmap, int8_t *x, int8_t *y,
                           uint16_t n)
{
    for (uint16_t i = 0; i < n - 1; i++)
    {
        ssd1306_draw_line(bitmap, x[i], y[i], x[i + 1], y[i + 1]);
    }
}
