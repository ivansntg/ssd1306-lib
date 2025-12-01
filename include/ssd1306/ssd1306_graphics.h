/**
 * @file ssd1306_graphics.h
 * @author Iván Santiago (https://github.com/ivansntg)
 * @brief This file provides functions for drawing lines, polygons and circles
 *        to the SSD1306 display.
 */

#ifndef __SSD1306_GRAPHICS_H
#define __SSD1306_GRAPHICS_H

#include "ssd1306_bitmap.h"
#include <stdint.h>

/**
 * @brief Sets a pixel at the (x, y) position.
 * @param bitmap Pointer to a ssd1306_bitmap stuct.
 * @param x Position on the x-axis.
 * @param y Position on the y-axis.
 */
static inline void ssd1306_set_pixel(ssd1306_bitmap_t *bitmap, uint8_t x,
                                     uint8_t y)
{
    if (x < bitmap->width && y < bitmap->height) {
        uint16_t index = 1u + x + (y >> 3u) * bitmap->width;
        uint8_t value = 1u << (y - ((y >> 3u) << 3u));
        bitmap->data[index] |= value;
    }
}

/**
 * @brief Draws a line from (x1, y1) to (x2, y2) using the Bresenham's line
 *        algorithm.
 * @param bitmap Pointer to a ssd1306_bitmap struct.
 * @param x1 Start point position on the x-axis.
 * @param y1 Start point position on the y-axis.
 * @param x2 End point position on the x-axis.
 * @param y2 End point position on the y-axis.
 */
void ssd1306_draw_line(ssd1306_bitmap_t *bitmap, int8_t x1, int8_t y1,
                       int8_t x2, int8_t y2);

/**
 * @brief Draws a circle using the midpoint algorithm.
 * @param bitmap Pointer to a ssd1306_bitmap struct.
 * @param cx Center x-axis position.
 * @param cy Center y-axis position.
 * @param r Radius.
 */
void ssd1306_draw_circle(ssd1306_bitmap_t *bitmap, int8_t cx, int8_t cy,
                         int8_t r);

/**
 * @brief Draws a polygon by connecting a list of points.
 * @param bitmap Pointer to ssd1306_bitmap struct.
 * @param x Array containing points x-axis positions.
 * @param y Array containing points y-axis positions.
 * @param n Number of points in the array.
 */
void ssd1306_draw_polygon(ssd1306_bitmap_t *bitmap, int8_t *x, int8_t *y,
                          uint16_t n);

/**
 * @brief Draws a list of points connected by lines.
 * @param bitmap Pointer to ssd1306_bitmap struct.
 * @param x Array containing points x-axis positions.
 * @param y Array containing points y-axis positions.
 * @param n Number of points in the array.
 */
void ssd1306_draw_polyline(ssd1306_bitmap_t *bitmap, int8_t *x, int8_t *y,
                           uint16_t n);

#endif /** !__SSD1306_GRAPHICS_H */
