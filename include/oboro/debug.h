/** -*- mode:c; coding:utf-8-unix; -*-
 *  @file debug.h
 *  @brief debug.h
 *
 *  debug.h
 *
 *  Copyright 2014 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @since 2015/05/29
 *  @date 2016/02/15
 */

/* ########################################################################## */
/*
  The MIT License (MIT)

  Copyright (c) <2014> hanepjiv <hanepjiv@gmail.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef OBORO_DEBUG_H_
#define OBORO_DEBUG_H_

/* ////////////////////////////////////////////////////////////////////////// */
/* ========================================================================== */
#if (defined(DEBUG) && !defined(OBORO_DEBUG))
# define OBORO_DEBUG
#endif
/* ========================================================================== */
#if (defined(NDEBUG) && defined(OBORO_DEBUG))
# undef OBORO_DEBUG
#endif
/* ========================================================================== */
#define OBORO_VERBOSITY_00              (0x00)
#define OBORO_VERBOSITY_01              (0x3F)
#define OBORO_VERBOSITY_02              (0x7F)
#define OBORO_VERBOSITY_03              (0xBF)
#define OBORO_VERBOSITY_04              (0xFF)
/* -------------------------------------------------------------------------- */
#define OBORO_VERBOSITY_DEBUG           OBORO_VERBOSITY_00
#define OBORO_VERBOSITY_INFO            OBORO_VERBOSITY_01
#define OBORO_VERBOSITY_WARNING         OBORO_VERBOSITY_02
#define OBORO_VERBOSITY_ERROR           OBORO_VERBOSITY_03
#define OBORO_VERBOSITY_CRITICAL        OBORO_VERBOSITY_04
/* -------------------------------------------------------------------------- */
#define OBORO_VERBOSITY_ALL             OBORO_VERBOSITY_DEBUG
#define OBORO_VERBOSITY_DEFAULT         OBORO_VERBOSITY_INFO
#define OBORO_VERBOSITY_QUIET           OBORO_VERBOSITY_CRITICAL
/* ////////////////////////////////////////////////////////////////////////// */
#ifdef OBORO_DEBUG
/* -------------------------------------------------------------------------- */
# if !defined(OBORO_VERBOSITY)
#   define OBORO_VERBOSITY              OBORO_VERBOSITY_DEBUG
# endif
/* ========================================================================== */
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
/* ========================================================================== */
# define OBORO_TRACE__(d)                                               \
  do {                                                                  \
    OBORO_USING_NAMESPACE_STD;                                          \
    fprintf(stderr, "%s(%i) : " d "\n", __FILE__, __LINE__);            \
    fflush(stderr);                                                     \
  } while (0)
# define OBORO_TRACE_(d) OBORO_TRACE__(d)
# define OBORO_TRACE(d) OBORO_TRACE_(d)
/* -------------------------------------------------------------------------- */
# define OBORO_TRACE_VERBOSITY__(l, d)                                  \
  do { if (OBORO_VERBOSITY <= (l)) { OBORO_TRACE(d); } } while (0)
# define OBORO_TRACE_VERBOSITY_(l, d) OBORO_TRACE_VERBOSITY__(l, d)
# define OBORO_TRACE_VERBOSITY(l, d) OBORO_TRACE_VERBOSITY_(l, d)
/* -------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&               \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_DEBUG)
#   define OBORO_TRACE_DEBUG__(d) OBORO_TRACE(d)
#   define OBORO_TRACE_DEBUG_(d) OBORO_TRACE_DEBUG__(d)
#   define OBORO_TRACE_DEBUG(d) OBORO_TRACE_DEBUG_(d)
# else
#   define OBORO_TRACE_DEBUG(d) (void)(0)
# endif
/* -------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                     \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_INFO)
#   define OBORO_TRACE_INFO__(d) OBORO_TRACE(d)
#   define OBORO_TRACE_INFO_(d) OBORO_TRACE_INFO__(d)
#   define OBORO_TRACE_INFO(d) OBORO_TRACE_INFO_(d)
# else
#   define OBORO_TRACE_INFO(d) (void)(0)
# endif
/* -------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                       \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_WARNING)
#   define OBORO_TRACE_WARNING__(d) OBORO_TRACE(d)
#   define OBORO_TRACE_WARNING_(d) OBORO_TRACE_WARNING__(d)
#   define OBORO_TRACE_WARNING(d) OBORO_TRACE_WARNING_(d)
# else
#   define OBORO_TRACE_WARNING(d) (void)(0)
# endif
/* -------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&               \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_ERROR)
#   define OBORO_TRACE_ERROR__(d) OBORO_TRACE(d)
#   define OBORO_TRACE_ERROR_(d) OBORO_TRACE_ERROR__(d)
#   define OBORO_TRACE_ERROR(d) OBORO_TRACE_ERROR_(d)
# else
#   define OBORO_TRACE_ERROR(d) (void)(0)
# endif
/* -------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                       \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_CRITICAL)
#   define OBORO_TRACE_CRITICAL__(d) OBORO_TRACE(d)
#   define OBORO_TRACE_CRITICAL_(d) OBORO_TRACE_CRITICAL__(d)
#   define OBORO_TRACE_CRITICAL(d) OBORO_TRACE_CRITICAL_(d)
# else
#   define OBORO_TRACE_CRITICAL(d) (void)(0)
# endif
/* ========================================================================== */
# if ((defined(__cplusplus) && (__cplusplus >= 201103L)) ||             \
      (defined(__STDC__) &&                                             \
       defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)))
