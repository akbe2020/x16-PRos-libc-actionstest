#ifndef STDLIB_H
#define STDLIB_H

#include <types.h>

int atoi (const char *); // todo
long atol (const char *); // todo
long long atoll (const char *); // todo: use atol()
double atof (const char *); // not planned

float strtof (const char *__restrict, char **__restrict); // not planned
double strtod (const char *__restrict, char **__restrict); // not planned
long double strtold (const char *__restrict, char **__restrict); // not planned

long strtol (const char *__restrict, char **__restrict, int); // todo
unsigned long strtoul (const char *__restrict, char **__restrict, int); // todo
long long strtoll (const char *__restrict, char **__restrict, int); // todo: use strtol()
unsigned long long strtoull (const char *__restrict, char **__restrict, int); // todo: use strtoul()

int rand (void); // optional
void srand (unsigned); // optional

void *malloc (size_t); // not planned
void *calloc (size_t, size_t); // not planned
void *realloc (void *, size_t); // not planned
void free (void *); // not planned

void abort (void); // todo
int atexit (void (*) (void)); // not planned
void exit (int); // todo
void _Exit (int); // not planned

char *getenv (const char *); // not planned

int system (const char *); // not planned

void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *)); // optional
void qsort (void *, size_t, size_t, int (*)(const void *, const void *)); // optional

int abs (int); // todo
long labs (long); // todo
long long llabs (long long); // todo: use lasb()

typedef struct {
    int quot, rem;
} div_t;
typedef struct {
    long quot, rem;
} ldiv_t;
typedef struct {
    long long quot, rem;
} lldiv_t;

div_t div (int, int); // todo
ldiv_t ldiv (long, long); // todo
lldiv_t lldiv (long long, long long); // todo: use ldiv()

int mblen (const char *, size_t); // not planned
int mbtowc (wchar_t *__restrict, const char *__restrict, size_t); // not planned
int wctomb (char *, wchar_t); // not planned
size_t mbstowcs (wchar_t *__restrict, const char *__restrict, size_t); // not planned
size_t wcstombs (char *__restrict, const wchar_t *__restrict, size_t); // not planned

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#endif //STDLIB_H
