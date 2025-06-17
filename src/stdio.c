#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

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

int printf(const char *format, ...) {
    va_list args;

    va_start(args, format);
    const int i = vsprintf(printbuf, format, args);
    va_end(args);

    const char *p = printbuf;
    for (int j = 0; j < i; j++) {
        putchar(*p++);
    }

    return i;
}

int sprintf(const char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int ret = vsprintf(str, format, args);
    va_end(args);
    return ret;
}

int snprintf(const char *str, size_t size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int ret = vsnprintf(str, size, format, args);
    va_end(args);
    return ret;
}

int vprintf(const char *format, va_list ap) {
    int len = vsprintf(printbuf, format, ap);
    const char *p = printbuf;
    for (int i = 0; i < len; i++) {
        putchar(*p++);
    }
    return len;
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
                const char c = (char) va_arg(args, int);
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

int vsnprintf(char *str, const size_t size, const char *format, va_list ap) {
    va_list ap2;
    va_copy(ap2, ap);
    // Use global printbuf to format the entire string
    const int total_len = vsprintf(printbuf, format, ap2);
    va_end(ap2);

    if (size > 0) {
        // Determine how much to copy
        size_t to_copy = total_len;
        if (to_copy >= size) {
            to_copy = size - 1;
        }
        memcpy(str, printbuf, to_copy);
        str[to_copy] = '\0';
    }

    return total_len;
}

int scanf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char buffer[1024];
    int buffer_pos = 0;
    int c;

    while (buffer_pos < sizeof(buffer) - 1 && 
          (c = getchar()) != '\r' && c != '\n') {
        buffer[buffer_pos++] = (char)c;
    }
    
    buffer[buffer_pos] = '\0';
    if (c == EOF && buffer_pos == 0) {
        va_end(args);
        return EOF;
    }
    
    int count = vsscanf(buffer, format, args);
    va_end(args);
    
    return count;
}

int sscanf(const char *str, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    int count = vsscanf(str, format, ap);
    va_end(ap);
    return count;
}

