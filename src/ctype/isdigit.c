#include <ctype.h>

int isdigit(const int c) {
    return (unsigned) c - '0' < 10;
}
