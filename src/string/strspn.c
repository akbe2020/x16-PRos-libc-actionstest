#include <string.h>

size_t strspn(const char *dst, const char *src) {
    for (size_t i = 0; src[i] != '\0'; i++) {
        if (strchr(dst, src[i]) == NULL) {
            return i;
        }
    }
    return 0;
}
