/** -*- mode:c; coding:utf-8-unix; -*-
 *  @file begin.h
 *  @brief begin.h
 *
 *  begin.h
 *
 *  Copyright 2014 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @copyright The MIT License (MIT)
 *  @since 2015/05/24
 *  @date 2016/01/30
 */

#ifndef OBORO_BEGIN_H_
#define OBORO_BEGIN_H_

/* ######################################################################### */
/* ========================================================================= */
#ifndef CALL_CDECL
# if defined(_WINDOWS) && !defined(__GNUC__)
#  define CALL_CDECL __cdecl
# else
#  define CALL_CDECL
# endif
#endif  /* CALL_CDECL */
/* ========================================================================= */
#ifndef OBORO_CALL
# define OBORO_CALL CALL_CDECL
#endif /* OBORO_CALL */
/* ========================================================================= */
#if defined(__GNUC__)
# if __GNUC__ >= 4
#  define DECLSPEC_EXPORTS __attribute__ ((visibility("default")))
#  define DECLSPEC_IMPORTS
# elif __GNUC__ >= 2
#  define DECLSPEC_EXPORTS __declspec(dllexport)
#  define DECLSPEC_IMPORTS
# endif
#elif defined(_WINDOWS)
#  define DECLSPEC_EXPORTS __declspec(dllexport)
#  define DECLSPEC_IMPORTS __declspec(dllimport)
#else
# define DECLSPEC_EXPORTS
# define DECLSPEC_IMPORTS
#endif
/* ========================================================================= */
#ifndef OBORO_DECLSPEC
# if defined(OBORO_EXPORTS)
#  define OBORO_DECLSPEC DECLSPEC_EXPORTS
# else
#  define OBORO_DECLSPEC DECLSPEC_IMPORTS
# endif
#endif /* OBORO_DECLSPEC */

#endif  /* OBORO_BEGIN_H_ */
