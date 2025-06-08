#include <string.h>

void *memcpy(void *restrict dst, const void *restrict src, size_t const n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dst;
}