#   define OBORO_TRACEF__(fmt, ...)                                   \
  do {                                                                \
    OBORO_USING_NAMESPACE_STD;                                        \
    fprintf(stderr, "%s(%i) %s : " fmt "\n",                          \
            __FILE__, __LINE__, __func__, __VA_ARGS__);               \
    fflush(stderr);                                                   \
  } while (0)
#   define OBORO_TRACEF_(fmt, ...) OBORO_TRACEF__(fmt, __VA_ARGS__)
#   define OBORO_TRACEF(fmt, ...) OBORO_TRACEF_(fmt, __VA_ARGS__)
/* -------------------------------------------------------------------------- */
#   define OBORO_TRACEF_VERBOSITY__(l, fmt, ...)                        \
  do {                                                                  \
    if (OBORO_VERBOSITY <= (l)) { OBORO_TRACEF(fmt, __VA_ARGS__); }     \
  } while (0)
#   define OBORO_TRACEF_VERBOSITY_(l, fmt, ...) \
  OBORO_TRACEF_VERBOSITY__(l, fmt, __VA_ARGS__)
#   define OBORO_TRACEF_VERBOSITY(l, fmt, ...)  \
  OBORO_TRACEF_VERBOSITY_(l, fmt, __VA_ARGS__)
/* -------------------------------------------------------------------------- */
#   if (defined(OBORO_VERBOSITY) &&                     \
        OBORO_VERBOSITY <= OBORO_VERBOSITY_DEBUG)
