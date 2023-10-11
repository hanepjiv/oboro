/** -*- mode:c; coding:utf-8-unix; -*-
 *  @file debug.h
 *  @brief debug.h
 *
 *  debug.h
 *
 *  Copyright 2014 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @copyright The MIT License (MIT)
 *  @since 2015/05/29
 *  @date 2023/10/10
 */

#ifndef OBORO_DEBUG_H_
#define OBORO_DEBUG_H_

/* ///////////////////////////////////////////////////////////////////////// */
/* ========================================================================= */
#if (defined(DEBUG) && !defined(OBORO_DEBUG))
# define OBORO_DEBUG
#endif
/* ========================================================================= */
#if (defined(NDEBUG) && defined(OBORO_DEBUG))
# undef OBORO_DEBUG
#endif
/* ========================================================================= */
#define OBORO_VERBOSITY_00              (0x00)
#define OBORO_VERBOSITY_01              (0x3F)
#define OBORO_VERBOSITY_02              (0x7F)
#define OBORO_VERBOSITY_03              (0xBF)
#define OBORO_VERBOSITY_04              (0xFF)
/* ------------------------------------------------------------------------- */
#define OBORO_VERBOSITY_DEBUG           OBORO_VERBOSITY_00
#define OBORO_VERBOSITY_INFO            OBORO_VERBOSITY_01
#define OBORO_VERBOSITY_WARNING         OBORO_VERBOSITY_02
#define OBORO_VERBOSITY_ERROR           OBORO_VERBOSITY_03
#define OBORO_VERBOSITY_CRITICAL        OBORO_VERBOSITY_04
/* ------------------------------------------------------------------------- */
#define OBORO_VERBOSITY_ALL             OBORO_VERBOSITY_DEBUG
#define OBORO_VERBOSITY_DEFAULT         OBORO_VERBOSITY_INFO
#define OBORO_VERBOSITY_QUIET           OBORO_VERBOSITY_CRITICAL
/* ///////////////////////////////////////////////////////////////////////// */
#ifdef OBORO_DEBUG
/* ------------------------------------------------------------------------- */
# if !defined(OBORO_VERBOSITY)
#   define OBORO_VERBOSITY              OBORO_VERBOSITY_DEBUG
# endif
/* ========================================================================= */
# ifdef __cplusplus
#   include <cstdio>
#   include <cstdlib>
#   include <cstdarg>
#   define OBORO_USING_NAMESPACE_STD using namespace std
# else  /* !__cplusplus */
#   include <stdio.h>
#   include <stdlib.h>
#   include <stdarg.h>
#   define OBORO_USING_NAMESPACE_STD
# endif  /* !__cplusplus */
/* ========================================================================= */
# define OBORO_TRACE_II(d)                                      \
  do {                                                          \
    OBORO_USING_NAMESPACE_STD;                                  \
    fprintf(stderr, "%s(%i) : " d "\n", __FILE__, __LINE__);    \
    fflush(stderr);                                             \
  } while (0)
# define OBORO_TRACE_I(d) OBORO_TRACE_II(d)
# define OBORO_TRACE(d) OBORO_TRACE_I(d)
/* ------------------------------------------------------------------------- */
# define OBORO_TRACE_VERBOSITY_II(l, d)                                 \
  do { if (OBORO_VERBOSITY <= (l)) { OBORO_TRACE(d); } } while (0)
