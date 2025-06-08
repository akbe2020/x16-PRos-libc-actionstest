#include <stdlib.h>
#include <ctype.h>

long long atoll(const char *str) {
    long long n = 0;
    int neg = 0;
    while (isspace(*str)) {
        str++;
    }
    switch (*str) {
        case '-': neg = 1;
        case '+': str++;
        default: ;
    }
    // Compute n as a negative number to avoid overflow on LLONG_MIN
    while (isdigit(*str)) {
        n = 10 * n - (*str++ - '0');
    }
    return neg ? n : -n;
}
