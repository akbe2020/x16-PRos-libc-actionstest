#ifndef STDIO_H
#define STDIO_H

// #include <stdarg.h>
#include <stddef.h>
#include <stdarg.h>

#ifndef EOF
#define EOF (-1)
#endif

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef struct FILE {
    int fd;
    int flags;
    unsigned char *buf;
    size_t buf_size;
    size_t buf_pos;
} FILE;

// extern FILE *stdin; // todo
// extern FILE *stdout; // todo
// extern FILE *stderr; // todo

int printf(const char *format, ...);
// int fprintf(FILE *stream, const char *format, ...); // todo
// int sprintf(char *str, const char *format, ...); // todo
// int snprintf(char *str, size_t size, const char *format, ...); // todo

// int vprintf(const char *format, va_list ap); // todo
// int vfprintf(FILE *stream, const char *format, va_list ap); // todo
int vsprintf(char *buf, const char *fmt, va_list args);
// int vsnprintf(char *str, size_t size, const char *format, va_list ap); // todo

// int scanf(const char *format, ...); // todo
// int fscanf(FILE *stream, const char *format, ...); // todo
// int sscanf(const char *str, const char *format, ...); // todo

// int vscanf(const char *format, va_list ap); // todo
// int vfscanf(FILE *stream, const char *format, va_list ap); // todo
// int vsscanf(const char *str, const char *format, va_list ap); // todo

// FILE *fopen(const char *path, const char *mode); // todo
// int fclose(FILE *stream); // todo
// int fflush(FILE *stream); // todo
// int remove(const char *path); // todo
// int rename(const char *oldpath, const char *newpath); // todo

// size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream); // todo
// size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream); // todo

// int fgetc(FILE *stream); // todo
// int getc(FILE *stream); // todo
char getchar(void);

// int fputc(int c, FILE *stream); // todo
// int putc(int c, FILE *stream); // todo
int putchar(char c);

// char *fgets(char *s, int size, FILE *stream); // todo
// int fputs(const char *s, FILE *stream); // todo
int puts(const char *s);

// int fseek(FILE *stream, long offset, int whence); // todo
// long ftell(FILE *stream); // todo
// void rewind(FILE *stream); // todo

// int feof(FILE *stream); // todo
// int ferror(FILE *stream); // todo
// void clearerr(FILE *stream); // todo

// void perror(const char *s); // todo

#endif //STDIO_H