#include <string.h>

char *strncat(char *restrict dst, const char *restrict src, const size_t n) {
    char *d = dst;
    while (*d++) {
    }
    for (size_t i = 0; i < n && src[i] != '\0'; i++) {
        d[i] = src[i];
    }
    return dst;
}
