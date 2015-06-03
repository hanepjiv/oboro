/** -*- coding:utf-8; -*-
 *  @file test00.cc
 *  @brief test00.cc
 *
 *  test00.cc
 *
 *  Copyright 2015 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @since 2015/05/24
 *  @date 2015/06/04
 */


// #############################################################################
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif  // HAVE_CONFIG_H

#include <oboro/oboro.hpp>

#include <cstdio>


// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

  // ===========================================================================
  int c_func(lua_State* L);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

  // ===========================================================================
  int c_func(lua_State* L) {
    ::oboro::printStack(L);
    int x = static_cast<int>(lua_tonumber(L, 1));
    int y = static_cast<int>(lua_tonumber(L, 2));
    lua_settop(L, 0);
    lua_pushnumber(L, x + y);
    ::oboro::printStack(L);
    return 1;
  }

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus


// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
int main(int argc, char* argv[]) {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  {
    lua_register(L, "c_func", c_func);
    if (luaL_loadstring(L,
                        "function hello()\n"
                        "    print([[hello]], c_func(1, 2))\n"
                        "end\n")) {
      std::fprintf(stderr, "ERROR!: luaL_loadstring");
      exit(EXIT_FAILURE);
    }
    ::oboro::printStack(L);
    if (lua_pcall(L, 0, 0, 0)) {
      std::fprintf(stderr, "ERROR!: lua_pcall: %s\n", lua_tostring(L, 1));
      exit(EXIT_FAILURE);
    }
    {
      lua_getglobal(L, "hello");
      if (lua_pcall(L, 0, 0, 0)) {
        std::fprintf(stderr, "ERROR!: lua_pcall: %s\n", lua_tostring(L, 1));
        exit(EXIT_FAILURE);
      }
    }
  }
  lua_close(L);
  return 0;
}
