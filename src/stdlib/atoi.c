#include <stdlib.h>
#include <ctype.h>

int atoi(const char *str) {
    int n = 0, neg = 0;
    while (isspace(*str)) {
        str++;
    }
    switch (*str) {
        case '-': neg = 1;
        case '+': str++;
        default: ;
    }
    // Compute n as a negative number to avoid overflow on INT_MIN
    while (isdigit(*str)) {
        n = 10 * n - (*str++ - '0');
    }
    return neg ? n : -n;
}
