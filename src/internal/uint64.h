#ifndef UINT64_H
#define UINT64_H

#include <stdint.h>

uint64_t __udivdi3(uint64_t numerator, uint64_t denominator);

uint64_t __umoddi3(uint64_t numerator, uint64_t denominator);

uint64_t __udivmoddi4(uint64_t numerator, uint64_t denominator, uint64_t *reminder);

#endif //UINT64_H
