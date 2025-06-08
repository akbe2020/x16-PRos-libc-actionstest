#include <string.h>

char *strchr(const char *src, const int ch) {
    const char *s = src;
    while (*s++ != ch && *s != '\0') {
    }
    if (*s == ch) {
        return (char *) s;
    }
    return NULL;
}
