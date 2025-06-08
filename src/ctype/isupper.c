#include <ctype.h>

int isupper(const int c) {
    return (unsigned) c - 'A' < 26;
}
