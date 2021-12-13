#include "tty.hpp"

// sample C++ function.
// We need to establish a stack from the bool sector to run this function.
int kmain_c_plus_plus(void) {
    Terminal term;

    term.write("Welcome to 0S\n", 14);

    return 0;
}

extern "C" int kmain() { return kmain_c_plus_plus(); }
