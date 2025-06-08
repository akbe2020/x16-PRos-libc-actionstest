#include <string.h>

int strcoll(const char *lhs, const char *rhs) {
    return strcmp(lhs, rhs); // ignore localization
}
