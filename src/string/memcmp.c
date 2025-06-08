#include <string.h>

int memcmp(const void *lhs, const void *rhs, size_t n) {
    const unsigned char *l = lhs, *r = rhs;
    for (; n && *l == *r; n--, l++, r++) {
    }
    return n ? *l - *r : 0;
}
