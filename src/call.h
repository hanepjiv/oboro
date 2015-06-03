/** -*- coding:utf-8; -*-
 *  @file call.h
 *  @brief call.h
 *
 *  call.h
 *
 *  Copyright 2015 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @since 2015/05/24
 *  @date 2015/06/02
 */


/* ########################################################################## */
/*
  The MIT License (MIT)

  Copyright (c) <2015> hanepjiv <hanepjiv@gmail.com>

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


#ifndef OBORO_CALL_H_
#define OBORO_CALL_H_


/* ########################################################################## */
/* ========================================================================== */
#ifndef CALL_CDECL
# if defined(_WINDOWS) && !defined(__GNUC__)
#  define CALL_CDECL __cdecl
# else
#  define CALL_CDECL
# endif
#endif  /* CALL_CDECL */


#endif  /* OBORO_CALL_H_ */
