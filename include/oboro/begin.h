/** -*- coding:utf-8; -*-
 *  @file begin.h
 *  @brief begin.h
 *
 *  begin.h
 *
 *  Copyright 2014 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @since 2015/05/24
 *  @date 2016/01/30
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


#ifndef OBORO_BEGIN_H_
#define OBORO_BEGIN_H_


/* ########################################################################## */
/* ========================================================================== */
#ifndef CALL_CDECL
# if defined(_WINDOWS) && !defined(__GNUC__)
#  define CALL_CDECL __cdecl
# else
#  define CALL_CDECL
# endif
#endif  /* CALL_CDECL */
/* ========================================================================== */
#ifndef OBORO_CALL
# define OBORO_CALL CALL_CDECL
#endif /* OBORO_CALL */
/* ========================================================================== */
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
/* ========================================================================== */
#ifndef OBORO_DECLSPEC
# if defined(OBORO_EXPORTS)
#  define OBORO_DECLSPEC DECLSPEC_EXPORTS
# else
#  define OBORO_DECLSPEC DECLSPEC_IMPORTS
# endif
#endif /* OBORO_DECLSPEC */


#endif  /* OBORO_BEGIN_H_ */
