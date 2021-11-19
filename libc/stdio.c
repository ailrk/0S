#include <limits.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

int puts(char const *str) { return printf("%s\n", str); }

int putchar(int ic) {
#if defined(__is_libk)
    char c = (char)ic;
    terminal_write(&c, sizeof(c));
#else
    // TOOD implement write system call.
#endif
    return ic;
}

static print (char const *data, size_t length) {
    unsigned char const * bytes = (unsigned char const *) data;
    for (size_t i = 0; i < length; ++i) {
        if (putchar(bytes[i]) == EOF) return false;
    }
    return true;
}

int printf(char const* __restrict fmt, ...) {
    va_list parameters;
    va_start(parameters, fmt);

    int written = 0;

    while (*fmt!= '\0') {
        size_t maxrem = INT_MAX - written;
    }

    // TODO

}
