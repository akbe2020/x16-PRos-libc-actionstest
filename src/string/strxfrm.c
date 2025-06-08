#include <string.h>

size_t strxfrm(char *dest, const char *src, const size_t n) {
    const size_t l = strlen(src);
    if (n > 1) {
        strcpy(dest, src);
    }
    return l; // ignore localization
}
