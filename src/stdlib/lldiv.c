#include <stdlib.h>

lldiv_t lldiv(const long long num, const long long den) {
    return (lldiv_t) {
        num / den, num % den
    };
}
