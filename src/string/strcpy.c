#include <string.h>

char *strcpy(char *restrict dst, const char *restrict src) {
    char *d = dst;
    const char *s = src;
    while ((*d++ = *s++)) {
    }
    return dst;
}
