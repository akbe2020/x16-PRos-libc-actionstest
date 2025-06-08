#include <ctype.h>

int isprint(const int c) {
    return (unsigned) c - 0x20 < 0x5f;
}
