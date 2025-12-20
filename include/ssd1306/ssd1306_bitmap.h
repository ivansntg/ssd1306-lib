/**
 * @file ssd1306_bitmap.h
 * @author Iván Santiago (https://github.com/ivansntg)
 * @brief This file provides the ssd1306_bitmap struct used for rendering
 *        graphic primitives and text.
 */

#ifndef __SSD1306_BITMAP_H
#define __SSD1306_BITMAP_H

#include <stdint.h>

/**
 * @brief Macro to compute the buffer size based on the display dimensions.
 * @param WIDTH Display width in pixels.
 * @param HEIGHT Display height in pixels.
 */
#define SSD1306_BUFFER_SIZE(WIDTH, HEIGHT) (1u + (WIDTH) * ((HEIGHT) >> 3u))

/**
 * @brief Struct for writing graphic primitives and text to the SSD1306 display.
 */
struct ssd1306_bitmap {
    uint8_t width;   /**< Display width in pixels. */
    uint8_t height;  /**< Display height in pixels. */
    uint16_t length; /**< Buffer length. */
    uint8_t *data;   /**< Pointer to buffer data. */
};

/**
 * @brief Fills the canvas data with 0x00.
 * @param canvas Pointer to a ssd1306_canvas struct.
 */
static inline void ssd1306_bitmap_clear(struct ssd1306_bitmap *bm)
{
    for (uint16_t i = 1; i < bm->length; i++) {
        bm->data[i] = 0x00;
    }
}

#endif /* !__SSD1306_BITMAP_H */
