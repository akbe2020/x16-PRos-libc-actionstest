#include <ctype.h>

int ispunct(const int c) {
    return isgraph(c) && !isalnum(c);
}
