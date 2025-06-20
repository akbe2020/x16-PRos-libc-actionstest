#ifndef INT64_H
#define INT64_H

#include <stdint.h>

int64_t __divdi3(int64_t numerator, int64_t denominator);

int64_t __moddi3(int64_t numerator, int64_t denominator);

int64_t __divmoddi4(int64_t numerator, int64_t denominator, int64_t *reminder);

#endif //INT64_H
