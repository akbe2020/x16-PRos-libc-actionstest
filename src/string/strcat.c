#include <string.h>

char *strcat(char *restrict dst, const char *restrict src) {
    char *d = dst;
    const char *s = src;
    while (*d++) {
    }
    while ((*d++ = *s++)) {
    }
    return dst;
}
