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
 *  @date 2015/05/30
 */


// #############################################################################
/*
  The MIT License (MIT)

  Copyright (c) <2014> Kagumo SAKISAKA <kagumo@gmail.com>

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

#include <boost/scope_exit.hpp>
#include <lua.hpp>

#include <oboro/oboro.hpp>

#include <ostream>

#include "../src/debug.h"


// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

  // ===========================================================================
  int my_add(lua_State* L);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

  // ===========================================================================
  int my_add(lua_State* L) {
    ::oboro::printStack(L);
    int x = static_cast<int>(lua_tonumber(L, 1));
    int y = static_cast<int>(lua_tonumber(L, 2));
    lua_settop(L, 0);  // clear stack
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
  BOOST_SCOPE_EXIT_ALL((L)) {
    lua_close(L);
  };
  {
    luaL_openlibs(L);
    lua_register(L, "my_add", my_add);
    if (luaL_loadstring(L,
                        "function hello()\n"
                        "    print([[hello]], my_add(1, 2))\n"
                        "end\n")) {
      std::cerr << "ERROR!: luaL_loadstring" << std::endl;
      exit(EXIT_FAILURE);
    }
    if (lua_pcall(L, 0, 0, 0)) {
      std::cerr << "ERROR!: lua_pcall: " << lua_tostring(L, 1) << std::endl;
      exit(EXIT_FAILURE);
    }
    {
      lua_getglobal(L, "hello");
      if (lua_pcall(L, 0, 0, 0)) {
        std::cerr << "ERROR!: lua_pcall: " << lua_tostring(L, 1) << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    lua_settop(L, 0);
  }
  return 0;
}
