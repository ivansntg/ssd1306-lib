/**
 * @file ssd1306_font.h
 * @author Iván Santiago (https://github.com/ivansntg)
 * @brief This file provides the ssd1306_font struct used for rendering text
 *        to the SSD1306 display.
 */

#ifndef __SSD1306_FONT_H
#define __SSD1306_FONT_H

#include <stdint.h>

/**
 * @brief SSD1306 font type.
 */
enum ssd1306_font_type {
    SSD1306_FIXED_WIDTH_FONT,   /**< All character have the same width. */
    SSD1306_VARIABLE_WIDTH_FONT /**< Characters have different widths. */
};

/**
 * @brief Struct for managing a bitmap-based font.
 */
struct ssd1306_font {
    enum ssd1306_font_type type; /**< Fixed width or variable width font. */
    char first_char;             /**< First ASCII character. */
    char last_char;              /**< Last ASCII character. */
    uint8_t space_width;         /**< Space width and fixed character width. */
    uint8_t horizontal_separation; /**< Separation between characters. */
    uint8_t page_alignment;        /**< Vertical alignment in terms of pages. */
    const uint8_t *data;           /**< Font bitmap data. */
    const uint16_t data_length;    /**< Font bitmap data length. */
    const uint8_t *char_width;     /**< Array containing character widths. */
    const uint16_t *char_offset;   /** Array containing character offset. < */
};

#endif /* !__SSD1306_FONT_H */
