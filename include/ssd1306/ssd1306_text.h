/**
 * @file ssd1306_text.h
 * @author Iván Santiago (https://github.com/ivansntg)
 * @brief This file provides functions, macros and data structures for rendering
 *        bitmap-based text to the SSD1306 display.
 */

#ifndef __SSD1306_TEXT_H
#define __SSD1306_TEXT_H

#include "font/ssd1306_font.h"
#include "ssd1306_bitmap.h"
#include <stdint.h>

/**
 * @brief Struct for managing text rendering.
 */
typedef struct ssd1306_text_renderer {
    ssd1306_bitmap_t *bitmap; /**< Pointer to a ssd1306_bitmap struct. */
    ssd1306_font_t *font;     /**< Pointer to a ssd1306_font struct. */
    uint8_t cursor_col;       /**< Cursor column position. */
    uint8_t cursor_row;       /**< Cursor row position. */
} ssd1306_text_renderer_t;

/**
 * @brief Sets cursor position.
 * @param r Pointer to a ssd1306_text_renderer struct.
 * @param col Cursor column.
 * @param row Cursor row.
 */
void ssd1306_set_cursor_position(ssd1306_text_renderer_t *t, uint8_t col,
                                 uint8_t row);

/**
 * @brief Draws a some text at the current cursor position.
 * @param r Pointer to a ssd1306_text_renderer struct.
 * @param str Text to draw.
 */
void ssd1306_draw_text(ssd1306_text_renderer_t *t, char *str);

#endif /* !__SSD1306_TEXT_H */
