#include <string.h>

char *strrchr(const char *src, const int ch) {
    const char *s = src;
    const char *c = NULL;
    for (; *s != '\0'; s++) {
        if (*s == ch) {
            c = s;
        }
    }
    return (char *)c;
}
