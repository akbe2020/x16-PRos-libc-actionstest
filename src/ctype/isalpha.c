#include <ctype.h>

int isalpha(const int c) {
    return ((unsigned) c | 32) - 'a' < 26;
}
