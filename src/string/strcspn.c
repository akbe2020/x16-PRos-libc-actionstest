#include <string.h>

size_t strcspn(const char *dst, const char *src) {
    for (size_t i = 0; src[i] != '\0'; i++) {
        if (strchr(dst, src[i])) {
            return i;
        }
    }
    return 0;
}
