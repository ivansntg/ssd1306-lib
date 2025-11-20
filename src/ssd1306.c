/**
 * @file ssd1306.c
 * @author Iván Santiago (https://github.com/ivansntg)
 * @brief This library provides macros, data structures and functions for
 *        configuring a SSD1306-driven OLED display.
 */
#include "ssd1306/ssd1306.h"

#define SSD1306_COMMAND_SET_START_LINE(LINE) (0x40 | ((LINE) & 0x3F))
#define SSD1306_PA_LOWER_START_COLUMN(COL) ((COL) & 0x0F)
#define SSD1306_PA_HIGHER_START_COLUMN(COL) (0x10 | ((COL) & 0x0F))
#define SSD1306_PA_START_PAGE(PAGE) (0xB0 | ((PAGE) & 0x07))

/**
 * @brief SSD1306 control byte.
 */
enum ssd1306_control_byte
{
    CONTROL_BYTE_COMMAND, DUMMY_BYTE_00 = 0x00,
    CONTROL_BYTE_DATA = 0x40,
    DUMMY_BYTE_FF = 0xFF
};

/**
 * @brief Writes to the SSD1306 chip using a ssd1306_t struct.
 * @param driver Pointer to a ssd1306 struct.
 * @param src Pointer to data source.
 * @param len Number of bytes to write.
 */
static inline void _ssd1306_write(ssd1306_t *driver, uint8_t *src, uint16_t len)
{
    driver->i2c_write(driver->i2c_address, src, len);
}

void ssd1306_set_contrast(ssd1306_t *driver, uint8_t contrast)
{
    uint8_t cmd[] = {
        CONTROL_BYTE_COMMAND,
        SSD1306_COMMAND_SET_CONTRAST_CONTROL,
        contrast
    };
    _ssd1306_write(driver, cmd, 3u);
}

void ssd1306_set_display_on(ssd1306_t *driver)
{
    uint8_t cmd[] = {
        CONTROL_BYTE_COMMAND,
        SSD1306_COMMAND_SET_DISPLAY_ON
    };
    _ssd1306_write(driver, cmd, 2u);
}

void ssd1306_set_display_off(ssd1306_t *driver)
{
    uint8_t cmd[] = {
        CONTROL_BYTE_COMMAND,
        SSD1306_COMMAND_SET_DISPLAY_OFF
    };
    _ssd1306_write(driver, cmd, 2u);
}

void ssd1306_set_normal_display(ssd1306_t *driver)
{
    uint8_t cmd[] = {
        CONTROL_BYTE_COMMAND,
        SSD1306_COMMAND_SET_NORMAL_DISPLAY
    };
    _ssd1306_write(driver, cmd, 2u);
}

void ssd1306_set_inverse_display(ssd1306_t *driver)
{
    uint8_t cmd[] = {
        CONTROL_BYTE_COMMAND,
        SSD1306_COMMAND_SET_INVERSE_DISPLAY
    };
    _ssd1306_write(driver, cmd, 2u);
}

void ssd1306_set_entire_display_on(ssd1306_t *driver)
{
    uint8_t cmd[] = {
        CONTROL_BYTE_COMMAND,
        SSD1306_COMMAND_ENTIRE_DISPLAY_ON
    };
    _ssd1306_write(driver, cmd, 2u);
}

void ssd1306_resume_to_ram_content(ssd1306_t *driver)
{
    uint8_t cmd[] = {
        CONTROL_BYTE_COMMAND,
        SSD1306_COMMAND_RESUME_TO_RAM_CONTENT
    };
    _ssd1306_write(driver, cmd, 2u);
}

void ssd1306_activate_scroll(ssd1306_t *driver,
                             ssd1306_scrolling_config_t config)
{
    if (config.mode >= VERTICAL_AND_RIGHT_SCROLL)
    {
        uint8_t cmd[] = {
            CONTROL_BYTE_COMMAND,
            SSD1306_COMMAND_SET_VERTICAL_SCROLL_AREA,
            config.start_row,
            config.rows,
            config.mode,
            DUMMY_BYTE_00,
            config.start_page,
            config.rate,
            config.end_page,
            config.vertical_offset,
            SSD1306_COMMAND_ACTIVATE_SCROLL
        };
        _ssd1306_write(driver, cmd, 11u);
    }
    else
    {
        uint8_t cmd[] = {
            CONTROL_BYTE_COMMAND,
            config.mode,
            DUMMY_BYTE_00,
            config.start_page,
            config.rate,
            config.end_page,
            DUMMY_BYTE_00,
            DUMMY_BYTE_FF,
            SSD1306_COMMAND_ACTIVATE_SCROLL
        };
        _ssd1306_write(driver, cmd, 9u);
    }
}

