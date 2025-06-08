#include <string.h>

void *memset(void *dst, int const ch, size_t const n) {
    unsigned char *d = dst;
    for (size_t i = 0; i < n; i++) {
        d[i] = ch;
    }
    return dst;
}
