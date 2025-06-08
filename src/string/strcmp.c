#include <string.h>

int strcmp(const char *lhs, const char *rhs) {
    for (; *lhs == *rhs && *lhs; lhs++, rhs++) {
    }
    return *(unsigned char *)lhs - *(unsigned char *)rhs;
}