int vsscanf(const char *str, const char *format, va_list ap) {
    int count = 0;
    const char *p = str;

    while (*format) {
        // skip whitespace in format
        if (isspace((unsigned char)*format)) {
            while (isspace((unsigned char)*p)) p++;
            format++;
            continue;
        }

        // match non-format characters
        if (*format != '%') {
            if (*p != *format) break;
            p++;
            format++;
            continue;
        }

        format++;  // skip '%'
        int suppress = 0;
        if (*format == '*') {
            suppress = 1;
            format++;
        }

        int width = -1;
        if (isdigit((unsigned char)*format)) {
            width = 0;
            while (isdigit((unsigned char)*format)) {
                width = width * 10 + (*format - '0');
                format++;
            }
        }

        switch (*format) {
            // integer
            case 'd': case 'i': case 'o': case 'u': case 'x': case 'X': {
                int base = 0;
                int sign = 1;
                
                if (*format == 'd' || *format == 'i') base = 10;
                else if (*format == 'o') base = 8;
                else if (*format == 'u') base = 10;
                else if (*format == 'x' || *format == 'X') base = 16;
                
                while (isspace((unsigned char)*p)) p++;
                
                int max_chars = (width == -1) ? 1000000 : width;
                const char *start = p;
                
                // negative
                if (max_chars > 0 && (*p == '+' || *p == '-')) {
                    if (*p == '-') sign = -1;
                    p++;
                    max_chars--;
                }
                
                if (base == 0) {
                    if (max_chars > 0 && *p == '0') {
                        p++;
                        max_chars--;
                        if (max_chars > 0 && (*p == 'x' || *p == 'X')) {
                            base = 16;
                            p++;
                            max_chars--;
                        } else {
                            base = 8;
                        }
                    } else {
                        base = 10;
                    }
                } else if (base == 16 && max_chars >= 2 && 
                          p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
                    p += 2;
                    max_chars -= 2;
                }
                
                unsigned long value = 0;
                int any_digit = 0;
                
                while (max_chars > 0 && *p) {
                    char c = *p;
                    int digit = -1;
                    
                    if (c >= '0' && c <= '9') digit = c - '0';
                    else if (base > 10) {
                        if (c >= 'a' && c <= 'f') digit = c - 'a' + 10;
                        else if (c >= 'A' && c <= 'F') digit = c - 'A' + 10;
                    }
                    
                    if (digit < 0 || digit >= base) break;
                    
                    value = value * base + digit;
                    any_digit = 1;
                    p++;
                    max_chars--;
                }
                
                if (!any_digit) goto end;
                long result = sign * (long)value;
                
                if (!suppress) {
                    int *ptr = va_arg(ap, int*);
                    *ptr = (int)result;
                    count++;
                }
                break;
            }
            
            case 'f':
            case 'F': {
                while (isspace((unsigned char)*p)) p++;
                
                int max = (width == -1) ? 1000000 : width;
                const char *start = p;
                int sign = 1;
                
                // negative
                if (max > 0 && (*p == '+' || *p == '-')) {
                    if (*p == '-') sign = -1;
                    p++;
                    max--;
                }
                
                float value = 0.0f;
                int any_digit = 0;
                
                // base
                while (max > 0 && isdigit(*p)) {
                    value = value * 10.0f + (*p - '0');
                    p++;
                    max--;
                    any_digit = 1;
                }
                
                // fractional
                if (max > 0 && *p == '.') {
                    p++;
                    max--;
                    float frac = 0.0f;
                    float divisor = 1.0f;
                    
                    while (max > 0 && isdigit(*p)) {
                        frac = frac * 10.0f + (*p - '0');
                        divisor *= 10.0f;
                        p++;
                        max--;
                        any_digit = 1;
                    }
                    
                    if (divisor > 1.0f) {
                        value += frac / divisor;
                    }
                }
                
                // exponent
                if (any_digit && max > 0 && (*p == 'e' || *p == 'E')) {
                    p++;
                    max--;
                    int exp_sign = 1;
                    
                    if (max > 0 && (*p == '+' || *p == '-')) {
                        if (*p == '-') exp_sign = -1;
                        p++;
                        max--;
                    }
                    
                    int exp_val = 0;
                    int exp_digits = 0;
                    
                    while (max > 0 && isdigit(*p)) {
                        exp_val = exp_val * 10 + (*p - '0');
                        p++;
                        max--;
                        exp_digits++;
                    }
                    
                    if (exp_digits) {
                        if (exp_sign < 0) exp_val = -exp_val;
                        
                        if (exp_val > 0) {
                            while (exp_val-- > 0) value *= 10.0f;
                        } else if (exp_val < 0) {
                            while (exp_val++ < 0) value /= 10.0f;
                        }
                    }
                }
                
                if (!any_digit) {
                    p = start;
                    goto end;
                }
                
                value *= sign;
                
                if (!suppress) {
                    float *dest = va_arg(ap, float*);
                    *dest = value;
                    count++;
                }
                break;
            }
            
            case 'c': {
                int read_count = (width == -1) ? 1 : width;
                
                if (!suppress) {
                    char *dest = va_arg(ap, char*);
                    for (int i = 0; i < read_count && *p; i++) {
                        *dest++ = *p++;
                    }
                    count++;
                } else {
                    for (int i = 0; i < read_count && *p; i++) p++;
                }
                break;
            }
            
            case 's': {
                while (isspace((unsigned char)*p)) p++;
                
                int max = (width == -1) ? 1000000 : width;
                if (!suppress) {
                    char *dest = va_arg(ap, char*);
                    while (max > 0 && *p && !isspace((unsigned char)*p)) {
                        *dest++ = *p++;
                        max--;
                    }
                    *dest = '\0';
                    count++;
                } else {
                    while (max > 0 && *p && !isspace((unsigned char)*p)) {
                        p++;
                        max--;
                    }
                }
                break;
            }
            
            case 'p': {
                while (isspace((unsigned char)*p)) p++;
                
                int max_chars = (width == -1) ? 1000000 : width;
                if (max_chars >= 2 && p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
                    p += 2;
                    max_chars -= 2;
                }
                
                unsigned long value = 0;
                int any_digit = 0;
                
                while (max_chars > 0 && *p) {
                    char c = *p;
                    int digit = -1;
                    
                    if (c >= '0' && c <= '9') digit = c - '0';
                    else if (c >= 'a' && c <= 'f') digit = c - 'a' + 10;
                    else if (c >= 'A' && c <= 'F') digit = c - 'A' + 10;
                    
                    if (digit < 0) break;
                    
                    value = value * 16 + digit;
                    any_digit = 1;
                    p++;
                    max_chars--;
                }
                
                if (!any_digit) goto end;
                if (!suppress) {
                    void **ptr = va_arg(ap, void**);
                    *ptr = (void*)(unsigned long)value;
                    count++;
                }
                break;
            }
            
            // count
            case 'n': {
                if (!suppress) {
                    int *ptr = va_arg(ap, int*);
                    *ptr = (int)(p - str);
                }
                break;
            }
            
            case '%': {
                if (*p != '%') goto end;
                p++;
                break;
            }
            
            default:
                goto end;
        }
        format++;
    }

end:
    return count;
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
