/**
 * @file ssd1306_text.c
 * @author Iván Santiago (https://github.com/ivansntg)
 * @brief This file provides functions, macros and data structures for
 * rendering bitmap-based text to the SSD1306 display.
 */

#include "ssd1306/ssd1306_text.h"

/**
 * @brief Converts the cursor position to a bitmap index.
 * @param t Pointer to a ssd1306_text_renderer struct.
 * @param col Cursor column position.
 * @param row Cursor row position.
 */
static inline uint16_t ssd1306_cursor_to_index(ssd1306_text_renderer_t *t,
                                               uint8_t col, uint8_t row)
{
    return (1 + col + row * t->bitmap->width);
}

/**
 * @brief Moves the cursor to the next line.
 * @param t Pointer to a ssd1306_text_renderer struct.
 */
static inline uint8_t ssd1306_cursor_next_line(ssd1306_text_renderer_t *t)
{
    uint8_t next_line = t->cursor_row + t->font->page_alignment;
    if (next_line > (t->bitmap->height >> 3) - t->font->page_alignment) {
        return 1;
    }
    t->cursor_col = 0;
    t->cursor_row = next_line;
    return 0;
}

void ssd1306_set_cursor_position(ssd1306_text_renderer_t *t, uint8_t col,
                                 uint8_t row)
{
    if (row > (t->bitmap->height >> 3) - t->font->page_alignment)
        row = (t->bitmap->height >> 3) - t->font->page_alignment;
    if (col >= t->bitmap->width)
        col = t->bitmap->width - 1;
    t->cursor_col = col;
    t->cursor_row = row;
}

void ssd1306_draw_text(ssd1306_text_renderer_t *t, char *str)
{
    uint16_t i = 0;

    while (str[i]) {
        if (str[i] == ' ') {
            ssd1306_set_cursor_position(t, t->cursor_col + t->font->space_width,
                                        t->cursor_row);
        } else if (str[i] >= t->font->first_char &&
                   str[i] <= t->font->last_char) {
            uint8_t x = str[i] - t->font->first_char;

            uint8_t w = t->font->type == SSD1306_VARIABLE_WIDTH_FONT
                            ? t->font->char_width[x]
                            : t->font->space_width;

            uint16_t font_index = t->font->type == SSD1306_VARIABLE_WIDTH_FONT
                                      ? t->font->char_offset[x]
                                      : x * w * t->font->page_alignment;

            if (t->cursor_col + w >= t->bitmap->width) {
                if (ssd1306_cursor_next_line(t)) {
                    break;
                }
            }

            for (uint8_t p = 0; p < t->font->page_alignment; p++) {
                uint16_t cursor_index = ssd1306_cursor_to_index(
                    t, t->cursor_col, t->cursor_row + p);
                for (uint8_t k = 0; k < w; k++) {
                    t->bitmap->data[cursor_index + k] =
                        t->font->data[font_index];
                    font_index++;
                }
            }
            if (str[i + 1] == ' ') {
                ssd1306_set_cursor_position(t, t->cursor_col + w,
                                            t->cursor_row);
            } else {
                ssd1306_set_cursor_position(
                    t, t->cursor_col + w + t->font->horizontal_separation,
                    t->cursor_row);
            }
        }

        i++;
    }
}
