#include <ctype.h>

int isgraph(const int c) {
    return (unsigned) c - 0x21 < 0x5e;
}