# define OBORO_TRACE_VERBOSITY_I(l, d) OBORO_TRACE_VERBOSITY_II(l, d)
# define OBORO_TRACE_VERBOSITY(l, d) OBORO_TRACE_VERBOSITY_I(l, d)
/* ------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&               \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_DEBUG)
#   define OBORO_TRACE_DEBUG_II(d) OBORO_TRACE(d)
#   define OBORO_TRACE_DEBUG_I(d) OBORO_TRACE_DEBUG_II(d)
#   define OBORO_TRACE_DEBUG(d) OBORO_TRACE_DEBUG_I(d)
# else
#   define OBORO_TRACE_DEBUG(d) (void)(0)
# endif
/* ------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&               \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_INFO)
#   define OBORO_TRACE_INFO_II(d) OBORO_TRACE(d)
#   define OBORO_TRACE_INFO_I(d) OBORO_TRACE_INFO_II(d)
#   define OBORO_TRACE_INFO(d) OBORO_TRACE_INFO_I(d)
# else
#   define OBORO_TRACE_INFO(d) (void)(0)
# endif
/* ------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                       \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_WARNING)
#   define OBORO_TRACE_WARNING_II(d) OBORO_TRACE(d)
#   define OBORO_TRACE_WARNING_I(d) OBORO_TRACE_WARNING_II(d)
#   define OBORO_TRACE_WARNING(d) OBORO_TRACE_WARNING_I(d)
# else
#   define OBORO_TRACE_WARNING(d) (void)(0)
# endif
/* ------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&               \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_ERROR)
#   define OBORO_TRACE_ERROR_II(d) OBORO_TRACE(d)
#   define OBORO_TRACE_ERROR_I(d) OBORO_TRACE_ERROR_II(d)
#   define OBORO_TRACE_ERROR(d) OBORO_TRACE_ERROR_I(d)
# else
#   define OBORO_TRACE_ERROR(d) (void)(0)
# endif
/* ------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                       \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_CRITICAL)
#   define OBORO_TRACE_CRITICAL_II(d) OBORO_TRACE(d)
#   define OBORO_TRACE_CRITICAL_I(d) OBORO_TRACE_CRITICAL_II(d)
#   define OBORO_TRACE_CRITICAL(d) OBORO_TRACE_CRITICAL_I(d)
# else
#   define OBORO_TRACE_CRITICAL(d) (void)(0)
# endif
/* ========================================================================= */
# if ((defined(__cplusplus) && (__cplusplus >= 201103L)) ||             \
      (defined(__STDC__) &&                                             \
       defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)))
#   define OBORO_TRACEF_II(fmt, ...)                    \
  do {                                                  \
    OBORO_USING_NAMESPACE_STD;                          \
    fprintf(stderr, "%s(%i) %s : " fmt "\n",            \
            __FILE__, __LINE__, __func__, __VA_ARGS__); \
    fflush(stderr);                                     \
  } while (0)
#   define OBORO_TRACEF_I(fmt, ...) OBORO_TRACEF_II(fmt, __VA_ARGS__)
#   define OBORO_TRACEF(fmt, ...) OBORO_TRACEF_I(fmt, __VA_ARGS__)
/* ------------------------------------------------------------------------- */
#   define OBORO_TRACEF_VERBOSITY_II(l, fmt, ...)                       \
  do {                                                                  \
    if (OBORO_VERBOSITY <= (l)) { OBORO_TRACEF(fmt, __VA_ARGS__); }     \
  } while (0)
#   define OBORO_TRACEF_VERBOSITY_I(l, fmt, ...)        \
  OBORO_TRACEF_VERBOSITY_II(l, fmt, __VA_ARGS__)
#   define OBORO_TRACEF_VERBOSITY(l, fmt, ...)  \
  OBORO_TRACEF_VERBOSITY_I(l, fmt, __VA_ARGS__)
/* ------------------------------------------------------------------------- */
#   if (defined(OBORO_VERBOSITY) &&                     \
        OBORO_VERBOSITY <= OBORO_VERBOSITY_DEBUG)