void ssd1306_deactivate_scroll(ssd1306_t *driver)
{
    uint8_t cmd[] = {
        CONTROL_BYTE_COMMAND,
        SSD1306_COMMAND_DEACTIVATE_SCROLL
    };
    _ssd1306_write(driver, cmd, 2u);
}

void ssd1306_configure(ssd1306_t *driver, ssd1306_config_t config)
{
    uint8_t cmd[] = {
        CONTROL_BYTE_COMMAND,
        SSD1306_COMMAND_SET_DISPLAY_OFF,
        SSD1306_COMMAND_SET_MUX_RATIO,
        config.mux_ratio,
        SSD1306_COMMAND_SET_DISPLAY_OFFSET,
        config.display_offset,
        SSD1306_COMMAND_SET_START_LINE(config.start_line),
        config.seg_remap,
        config.scan_direction,
        SSD1306_COMMAND_SET_COM_PINS_CONFIGURATION,
        config.pin_config | config.com_remap,
        SSD1306_COMMAND_SET_CONTRAST_CONTROL,
        config.contrast,
        SSD1306_COMMAND_RESUME_TO_RAM_CONTENT,
        config.mode,
        SSD1306_COMMAND_SET_OSCILLATOR_FREQUENCY,
        (config.oscillator_frequency << 4u) | (config.clock_divider & 0x0F),
        SSD1306_COMMAND_SET_PRECHARGE_PERIOD,
        (config.phase1_period << 4u) | (config.phase2_period & 0x0F),
        SSD1306_COMMAND_SET_DESELECT_LEVEL,
        config.deselect_level,
        SSD1306_COMMAND_SET_MEMORY_ADDRESSING_MODE,
        config.addressing_mode,
        SSD1306_PA_LOWER_START_COLUMN(config.start_column),
        SSD1306_PA_HIGHER_START_COLUMN(config.start_column),
        SSD1306_PA_START_PAGE(config.start_page),
        SSD1306_COMMAND_SET_COLUMN_ADDRESS,
        config.start_column,
        config.end_column,
        SSD1306_COMMAND_SET_PAGE_ADDRESS,
        config.start_page,
        config.end_page,
        SSD1306_COMMAND_CHARGE_PUMP_SETTING,
        config.charge_pump
    };
    _ssd1306_write(driver, cmd, 34u);
}

ssd1306_config_t ssd1306_get_default_config(void)
{
    ssd1306_config_t default_config = {
        .contrast = 0x7F,
        .mode = NORMAL_DISPLAY,
        .addressing_mode = PAGE_ADDRESSING_MODE,
        .start_column = 0,
        .end_column = 127,
        .start_page = 0,
        .end_page = 7,
        .start_line = 0,
        .seg_remap = MAP_COL0_TO_SEG0,
        .mux_ratio = 63,
        .scan_direction = SCAN_DIRECTION_NORMAL,
        .display_offset = 0,
        .pin_config = ALTERNATIVE_COM_PIN_CONFIGURATION,
        .com_remap = DISABLE_COM_LEFT_RIGHT_REMAP,
        .clock_divider = 0,
        .oscillator_frequency = 8,
        .phase1_period = 2,
        .phase2_period = 2,
        .deselect_level = DESELECT_LEVEL_77_PERCENT_VCC,
        .charge_pump = DISABLE_CHARGE_PUMP
    };
    return default_config;
}

void ssd1306_update_gddram(ssd1306_t *driver, uint8_t *bitmap, uint16_t lenght)
{
    bitmap[0] = CONTROL_BYTE_DATA;
    _ssd1306_write(driver, bitmap, lenght);
}
