#include "int64.h"

int64_t __divdi3(const int64_t numerator, const int64_t denominator) {
    int neg = 0;
    uint64_t ua, ub;
    if (numerator < 0) {
        ua = -(uint64_t) numerator;
        neg ^= 1;
    } else ua = (uint64_t) numerator;
    if (denominator < 0) {
        ub = -(uint64_t) denominator;
        neg ^= 1;
    } else ub = (uint64_t) denominator;

    const uint64_t uq = ua / ub;
    const int64_t q = (int64_t) uq;
    return neg ? -q : q;
}

int64_t __moddi3(const int64_t numerator, const int64_t denominator) {
    const uint64_t ua = numerator < 0 ? -(uint64_t) numerator : (uint64_t) numerator;
    const uint64_t ub = denominator < 0 ? -(uint64_t) denominator : (uint64_t) denominator;
    const uint64_t ur = ua % ub;
    const int64_t rem = (int64_t) ur;
    return numerator < 0 ? -rem : rem;
}

int64_t __divmoddi4(const int64_t numerator, const int64_t denominator, int64_t *remainder) {
    *remainder = numerator % denominator;
    return numerator / denominator;
}
