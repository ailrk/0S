#include "tty.hpp"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "wrong targat"
#endif

#if !defined(__i386__)
#error "wrong target. require i386"
#endif

static inline uint8_t vga_entry_color(VgaColor fg, VgaColor bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return static_cast<uint16_t>(uc) | static_cast<uint16_t>(color) << 8;
}

size_t strlen(char const *str) {
    size_t len = 0;
    for (; *str != '\0'; ++len)
        ;
    return len;
}

static size_t const VGA_WIDTH = 80;
static size_t const VGA_HEIGHT = 25;

Terminal::Terminal() {
    row = 0;
    column = 0;
    color = vga_entry(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    buffer = reinterpret_cast<uint16_t *>(0xb8000);

    for (size_t y = 0; y < VGA_HEIGHT; ++y)
        for (size_t x = 0; x < VGA_HEIGHT; ++x)
            buffer[y * VGA_WIDTH + x] = vga_entry(' ', color);
}

void Terminal::set_color(uint8_t color) { color = color; }

void Terminal::put_entry_at(char c, uint8_t color, size_t x, size_t y) {
    buffer[y * VGA_WIDTH + x] = vga_entry(c, color);
}

void Terminal::putchar(char c) {
    put_entry_at(c, color, column, row);
    if (++column == VGA_WIDTH) {
        column = 0;
        if (++row == VGA_HEIGHT)
            row = 0;
    }
}

void Terminal::write(char const *data, size_t size) {
    for (size_t i = 0; i < size; ++i) putchar(data[i]);
}

void Terminal::write_string(char const *data) { write(data, strlen(data)); }
