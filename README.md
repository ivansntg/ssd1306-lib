# ssd1306-lib

This library provides macros, data structures, and functions to interface
a microcontroller with an SSD1306-driven OLED display.

## Features

- Supported interfaces: `I2C`
- SSD1306 configuration and control
- Basic graphic primitives rendering
- Bitmap-based text rendering

## Project structure

| Directory | Description |
| --- | --- |
| `assets/fonts` | Contains text fonts as images |
| `docs` | Documentation related files |
| `include/ssd1306` | Header files |
| `include/ssd1306/font` | Font header files |
| `src` | Source files |

## Usage

### SSD1306 configuration

In order to configure the SSD1306 chip, it is necessary to implement a
function that uses the MCU I2C hardware to write a burst of bytes and
initialize a `ssd1306` struct to use it. The following example code
shows how to configure the SSD1306 chip.

```c
void ssd1306_i2c_write(uint8_t address, uint8_t *src, uint16_t length)
{
    // MCU-specific I2C write function
}

ssd1306_t ssd1306_handler = {
    .i2c_address = 0x3C
    .i2c_write = ssd1306_i2c_write
};

ssd1306_config_t config = ssd1306_get_default_config();
config.addressing_mode = HORIZONTAL_ADDRESSING_MODE;
ssd1306_configure(&ssd1306_handler, config);

ssd1306_set_display_on(&ssd1306_handler);
```

### Rendering graphics

The `ssd1306/ssd1306_graphics.h` file provides functions to draw some
basic graphics using a `ssd1306_bitmap` struct.

```c
uint8_t ssd1306_buffer[SSD1306_BUFFER_SIZE(128, 64)];

ssd1306_bitmap_t bm = {
    .width = 128,
    .height = 64,
    .length = SSD1306_BUFFER_SIZE(128, 64),
    .data = ssd1306_buffer
};

// Clear buffer
ssd1306_bitmap_clear(&bm);

// Draw
ssd1306_draw_line(&bm, 0, 0, 127, 63);

// Update SSD1306 RAM contents
ssd1306_update_gddram(&ssd1306_handler, bm.data, bm.length);
```

### Rendering text

Text rendering is provided by the `ssd1306/ssd1306_text.h` file and can be
used as follows:

```c
#include "ssd1306/font/ssd1306_font_7x11.h"

ssd1306_text_renderer_t text = {
    .bitmap = &bm,
    .font = &font_7x11
};

ssd1306_set_cursor_position(&text, 0, 0);
ssd1306_draw_text(&text, "Hello world!");
```

### Building

If the project uses `CMake` as build system, the library can be added as follows:

```cmake
add_library(ssd1306-lib INTERFACE)
target_sources(ssd1306-lib INTERFACE ./src/ssd1306.c .src/ssd1306_graphics.h .src/ssd1306_text.h)
target_include_directories(ssd1306-lib INTERFACE ./include)
```

### Documentation

The API reference documentation can be built with `doxygen` using the
following command:

```shell
cd docs
doxygen Doxyfile
```
