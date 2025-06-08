#include <string.h>

char *strstr(const char *str, const char *substr) {
    const char *s = str;
    while (*s != '\0') {
        const char *s1 = s;
        const char *s2 = substr;
        while (*s1 && *s2 && *s1 == *s2) {
            s1++;
            s2++;
        }
        if (*s2 == '\0') {
            return (char *)s;
        }
        s++;
    }
    return NULL;
}
