#include <string.h>

void *memchr(const void *src, int ch, size_t n) {
    const unsigned char *s = src;
    ch = (unsigned char) ch;
    for (; n && *s != ch; s++, n--) {
    }
    return n ? (void *) s : NULL;
}
