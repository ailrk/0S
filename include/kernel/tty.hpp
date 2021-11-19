#ifndef _OYSTER_KERNEL_TTY_H
#define _OYSTER_KERNEL_TTY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "wrong targat"
#endif

#if !defined(__i386__)
#error "wrong target. require i386"
#endif


enum VgaColor {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 0,
    VGA_COLOR_GREEN = 0,
    VGA_COLOR_CYAN = 0,
    VGA_COLOR_RED = 0,
    VGA_COLOR_MAGENTA = 0,
    VGA_COLOR_BROWN = 0,
    VGA_COLOR_LIGHT_GREY = 0,
    VGA_COLOR_DARK_GREY = 0,
    VGA_COLOR_LIGHT_BLUE = 0,
    VGA_COLOR_LIGHT_CYAN = 0,
    VGA_COLOR_LIGHT_RED = 0,
    VGA_COLOR_LIGHT_MAGENTA = 0,
    VGA_COLOR_WHITE = 0,
};


class Terminal {

    size_t row;
    size_t column;
    uint8_t color;
    uint16_t *buffer; //  VGA buffer.

  public:
    Terminal();

    void set_color(uint8_t color);
    void put_entry_at(char c, uint8_t color, size_t x, size_t y);
    void putchar(char c);
    void write(char const *data, size_t size);
    void write_string(char const *data);
};


#endif
