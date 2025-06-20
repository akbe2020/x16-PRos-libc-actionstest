#include "uint64.h"

uint64_t __udivdi3(const uint64_t numerator, const uint64_t denominator) {
    uint64_t q = 0;
    uint64_t r = 0;
    for (int i = 63; i >= 0; i--) {
        r = (r << 1) | ((numerator >> i) & 1);
        if (r >= denominator) {
            r -= denominator;
            q |= (uint64_t)1 << i;
        }
    }
    return q;
}

uint64_t __umoddi3(const uint64_t numerator, const uint64_t denominator) {
    uint64_t r = 0;
    for (int i = 63; i >= 0; i--) {
        r = (r << 1) | ((numerator >> i) & 1);
        if (r >= denominator) {
            r -= denominator;
        }
    }
    return r;
}

uint64_t __udivmoddi4(const uint64_t numerator, const uint64_t denominator, uint64_t *reminder) {
    *reminder = numerator % denominator;
    return numerator / denominator;
}
