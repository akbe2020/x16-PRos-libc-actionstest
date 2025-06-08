#include <ctype.h>

int islower(const int c) {
    return (unsigned) c - 'a' < 26;
}