#     define OBORO_TRACEF_DEBUG_II(fmt, ...)    \
  OBORO_TRACEF(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_DEBUG_I(fmt, ...)     \
  OBORO_TRACEF_DEBUG_II(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_DEBUG(fmt, ...)       \
  OBORO_TRACEF_DEBUG_I(fmt, __VA_ARGS__)
#   else
#     define OBORO_TRACEF_DEBUG(fmt, ...) (void)(0)
#   endif
/* ------------------------------------------------------------------------- */
#   if (defined(OBORO_VERBOSITY) &&                     \
        OBORO_VERBOSITY <= OBORO_VERBOSITY_INFO)
#     define OBORO_TRACEF_INFO_II(fmt, ...)     \
  OBORO_TRACEF(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_INFO_I(fmt, ...)      \
  OBORO_TRACEF_INFO_II(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_INFO(fmt, ...)        \
  OBORO_TRACEF_INFO_I(fmt, __VA_ARGS__)
#   else
#     define OBORO_TRACEF_INFO(fmt, ...) (void)(0)
#   endif
/* ------------------------------------------------------------------------- */
#   if (defined(OBORO_VERBOSITY) &&                     \
        OBORO_VERBOSITY <= OBORO_VERBOSITY_WARNING)
#     define OBORO_TRACEF_WARNING_II(fmt, ...)  \
  OBORO_TRACEF(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_WARNING_I(fmt, ...)   \
  OBORO_TRACEF_WARNING_II(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_WARNING(fmt, ...)     \
  OBORO_TRACEF_WARNING_I(fmt, __VA_ARGS__)
#   else
#     define OBORO_TRACEF_WARNING(fmt, ...) (void)(0)
#   endif
/* ------------------------------------------------------------------------- */
#   if (defined(OBORO_VERBOSITY) &&                     \
        OBORO_VERBOSITY <= OBORO_VERBOSITY_ERROR)
#     define OBORO_TRACEF_ERROR_II(fmt, ...)    \
  OBORO_TRACEF(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_ERROR_I(fmt, ...)     \
  OBORO_TRACEF_ERROR_II(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_ERROR(fmt, ...)       \
  OBORO_TRACEF_ERROR_I(fmt, __VA_ARGS__)
#   else
#     define OBORO_TRACEF_ERROR(fmt, ...) (void)(0)
#   endif
/* ------------------------------------------------------------------------- */
#   if (defined(OBORO_VERBOSITY) &&                     \
        OBORO_VERBOSITY <= OBORO_VERBOSITY_CRITICAL)
#     define OBORO_TRACEF_CRITICAL_II(fmt, ...) \
  OBORO_TRACEF(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_CRITICAL_I(fmt, ...)  \
  OBORO_TRACEF_CRITICAL_II(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_CRITICAL(fmt, ...)    \
  OBORO_TRACEF_CRITICAL_I(fmt, __VA_ARGS__)
#   else
#     define OBORO_TRACEF_CRITICAL(fmt, ...) (void)(0)
#   endif
# endif  /* defined(__STDC__) && ... */
/* ========================================================================= */
# define OBORO_ASSERT_II(c, t, d)               \
  do { if (!(c)) {                              \
      OBORO_USING_NAMESPACE_STD;                \
      OBORO_TRACE_CRITICAL(t ": " d);           \
      abort();                                  \
    }                                           \
  } while (0)
# define OBORO_ASSERT_I(c, t, d) OBORO_ASSERT_II(c, t, d)
# define OBORO_ASSERT(c, d) OBORO_ASSERT_I(c, #c, d)
/* ------------------------------------------------------------------------- */
# define OBORO_ASSERT_VERBOSITY_II(l, c, d)                             \
  do { if (OBORO_VERBOSITY <= (l)) { OBORO_ASSERT(c, d); } } while (0)
# define OBORO_ASSERT_VERBOSITY_I(l, c, d)      \
  OBORO_ASSERT_VERBOSITY_II(l, c, d)
# define OBORO_ASSERT_VERBOSITY(l, c, d)        \
  OBORO_ASSERT_VERBOSITY_I(l, c, d)
/* ------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&               \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_DEBUG)
#   define OBORO_ASSERT_DEBUG_II(c, d) OBORO_ASSERT(c, d)
#   define OBORO_ASSERT_DEBUG_I(c, d) OBORO_ASSERT_DEBUG_II(c, d)
#   define OBORO_ASSERT_DEBUG(c, d) OBORO_ASSERT_DEBUG_I(c, d)
# else
#   define OBORO_ASSERT_DEBUG(c, d) (void)(0)
# endif
/* ------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&               \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_INFO)
#   define OBORO_ASSERT_INFO_II(c, d) OBORO_ASSERT(c, d)
#   define OBORO_ASSERT_INFO_I(c, d) OBORO_ASSERT_INFO_II(c, d)
#   define OBORO_ASSERT_INFO(c, d) OBORO_ASSERT_INFO_I(c, d)
# else
#   define OBORO_ASSERT_INFO(c, d) (void)(0)
# endif
/* ------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                       \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_WARNING)
#   define OBORO_ASSERT_WARNING_II(c, d) OBORO_ASSERT(c, d)
#   define OBORO_ASSERT_WARNING_I(c, d) OBORO_ASSERT_WARNING_II(c, d)
#   define OBORO_ASSERT_WARNING(c, d) OBORO_ASSERT_WARNING_I(c, d)
# else
#   define OBORO_ASSERT_WARNING(c, d) (void)(0)
# endif
/* ------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&               \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_ERROR)
#   define OBORO_ASSERT_ERROR_II(c, d) OBORO_ASSERT(c, d)
#   define OBORO_ASSERT_ERROR_I(c, d) OBORO_ASSERT_ERROR_II(c, d)
#   define OBORO_ASSERT_ERROR(c, d) OBORO_ASSERT_ERROR_I(c, d)
# else
#   define OBORO_ASSERT_ERROR(c, d) (void)(0)
# endif
/* ------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                       \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_CRITICAL)
#   define OBORO_ASSERT_CRITICAL_II(c, d) OBORO_ASSERT(c, d)
#   define OBORO_ASSERT_CRITICAL_I(c, d) OBORO_ASSERT_CRITICAL_II(c, d)
#   define OBORO_ASSERT_CRITICAL(c, d) OBORO_ASSERT_CRITICAL_I(c, d)
# else
#   define OBORO_ASSERT_CRITICAL(c, d) (void)(0)
# endif
#else  /* OBORO_DEBUG  ///////////////////////////////////////////////////// */
/* ========================================================================= */
# define OBORO_TRACE(d) (void)(0)
# define OBORO_TRACE_VERBOSITY(l, d) (void)(0)
# define OBORO_TRACE_DEBUG(d) (void)(0)
# define OBORO_TRACE_INFO(d) (void)(0)
# define OBORO_TRACE_WARNING(d) (void)(0)
# define OBORO_TRACE_ERROR(d) (void)(0)
# define OBORO_TRACE_CRITICAL(d) (void)(0)
/* ========================================================================= */
# if ((defined(__cplusplus) && (__cplusplus >= 201103L)) ||             \
      (defined(__STDC__) &&                                             \
       defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)))
#   define OBORO_TRACEF(fmt, ...) (void)(0)
#   define OBORO_TRACEF_VERBOSITY(l, fmt, ...) (void)(0)
#   define OBORO_TRACEF_DEBUG(fmt, ...) (void)(0)
#   define OBORO_TRACEF_INFO(fmt, ...) (void)(0)
#   define OBORO_TRACEF_WARNING(fmt, ...) (void)(0)
#   define OBORO_TRACEF_ERROR(fmt, ...) (void)(0)
#   define OBORO_TRACEF_CRITICAL(fmt, ...) (void)(0)
# endif  /* defined(__STDC__) && ... */
/* ========================================================================= */
# define OBORO_ASSERT(c, d) (void)(0)
# define OBORO_ASSERT_VERBOSITY(l, c, d) (void)(0)
# define OBORO_ASSERT_DEBUG(c, d) (void)(0)
# define OBORO_ASSERT_INFO(c, d) (void)(0)
# define OBORO_ASSERT_WARNING(c, d) (void)(0)
# define OBORO_ASSERT_ERROR(c, d) (void)(0)
# define OBORO_ASSERT_CRITICAL(c, d) (void)(0)
#endif  /* OBORO_DEBUG  //////////////////////////////////////////////////// */

#endif  /* OBORO_DEBUG_H_ */
