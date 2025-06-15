#ifndef LIMITS_H
#define LIMITS_H

#undef CHAR_BIT
#define CHAR_BIT __CHAR_BIT__

#ifndef MB_LEN_MAX
#define MB_LEN_MAX 1
#endif

#undef SCHAR_MIN
#define SCHAR_MIN (-SCHAR_MAX - 1)
#undef SCHAR_MAX
#define SCHAR_MAX __SCHAR_MAX__

#undef UCHAR_MAX
#if __SCHAR_MAX__ == __INT_MAX__
# define UCHAR_MAX (SCHAR_MAX * 2U + 1U)
#else
# define UCHAR_MAX (SCHAR_MAX * 2 + 1)
#endif

#ifdef __CHAR_UNSIGNED__
# undef CHAR_MIN
# if __SCHAR_MAX__ == __INT_MAX__
#  define CHAR_MIN 0U
# else
#  define CHAR_MIN 0
# endif
# undef CHAR_MAX
# define CHAR_MAX UCHAR_MAX
#else
# undef CHAR_MIN
# define CHAR_MIN SCHAR_MIN
# undef CHAR_MAX
# define CHAR_MAX SCHAR_MAX
#endif

#undef SHRT_MIN
#define SHRT_MIN (-SHRT_MAX - 1)
#undef SHRT_MAX
#define SHRT_MAX __SHRT_MAX__

#undef USHRT_MAX
#if __SHRT_MAX__ == __INT_MAX__
# define USHRT_MAX (SHRT_MAX * 2U + 1U)
#else
# define USHRT_MAX (SHRT_MAX * 2 + 1)
#endif

#undef INT_MIN
#define INT_MIN (-INT_MAX - 1)
#undef INT_MAX
#define INT_MAX __INT_MAX__

#undef UINT_MAX
#define UINT_MAX (INT_MAX * 2U + 1U)

#undef LONG_MIN
#define LONG_MIN (-LONG_MAX - 1L)
#undef LONG_MAX
#define LONG_MAX __LONG_MAX__

#undef ULONG_MAX
#define ULONG_MAX (LONG_MAX * 2UL + 1UL)

#undef LLONG_MIN
#define LLONG_MIN (-LLONG_MAX - 1LL)
#undef LLONG_MAX
#define LLONG_MAX __LONG_LONG_MAX__

# undef ULLONG_MAX
# define ULLONG_MAX (LLONG_MAX * 2ULL + 1ULL)

#undef LONG_LONG_MIN
#define LONG_LONG_MIN (-LONG_LONG_MAX - 1LL)
#undef LONG_LONG_MAX
#define LONG_LONG_MAX __LONG_LONG_MAX__

#undef ULONG_LONG_MAX
#define ULONG_LONG_MAX (LONG_LONG_MAX * 2ULL + 1ULL)

#endif //LIMITS_H
