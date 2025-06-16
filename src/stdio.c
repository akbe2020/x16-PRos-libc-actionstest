#include <stdio.h>
#include <stdarg.h>
#include <string.h>

FILE __stdin;
FILE __stdout;
FILE __stderr;

FILE *stdin = &__stdin;
FILE *stdout = &__stdout;
FILE *stderr = &__stderr;

char printbuf[2048];

/////////////////////////////////////////////
//          helper functions
/////////////////////////////////////////////

char __bool_is_digit(const char c) {
    return c >= '0' && c <= '9';
}

int parse_int(const char **s) {
    int value = 0;
    while (__bool_is_digit(**s)) {
        value = value * 10 + (**s - '0');
        (*s)++;
    }
    return value;
}

char *__number_conversion(
    char *buf,
    unsigned long num,
    const int base,
    const int width,
    const int precision,
    const char left_align,
    const char zero_pad,
    const char upper_case,
    const char negative,
    const char space_if_no_sign,
    const char alternate_form
) {
    const char *digits = upper_case ? "0123456789ABCDEF" : "0123456789abcdef";
    char tmp[32];
    int pos = 0;

    // Handle zero cases
    if (num == 0) {
        tmp[pos++] = '0';
    } else {
        // Convert number to string in reverse order
        while (num != 0) {
            const unsigned long rem = num % base;
            num /= base;
            tmp[pos++] = digits[rem];
        }
    }

    // Apply precision (minimum digits)
    while (pos < precision) {
        tmp[pos++] = '0';
    }

    // Calculate padding
    int pad_len = width - pos;
    if (negative || space_if_no_sign) pad_len--;
    if (alternate_form && base == 16) pad_len -= 2;

    // Right alignment padding
    if (!left_align && pad_len > 0) {
        memset(buf, zero_pad ? '0' : ' ', pad_len);
        buf += pad_len;
    }

    // Sign handling
    if (negative) {
        *buf++ = '-';
    } else if (space_if_no_sign) {
        *buf++ = ' ';
    }

    // Alternate form prefix
    if (alternate_form) {
        if (base == 16) {
            *buf++ = '0';
            *buf++ = upper_case ? 'X' : 'x';
        } else if (base == 8) {
            *buf++ = '0';
        }
    }

    // Write digits in the correct order
    while (--pos >= 0) {
        *buf++ = tmp[pos];
    }

    // Left alignment padding
    if (left_align && pad_len > 0) {
        memset(buf, ' ', pad_len);
        buf += pad_len;
    }

    return buf;
}

/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////

int printf(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    const int i = vsprintf(printbuf, fmt, args);
    va_end(args);

    const char *p = printbuf;
    for (int j = 0; j < i; j++) {
        putchar(*p++);
    }

    return i;
}

