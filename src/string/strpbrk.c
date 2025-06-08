#include <string.h>

char *strpbrk(const char *dst, const char *brkset) {
    const char *d = dst;
    while (*dst != '\0') {
        if (*dst == *brkset) {
            return (char *)d;
        }
    }
    return NULL;
}
