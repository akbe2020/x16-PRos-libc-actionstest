#include <string.h>

char *strtok(char *restrict str, const char *restrict delim) {
    static char *last;
    if (str != NULL) {
        last = str;
    }
    if (last == NULL) {
        return NULL;
    }
    while (*last && strchr(delim, *last)) {
        last++;
    }
    if (*last == '\0') {
        return NULL;
    }
    char *tokstart = last;
    while (*last && !strchr(delim, *last)) {
        last++;
    }
    if (*last != '\0') {
        *last = '\0';
        last++;
    } else {
        last = NULL;
    }
    return tokstart;
}
