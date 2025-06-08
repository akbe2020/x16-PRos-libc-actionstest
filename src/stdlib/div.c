#include <stdlib.h>

div_t div(const int num, const int den) {
    return (div_t) {
        num / den, num % den
    };
}
