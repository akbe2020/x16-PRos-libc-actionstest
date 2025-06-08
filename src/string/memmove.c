#include <string.h>

void *memmove(void *dst, const void *src, const size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    if (d == s) {
        return dst;
    }
    if (d < s) {
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else {
        for (size_t i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }
    return dst;
}
