#include <ctype.h>

int toupper(const int c) {
    if (isupper(c)) {
        return c & 0x5f;
    }
    return c;
}
