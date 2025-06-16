#include <stdio.h>

FILE __stdin;
FILE __stdout;
FILE __stderr;

FILE *stdin  = &__stdin;
FILE *stdout = &__stdout;
FILE *stderr = &__stderr;

char getchar(void) {
    char result;
    __asm__ __volatile__ (
        "mov $0x00, %%ah\n"
        "int $0x16\n"
        : "=a" (result)
        : :
    );
    putchar(result);
    return result;
}

int putchar(char c) {
    __asm__ __volatile__ (
        "mov $0x0E, %%ah\n"
        "mov %0, %%al\n"
        "mov $0x00, %%bh\n"
        "mov $0x0F, %%bl\n"
        "int $0x10"
        : : "r" (c)
        : "%ah", "%al", "%bh", "%bl"
    );
    return EOF;
}

int puts(const char *s)
{
    while (*s) {
        putchar(*s++);
    }

    putchar('\n');
    putchar('\r');
    return EOF;
}