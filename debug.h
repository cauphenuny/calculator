#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG

#include <cstdio>

#define logl(fmt, ...) \
    fprintf(stderr, "%s:%d, %s: " fmt "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
#else

#define logl(...)

#endif

#endif
