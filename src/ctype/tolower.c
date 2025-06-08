#include <ctype.h>

int tolower(const int c) {
    if (isupper(c)) {
        return c | 32;
    }
    return c;
}
