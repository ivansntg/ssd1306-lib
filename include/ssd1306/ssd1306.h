/**
 * @file ssd1306.h
 * @author Iván Santiago (https://github.com/ivansntg)
 * @brief This library provides macros, data structures and functions for
 *        configuring a SSD1306-driven OLED display.
 */

#ifndef __SSD1306_H
#define __SSD1306_H

#include <stdint.h>

#define SSD1306_COMMAND_SET_CONTRAST_CONTROL 0x81
#define SSD1306_COMMAND_RESUME_TO_RAM_CONTENT 0xA4
#define SSD1306_COMMAND_ENTIRE_DISPLAY_ON 0xA5
#define SSD1306_COMMAND_SET_NORMAL_DISPLAY 0xA6
#define SSD1306_COMMAND_SET_INVERSE_DISPLAY 0xA7
#define SSD1306_COMMAND_SET_DISPLAY_OFF 0xAE
#define SSD1306_COMMAND_SET_DISPLAY_ON  0xAF
#define SSD1306_COMMAND_RIGHT_SCROLL_SETUP 0x26
#define SSD1306_COMMAND_LEFT_SCROLL_SETUP 0x27
#define SSD1306_COMMAND_VERTICAL_AND_RIGHT_SCROLL_SETUP 0x29
#define SSD1306_COMMAND_VERTICAL_AND_LEFT_SCROLL_SETUP 0x2A
#define SSD1306_COMMAND_DEACTIVATE_SCROLL 0x2E
#define SSD1306_COMMAND_ACTIVATE_SCROLL 0x2F
#define SSD1306_COMMAND_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_COMMAND_SET_MEMORY_ADDRESSING_MODE 0x20
#define SSD1306_COMMAND_SET_COLUMN_ADDRESS 0x21
#define SSD1306_COMMAND_SET_PAGE_ADDRESS 0x22
#define SSD1306_COMMAND_MAP_COL0_TO_SEG0 0xA0
#define SSD1306_COMMAND_MAP_COL127_TO_SEG0 0xA1
#define SSD1306_COMMAND_SET_MUX_RATIO 0xA8
#define SSD1306_COMMAND_SET_NORMAL_SCAN_DIRECTION 0xC0
#define SSD1306_COMMAND_SET_REMAPPED_SCAN_DIRECTION 0xC8
#define SSD1306_COMMAND_SET_DISPLAY_OFFSET 0xD3
#define SSD1306_COMMAND_SET_COM_PINS_CONFIGURATION 0xDA
#define SSD1306_COMMAND_SET_OSCILLATOR_FREQUENCY 0xD5
#define SSD1306_COMMAND_SET_PRECHARGE_PERIOD 0xD9
#define SSD1306_COMMAND_SET_DESELECT_LEVEL 0xDB
#define SSD1306_COMMAND_NOP 0xE9
#define SSD1306_COMMAND_CHARGE_PUMP_SETTING 0x8D

/**
 * @brief Struct for driving a SSD1306-based display.
 */
typedef struct ssd1306
{
    uint8_t i2c_address; /**< SSD1306 I2C address. */
    /**< Function to write to the SSD1306 chip using the I2C interface. */
    void (*i2c_write)(uint8_t, uint8_t *, uint16_t);
} ssd1306_t;

/**
 * @brief SSD1306 display mode. When the inverted mode is selected a 0 in RAM is
 *        ON in the display panel.
 */
enum ssd1306_display_mode
{
    NORMAL_DISPLAY = 0xA6,
    INVERSE_DISPLAY = 0xA7
};

/**
 * @brief SSD1306 scrolling mode.
 */
enum ssd1306_scrolling_mode
{
    RIGHT_HORIZONTAL_SCROLL = 0x26,
    LEFT_HORIZONTAL_SCROLL = 0x27,
    VERTICAL_AND_RIGHT_SCROLL = 0x29,
    VERTICAL_AND_LEFT_SCROLL = 0x2A
};

/**
 * @brief SSD1306 segment mapping mode.
 */
enum ssd1306_segment_remap
{
    MAP_COL0_TO_SEG0 = 0xA0,
    MAP_COL127_TO_SEG0 = 0xA1
};

/**
 * @brief SSD1306 scan direction.
 */
enum ssd1306_scan_direction
{
    SCAN_DIRECTION_NORMAL = 0xC0,
    SCAN_DIRECTION_REMAPPED = 0xC8
};

/**
 * @brief SSD1306 COM pins hardware configuration.
 */
enum ssd1306_pin_configuration
{
    SEQUENTIAL_COM_PIN_CONFIGURATION = 0x00,
    ALTERNATIVE_COM_PIN_CONFIGURATION = 0x10
};

/**
 * @brief SSD1306 COM left/rigt remap.
 */
enum ssd1306_com_remap
{
    DISABLE_COM_LEFT_RIGHT_REMAP = 0x00,
    ENABLE_COM_LEFT_RIGHT_REMAP = 0x20
};

/**
 * @brief SSD1306 deselect level.
 */
enum ssd1306_deselect_level
{
    DESELECT_LEVEL_65_PERCENT_VCC = 0x00,
    DESELECT_LEVEL_77_PERCENT_VCC = 0x20,
    DESELECT_LEVEL_83_PERCENT_VCC = 0x30
};

/**
 * @brief SSD1306 enable/disable charge pump.
 */
enum ssd1306_charge_pump
{
    DISABLE_CHARGE_PUMP = 0x10,
    ENABLE_CHARGE_PUMP = 0x14
};

/**
 * @brief SSD1306 addressing mode.
 */
