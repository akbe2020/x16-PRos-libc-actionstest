#include <stdlib.h>

ldiv_t ldiv(const long num, const long den) {
    return (ldiv_t) {
        num / den, num % den
    };
}