#     define OBORO_TRACEF_DEBUG__(fmt, ...)     \
  OBORO_TRACEF(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_DEBUG_(fmt, ...)      \
  OBORO_TRACEF_DEBUG__(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_DEBUG(fmt, ...)       \
  OBORO_TRACEF_DEBUG_(fmt, __VA_ARGS__)
#   else
#     define OBORO_TRACEF_DEBUG(fmt, ...) (void)(0)
#   endif
/* -------------------------------------------------------------------------- */
#   if (defined(OBORO_VERBOSITY) &&                     \
        OBORO_VERBOSITY <= OBORO_VERBOSITY_INFO)
#     define OBORO_TRACEF_INFO__(fmt, ...)      \
  OBORO_TRACEF(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_INFO_(fmt, ...)       \
  OBORO_TRACEF_INFO__(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_INFO(fmt, ...)        \
  OBORO_TRACEF_INFO_(fmt, __VA_ARGS__)
#   else
#     define OBORO_TRACEF_INFO(fmt, ...) (void)(0)
#   endif
/* -------------------------------------------------------------------------- */
#   if (defined(OBORO_VERBOSITY) &&                     \
        OBORO_VERBOSITY <= OBORO_VERBOSITY_WARNING)
#     define OBORO_TRACEF_WARNING__(fmt, ...)   \
  OBORO_TRACEF(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_WARNING_(fmt, ...)    \
  OBORO_TRACEF_WARNING__(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_WARNING(fmt, ...)     \
  OBORO_TRACEF_WARNING_(fmt, __VA_ARGS__)
#   else
#     define OBORO_TRACEF_WARNING(fmt, ...) (void)(0)
#   endif
/* -------------------------------------------------------------------------- */
#   if (defined(OBORO_VERBOSITY) &&                     \
        OBORO_VERBOSITY <= OBORO_VERBOSITY_ERROR)
#     define OBORO_TRACEF_ERROR__(fmt, ...)     \
  OBORO_TRACEF(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_ERROR_(fmt, ...)      \
  OBORO_TRACEF_ERROR__(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_ERROR(fmt, ...)       \
  OBORO_TRACEF_ERROR_(fmt, __VA_ARGS__)
#   else
#     define OBORO_TRACEF_ERROR(fmt, ...) (void)(0)
#   endif
/* -------------------------------------------------------------------------- */
#   if (defined(OBORO_VERBOSITY) &&                     \
        OBORO_VERBOSITY <= OBORO_VERBOSITY_CRITICAL)
#     define OBORO_TRACEF_CRITICAL__(fmt, ...)  \
  OBORO_TRACEF(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_CRITICAL_(fmt, ...)   \
  OBORO_TRACEF_CRITICAL__(fmt, __VA_ARGS__)
#     define OBORO_TRACEF_CRITICAL(fmt, ...)    \
  OBORO_TRACEF_CRITICAL_(fmt, __VA_ARGS__)
#   else
#     define OBORO_TRACEF_CRITICAL(fmt, ...) (void)(0)
#   endif
# endif  /* defined(__STDC__) && ... */
/* ========================================================================== */
# define OBORO_ASSERT__(c, t, d)                        \
  do { if (!(c)) {                                                    \
      OBORO_USING_NAMESPACE_STD;                                      \
      OBORO_TRACE_CRITICAL(t ": " d);                                 \
      abort();                                                        \
    }                                                                 \
  } while (0)
# define OBORO_ASSERT_(c, t, d) OBORO_ASSERT__(c, t, d)
# define OBORO_ASSERT(c, d) OBORO_ASSERT_(c, #c, d)
/* -------------------------------------------------------------------------- */
# define OBORO_ASSERT_VERBOSITY__(l, c, d)                              \
  do { if (OBORO_VERBOSITY <= (l)) { OBORO_ASSERT(c, d); } } while (0)
# define OBORO_ASSERT_VERBOSITY_(l, c, d)       \
  OBORO_ASSERT_VERBOSITY__(l, c, d)
# define OBORO_ASSERT_VERBOSITY(l, c, d)      \
  OBORO_ASSERT_VERBOSITY_(l, c, d)
/* -------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                     \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_DEBUG)
#   define OBORO_ASSERT_DEBUG__(c, d) OBORO_ASSERT(c, d)
#   define OBORO_ASSERT_DEBUG_(c, d) OBORO_ASSERT_DEBUG__(c, d)
#   define OBORO_ASSERT_DEBUG(c, d) OBORO_ASSERT_DEBUG_(c, d)
# else
#   define OBORO_ASSERT_DEBUG(c, d) (void)(0)
# endif
/* -------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                     \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_INFO)
#   define OBORO_ASSERT_INFO__(c, d) OBORO_ASSERT(c, d)
#   define OBORO_ASSERT_INFO_(c, d) OBORO_ASSERT_INFO__(c, d)
#   define OBORO_ASSERT_INFO(c, d) OBORO_ASSERT_INFO_(c, d)
# else
#   define OBORO_ASSERT_INFO(c, d) (void)(0)
# endif
/* -------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                     \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_WARNING)
#   define OBORO_ASSERT_WARNING__(c, d) OBORO_ASSERT(c, d)
#   define OBORO_ASSERT_WARNING_(c, d) OBORO_ASSERT_WARNING__(c, d)
#   define OBORO_ASSERT_WARNING(c, d) OBORO_ASSERT_WARNING_(c, d)
# else
#   define OBORO_ASSERT_WARNING(c, d) (void)(0)
# endif
/* -------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                     \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_ERROR)
#   define OBORO_ASSERT_ERROR__(c, d) OBORO_ASSERT(c, d)
#   define OBORO_ASSERT_ERROR_(c, d) OBORO_ASSERT_ERROR__(c, d)
#   define OBORO_ASSERT_ERROR(c, d) OBORO_ASSERT_ERROR_(c, d)
# else
#   define OBORO_ASSERT_ERROR(c, d) (void)(0)
# endif
/* -------------------------------------------------------------------------- */
# if (defined(OBORO_VERBOSITY) &&                     \
      OBORO_VERBOSITY <= OBORO_VERBOSITY_CRITICAL)
#   define OBORO_ASSERT_CRITICAL__(c, d) OBORO_ASSERT(c, d)
#   define OBORO_ASSERT_CRITICAL_(c, d) OBORO_ASSERT_CRITICAL__(c, d)
#   define OBORO_ASSERT_CRITICAL(c, d) OBORO_ASSERT_CRITICAL_(c, d)
# else
#   define OBORO_ASSERT_CRITICAL(c, d) (void)(0)
# endif
#else  /* OBORO_DEBUG  ////////////////////////////////////////////////////// */
/* ========================================================================== */
# define OBORO_TRACE(d) (void)(0)
# define OBORO_TRACE_VERBOSITY(l, d) (void)(0)
# define OBORO_TRACE_DEBUG(d) (void)(0)
# define OBORO_TRACE_INFO(d) (void)(0)
# define OBORO_TRACE_WARNING(d) (void)(0)
# define OBORO_TRACE_ERROR(d) (void)(0)
# define OBORO_TRACE_CRITICAL(d) (void)(0)
/* ========================================================================== */
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
/* ========================================================================== */
# define OBORO_ASSERT(c, d) (void)(0)
# define OBORO_ASSERT_VERBOSITY(l, c, d) (void)(0)
# define OBORO_ASSERT_DEBUG(c, d) (void)(0)
# define OBORO_ASSERT_INFO(c, d) (void)(0)
# define OBORO_ASSERT_WARNING(c, d) (void)(0)
# define OBORO_ASSERT_ERROR(c, d) (void)(0)
# define OBORO_ASSERT_CRITICAL(c, d) (void)(0)
#endif  /* OBORO_DEBUG  ///////////////////////////////////////////////////// */

#endif  /* OBORO_DEBUG_H_ */
