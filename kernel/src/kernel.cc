#include "../kernel/tty.hpp"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "wrong targat"
#endif

#if !defined(__i386__)
#error "wrong target. require i386"
#endif

void kernel_main_cpp() {
    Terminal term;
    term.write_string("Hello Kernel!\n");
}

extern "C" void kernel_main() { kernel_main_cpp(); }
