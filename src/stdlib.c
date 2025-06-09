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

long atol(const char *str) {
    long n = 0;
    int neg = 0;
    while (isspace(*str)) {
        str++;
    }
    switch (*str) {
        case '-': neg = 1;
        case '+': str++;
        default: ;
    }
    // Compute n as a negative number to avoid overflow on LONG_MIN
    while (isdigit(*str)) {
        n = 10 * n - (*str++ - '0');
    }
    return neg ? n : -n;
}

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

int abs(const int x) {
    return x >= 0 ? x : -x;
}

long labs(const long x) {
    return x >= 0 ? x : -x;
}

long long llabs(const long long x) {
    return x >= 0 ? x : -x;
}

div_t div(const int num, const int den) {
    return (div_t) {
        num / den, num % den
    };
}

ldiv_t ldiv(const long num, const long den) {
    return (ldiv_t) {
        num / den, num % den
    };
}

lldiv_t lldiv(const long long num, const long long den) {
    return (lldiv_t) {
        num / den, num % den
    };
}
