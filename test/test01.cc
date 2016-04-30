/** -*- coding:utf-8; -*-
 *  @file test01.cc
 *  @brief test01.cc
 *
 *  test01.cc
 *
 *  Copyright 2014 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @since 2015/05/24
 *  @date 2016/02/11
 */

// #############################################################################
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif  // HAVE_CONFIG_H

#undef OBORO_VERBOSITY
#define OBORO_VERBOSITY OBORO_VERBOSITY_INFO

#include <oboro/initializer.hpp>
#include <oboro/oboro.hpp>
#include <oboro/function.hpp>
#include <oboro/module.hpp>

#include <stdexcept>
#include <cstring>

// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
  // ===========================================================================
  static int c_func(lua_State* L) noexcept;
  static int c_index(lua_State* L) noexcept;
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus
// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
  // ===========================================================================
  int c_func(lua_State* L) noexcept {
    int ret = static_cast<int>(lua_tonumber(L, 1)) +
              static_cast<int>(lua_tonumber(L, 2));
    lua_settop(L, 0);
    lua_pushnumber(L, ret);
    return 1;
  }
  // ===========================================================================
  int c_index(lua_State* L) noexcept {
    ::std::printf("c_index\n");
    oboro::printStack(L);
    int** ppi = static_cast<int**>(lua_touserdata(L, 1));
    const char* key = lua_tostring(L, 2);
    lua_settop(L, 0);
    if (0 == ::std::strcmp("test", key)) {
      lua_pushnumber(L, **ppi);
    } else {
      lua_pushnil(L);
    }
    return 1;
  }
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus
// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
int main(int argc, char* argv[]) {
  OBORO_TRACE("TEST01");
  oboro::Initializer L;
  luaL_openlibs(L);
  // ---------------------------------------------------------------------------
  { OBORO_TRACE("TEST01::00");
    {
      oboro::newtable(L, 1, -1, 1.0, -1.0, "test");
      OBORO_ASSERT(LUA_TTABLE == lua_type(L, -1), "ERROR!");
      lua_rawgeti(L, -1, 1);
      OBORO_ASSERT(LUA_TNUMBER == lua_type(L, -1), "ERROR!");
      OBORO_ASSERT(1 == static_cast<int>(lua_tonumber(L, -1)), "ERROR!");
      lua_pop(L, 2);
    }
    OBORO_ASSERT(0 == lua_gettop(L), "ERROR!");
  }
  // ---------------------------------------------------------------------------
  { OBORO_TRACE("TEST01::01");
    {
      oboro::newmetatable(L, "OBORO", ::std::make_pair("_test", "TEST"));
      lua_pop(L, 1);
    }
    OBORO_ASSERT(0 == lua_gettop(L), "ERROR!");
  }
  // ---------------------------------------------------------------------------
  { OBORO_TRACE("TEST01::02");
    {
      oboro::newtable(L, 1, -1, 1.0, -1.0, "test");
      {
        oboro::newmetatable(L, "OBORO",
                            ::std::make_pair("_test", "TEST"),
                            ::std::make_pair("_num", 10),
                            ::std::make_pair("_cfunc", &c_func));
        lua_setmetatable(L, -2);

        OBORO_ASSERT(LUA_TNIL != luaL_getmetafield(L, -1, "_num"), "ERROR!");
        OBORO_ASSERT(LUA_TNUMBER == lua_type(L, -1), "ERROR!");
        OBORO_ASSERT(10 == static_cast<int>(lua_tonumber(L, -1)), "ERROR!");
        lua_pop(L, 1);
      }
      lua_pop(L, 1);
    }
    OBORO_ASSERT(0 == lua_gettop(L), "ERROR!");
  }
  // ---------------------------------------------------------------------------
  { OBORO_TRACE("TEST01::03");
    {
      int** ppi = static_cast<int**>(lua_newuserdata(L, sizeof(int*)));
      int i = 12;
      *ppi = &i;
      {
        oboro::newmetatable(L, "TEST03", ::std::make_pair("__index", c_index));
        lua_setmetatable(L, -2);
      }
      oboro::printStack(L);
      lua_pushstring(L, "test");
      lua_gettable(L, -2);
      oboro::printStack(L);
      lua_pop(L, 2);
    }
    OBORO_ASSERT(0 == lua_gettop(L), "ERROR!");
  }
  // ---------------------------------------------------------------------------
  { OBORO_TRACE("TEST01::04");
    {
      oboro::newtable(L,
                      1, 2.0, "test",
                      ::std::make_pair("test", 1), ::std::make_pair("_0", 0));
      lua_pushnil(L);
      for (int idx = -2; 0 != lua_next(L, idx); --idx) {
        lua_insert(L, -2);
      }
      oboro::printStack(L);
      lua_settop(L, 0);
    }
    OBORO_ASSERT(0 == lua_gettop(L), "ERROR!");
  }
  // ---------------------------------------------------------------------------
  { OBORO_TRACE("TEST01::05");
    {
      oboro::Module("test", 1, 0, 0)
          .def("test", 1)
          .def("test", 1)
          .end();
    }
    OBORO_ASSERT(0 == lua_gettop(L), "ERROR!");
  }
  // ---------------------------------------------------------------------------
  { OBORO_TRACE("TEST01::06");
    {
      lua_pushlightuserdata(L, reinterpret_cast<void*>(&c_func));
      lua_pushcclosure(L, &oboro::oboroClosure, 1);
      lua_pushnumber(L, 1);
      lua_pushnumber(L, 2);
      if (lua_pcall(L, 2, 1, 0)) {
        ::std::fprintf(stderr, "ERROR!: lua_pcall: %s\n", lua_tostring(L, 1));
        throw ::std::runtime_error("ERROR!");
      }
      oboro::printStack(L);
      lua_pop(L, 1);
    }
    OBORO_ASSERT(0 == lua_gettop(L), "ERROR!");
  }
}