int vsprintf(char *buf, const char *fmt, const va_list args) {
    const char *start = buf;

    while (*fmt) {
        if (*fmt != '%') {
            *buf++ = *fmt++;
            continue;
        }

        fmt++; // Skip '%'

        // Parse flags
        char left_align = 0;
        char show_sign = 0;
        char space_if_no_sign = 0;
        char alternate_form = 0;
        char zero_pad = 0;

        while (1) {
            switch (*fmt) {
                case '-': left_align = 1;
                    fmt++;
                    continue;
                case '+': show_sign = 1;
                    fmt++;
                    continue;
                case ' ': space_if_no_sign = 1;
                    fmt++;
                    continue;
                case '#': alternate_form = 1;
                    fmt++;
                    continue;
                case '0': zero_pad = 1;
                    fmt++;
                    continue;
                default:
                    break;
            }
            break;
        }

        // Parse field width
        int width = 0;
        if (__bool_is_digit(*fmt)) {
            width = parse_int(&fmt);
        } else if (*fmt == '*') {
            width = va_arg(args, int);
            fmt++;
            if (width < 0) {
                width = -width;
                left_align = 1;
            }
        }

        // Parse precision
        int precision = -1;
        if (*fmt == '.') {
            fmt++;
            if (__bool_is_digit(*fmt)) {
                precision = parse_int(&fmt);
            } else if (*fmt == '*') {
                precision = va_arg(args, int);
                fmt++;
            }
            if (precision < 0) precision = 0;
        }

        // Handle conversion specifier
        switch (*fmt) {
            case 'c': {
                char c = (char) va_arg(args, int);
                *buf++ = c;
                break;
            }

            case 's': {
                const char *s = va_arg(args, const char *);
                int len = s ? strlen(s) : 0;
                if (precision >= 0 && len > precision) {
                    len = precision;
                }

                if (!left_align && width > len) {
                    memset(buf, ' ', width - len);
                    buf += width - len;
                }

                if (s) {
                    memcpy(buf, s, len);
                    buf += len;
                }

                if (left_align && width > len) {
                    memset(buf, ' ', width - len);
                    buf += width - len;
                }
                break;
            }

            case 'd':
            case 'i': {
                const long num = va_arg(args, long);
                const char negative = num < 0;
                const unsigned long unum = negative ? -num : num;

                buf = __number_conversion(
                    buf, unum, 10, width, precision,
                    left_align, zero_pad, 0,
                    negative,
                    space_if_no_sign && !negative && !show_sign,
                    alternate_form
                );
                break;
            }

            case 'f':
            case 'F': {
                float f = (float) va_arg(args, double);
                char temp[1024];
                if (precision < 0) precision = 6;

                // Handle negative numbers properly
                const int is_negative = f < 0;
                if (is_negative) f = -f;

                // Round the number according to precision
                float round_offset = 0.5f;
                for (int i = 0; i < precision; i++) round_offset /= 10.0f;
                f += round_offset;

                int whole = (int) f;
                float fraction = f - (float) whole;

                // Handle the whole part
                char *ptr = temp;
                if (whole == 0 && is_negative) {
                    *ptr++ = '-';
                    *ptr++ = '0';
                } else if (whole == 0) {
                    *ptr++ = '0';
                } else {
                    // Handle negative sign
                    if (is_negative) {
                        *ptr++ = '-';
                    }
                    // Convert whole part (reversed)
                    char *start = ptr;
                    while (whole > 0) {
                        *ptr++ = whole % 10 + '0';
                        whole /= 10;
                    }
                    // Reverse the whole part string
                    char *end = ptr - 1;
                    while (start < end) {
                        const char tmp = *start;
                        *start = *end;
                        *end = tmp;
                        start++;
                        end--;
                    }
                }

                // Handle fraction part
                if (precision > 0) {
                    *ptr++ = '.';
                    while (precision-- > 0) {
                        fraction *= 10;
                        const int digit = (int) fraction;
                        *ptr++ = digit + '0';
                        fraction -= digit;
                    }
                }
                *ptr = '\0';

                const int len = strlen(temp);

                if (!left_align && width > len) {
                    memset(buf, ' ', width - len);
                    buf += width - len;
                }

                memcpy(buf, temp, len);
                buf += len;

                if (left_align && width > len) {
                    memset(buf, ' ', width - len);
                    buf += width - len;
                }
                break;
            }

            case 'u': {
                const unsigned long num = va_arg(args, unsigned long);
                buf = __number_conversion(
                    buf, num, 10, width, precision,
                    left_align, zero_pad, 0,
                    show_sign, space_if_no_sign,
                    alternate_form
                );
                break;
            }

            case 'x':
            case 'X': {
                const unsigned long num = va_arg(args, unsigned long);
                buf = __number_conversion(
                    buf, num, 16, width, precision,
                    left_align, zero_pad, (*fmt == 'X'),
                    show_sign, space_if_no_sign,
                    alternate_form
                );
                break;
            }

            case 'o': {
                const unsigned long num = va_arg(args, unsigned long);
                buf = __number_conversion(
                    buf, num, 8, width, precision,
                    left_align, zero_pad, 0,
                    show_sign, space_if_no_sign,
                    alternate_form
                );
                break;
            }

            case 'p': {
                void *ptr = va_arg(args, void *);
                buf = __number_conversion(
                    buf, (unsigned long) ptr, 16,
                    width >= 0 ? width : 2 * sizeof(void *),
                    precision,
                    left_align, 1, 0,
                    0, 0, 1
                );
                break;
            }

            case '%':
                *buf++ = '%';
                break;

            default:
                // Unknown specifier, copy
                *buf++ = '%';
                *buf++ = *fmt;
                break;
        }

        if (*fmt) fmt++;
    }

    *buf = '\0';
    return buf - start;
}

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

int puts(const char *s) {
    while (*s) {
        putchar(*s++);
    }

    putchar('\n');
    putchar('\r');
    return EOF;
}