enum ssd1306_addressing_mode
{
    HORIZONTAL_ADDRESSING_MODE,
    VERTICAL_ADDRESSING_MODE,
    PAGE_ADDRESSING_MODE
};

/**
 * @brief SSD1306 time between each scroll step.
 */
enum ssd1306_scrolling_rate
{
    SCROLL_RATE_5_FRAMES,
    SCROLL_RATE_64_FRAMES,
    SCROLL_RATE_128_FRAMES,
    SCROLL_RATE_256_FRAMES,
    SCROLL_RATE_3_FRAMES,
    SCROLL_RATE_4_FRAMES,
    SCROLL_RATE_25_FRAMES,
    SCROLL_RATE_2_FRAMES
};

/**
 * @brief Struct for configuring the SSD1306 chip.
 */
typedef struct ssd1306_config
{
    uint8_t contrast; /**< Contrast level (0-255). */
    enum ssd1306_display_mode mode; /**< Normal or inverted mode. */
    enum ssd1306_addressing_mode addressing_mode; /**< Addressing mode. */
    uint8_t start_column; /**< Start column address. */
    uint8_t end_column; /**< End column address. */
    uint8_t start_page; /**< Start page address. */
    uint8_t end_page; /**< End page address. */
    uint8_t start_line; /**< Display start line. */
    enum ssd1306_segment_remap seg_remap; /**< Segment re-map. */
    uint8_t mux_ratio; /**< Multiplexer ratio (15-63). */
    enum ssd1306_scan_direction scan_direction; /**< Scan direction. */
    uint8_t display_offset; /**< Vertical shift by COM (0-63). */
    enum ssd1306_pin_configuration pin_config; /**< Hardware COM pins. */
    enum ssd1306_com_remap com_remap; /**< COM left/right remap. */
    uint8_t clock_divider; /**< Clock divide ratio (0-15). */
    uint8_t oscillator_frequency; /**< Oscillator frequency. (0-15). */
    uint8_t phase1_period; /**< Phase 1 period. (1-15). */
    uint8_t phase2_period; /**< Phase 2 period. (1-15). */
    enum ssd1306_deselect_level deselect_level; /**< Deselect V_{COMH} level. */
    enum ssd1306_charge_pump charge_pump; /**< Enable/disable charge pump. */
} ssd1306_config_t;

/**
 * @brief Struct for configuring SSD1306 scroll.
 */
typedef struct ssd1306_scrolling_config
{
    enum ssd1306_scrolling_mode mode; /**< Scrolling mode. */
    enum ssd1306_scrolling_rate rate; /**< Scrolling rate. */
    uint8_t start_page; /**< Horizontal scrolling start page. */
    uint8_t end_page; /**< Horizontal scrolling end page. */
    uint8_t vertical_offset; /**< Vertical scrolling offset. */
    uint8_t start_row; /**< Number of rows in the top fixed area. */
    uint8_t rows; /**< Number of rows for vertical scrolling. */
} ssd1306_scrolling_config_t;

/**
 * @brief Sets the contrast value.
 * @param driver Pointer to a ssd1306 struct.
 * @param contrast Contrast value.
 */
void ssd1306_set_contrast(ssd1306_t *driver, uint8_t contrast);

/**
 * @brief Sets the display on. (Normal mode)
 * @param driver Pointer to a ssd1306 struct.
 */
void ssd1306_set_display_on(ssd1306_t *driver);

/**
 * @brief Sets the display off. (Sleep mode)
 * @param driver Pointer to a ssd1306 struct.
 */
void ssd1306_set_display_off(ssd1306_t *driver);

/**
 * @brief Sets normal display mode. A 0 in RAM means OFF in the display panel.
 * @param driver Pointer to a ssd1306 struct.
 */
void ssd1306_set_normal_display(ssd1306_t *driver);

/**
 * @brief Sets inverse display mode. A 0 in RAM means ON in the display panel.
 * @param driver Pointer to a ssd1306 struct.
 */
void ssd1306_set_inverse_display(ssd1306_t *driver);

/**
 * @brief Sets the entire display on.
 * @param driver Pointer to a ssd1306 struct.
 */
void ssd1306_set_entire_display_on(ssd1306_t *driver);

/**
 * @brief Resumes to RAM content.
 * @param driver Pointer to a ssd1306 struct.
 */
void ssd1306_resume_to_ram_content(ssd1306_t *driver);

/**
 * @brief Activates display scrolling.
 * @param driver Pointer to a ssd1306 struct.
 * @param config Struct that defines scrolling configuration.
 */
void ssd1306_activate_scroll(ssd1306_t *driver,
                             ssd1306_scrolling_config_t config);

/**
 * @brief Deactivates display scrolling.
 * @param driver Pointer to a ssd1306 struct.
 */
void ssd1306_deactivate_scroll(ssd1306_t *driver);

/**
 * @brief Configures the SSD1306 chip.
 * @param driver Pointer to a ssd1306 struct.
 * @param config Struct that defines SSD1306 configuration.
 */
void ssd1306_configure(ssd1306_t *driver, ssd1306_config_t config);

/**
 * @brief Returns the default SSD1306 configuration.
 * @return A ssd1306_config struct that contains SSD1306 reset values.
 */
ssd1306_config_t ssd1306_get_default_config(void);

/**
 * @brief Updates SSD1306 Graphics Display Data RAM.
 * @param driver Pointer to a ssd1306 struct.
 * @param bitmap Array containing graphics display data.
 * @pram length Number of bytes to write.
 * @note The first byte in the bitmap array is reserved as a control byte.
 */
void ssd1306_update_gddram(ssd1306_t *driver, uint8_t *bitmap, uint16_t lenght);

#endif /* !__SSD1306_H */
