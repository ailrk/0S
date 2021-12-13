#pragma once

#include "cdefs.h"
#ifdef __cplusplus
extern "C" {
#endif

int printf(char const *__restrict, ...);
int putchar(int);
int puts(char const *);
int printf(const char *__restrict, ...);

#ifdef __cplusplus
}
#endif
