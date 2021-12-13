#pragma once

#include <stdint.h>
#include <stddef.h>

enum VgaColor {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE,
    VGA_COLOR_GREEN,
    VGA_COLOR_CYAN,
    VGA_COLOR_RED,
    VGA_COLOR_MAGENTA,
    VGA_COLOR_BROWN,
    VGA_COLOR_LIGHT_GREY,
    VGA_COLOR_DARK_GREY,
    VGA_COLOR_LIGHT_BLUE,
    VGA_COLOR_LIGHT_CYAN,
    VGA_COLOR_LIGHT_RED,
    VGA_COLOR_LIGHT_MAGENTA,
    VGA_COLOR_WHITE,
};

struct Terminal {
    size_t row;
    size_t column;
    uint8_t color;
    uint16_t *buffer;

    Terminal();
    void set_color(uint8_t color);
    void put_entry_at(char c, uint8_t color, size_t x, size_t y);
    void putchar(char c);
    void write(const char *data, size_t size);
    void write_string(const char *data);
};
