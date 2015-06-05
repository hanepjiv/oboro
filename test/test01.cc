/** -*- coding:utf-8; -*-
 *  @file test01.cc
 *  @brief test01.cc
 *
 *  test01.cc
 *
 *  Copyright 2015 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @since 2015/05/24
 *  @date 2015/06/05
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

#if 0
#undef OBORO_VERBOSITY
#define OBORO_VERBOSITY OBORO_VERBOSITY_ALL
#endif
#include <oboro/oboro.hpp>
#include <oboro/function.hpp>
#include <oboro/module.hpp>


// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
  // ===========================================================================
  static int c_func(lua_State* L);
  static int c_index(lua_State* L);
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus
// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
int main(int argc, char* argv[]) {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  {
    { OBORO_TRACE("TEST00");
      {
        oboro::newtable(L, oboro::IdxTable { 1, -1, 1.0, -1.0, "test"});
        OBORO_ASSERT(LUA_TTABLE == lua_type(L, -1), "ERROR!");
        lua_rawgeti(L, -1, 1);
        OBORO_ASSERT(LUA_TNUMBER == lua_type(L, -1), "ERROR!");
        OBORO_ASSERT(1 == static_cast<int>(lua_tonumber(L, -1)), "ERROR!");
        lua_settop(L, 0);
      }
      {
        oboro::IdxTable it { 1, -1, 1.0, -1.0, "test", oboro::NIL()};
        oboro::newtable(L, it);
        lua_pop(L, 1);
      }
      {
        const oboro::IdxTable it {
          1, -1, 1.0, -1.0, "test", oboro::IdxTable{1, 2}
        };
        oboro::newtable(L, it);
        lua_pop(L, 1);
      }
    }
    OBORO_ASSERT(0 == lua_gettop(L), "ERROR!");
  }
  { OBORO_TRACE("TEST01");
    {
      {
        oboro::newmetatable(L, "OBORO", oboro::KeyTable {
            {"_test", "TEST"},
            {"kt", oboro::KeyTable {
                {"_test",       "TEST"},
                {"_num",        10},
                {"_cfunc",      &c_func}
              }} });
        lua_pop(L, 1);
      }
      {
        oboro::KeyTable kt { {"_test", "TEST"} };
        oboro::newmetatable(L, "OBORO", kt);
        lua_pop(L, 1);
      }
      {
        const oboro::KeyTable kt { {"_test", "TEST"}, {"nil", oboro::NIL()} };
        oboro::newmetatable(L, "OBORO", kt);
        lua_pop(L, 1);
      }
    }
    OBORO_ASSERT(0 == lua_gettop(L), "ERROR!");
  }
  { OBORO_TRACE("TEST02");
    {
      oboro::newtable(L, oboro::IdxTable { 1, -1, 1.0, -1.0, "test" });
      {
        const oboro::KeyTable kt { {"_test", "TEST"}, {"nil", oboro::NIL()} };
        oboro::newmetatable(L, "OBORO", oboro::KeyTable {
            {"_test",   "TEST"},
            {"_num",    10},
            {"_cfunc",  &c_func},
            {"kt",      kt}
          });
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
  { OBORO_TRACE("TEST03");
    {
      oboro::Module("test3", 1, 0, 0)
          .def("test", 1)
          .def("test", 1)
          .end();
    }
    OBORO_ASSERT(0 == lua_gettop(L), "ERROR!");
  }
  { OBORO_TRACE("TEST04");
    {
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wpedantic"
      lua_pushlightuserdata(L, reinterpret_cast<void*>(&c_func));
# pragma GCC diagnostic pop
      lua_pushcclosure(L, &oboro::oboroClosure, 1);
      lua_pushnumber(L, 1);
      lua_pushnumber(L, 2);
      if (lua_pcall(L, 2, 1, 0)) {
        std::fprintf(stderr, "ERROR!: lua_pcall: %s\n", lua_tostring(L, 1));
        exit(EXIT_FAILURE);
      }
      oboro::printStack(L);
      lua_pop(L, 1);
    }
    OBORO_ASSERT(0 == lua_gettop(L), "ERROR!");
  }
  { OBORO_TRACE("TEST05");
    {
      int** ppi = static_cast<int**>(lua_newuserdata(L, sizeof(int*)));
      int i = 12;
      *ppi = &i;
      {
        luaL_newmetatable(L, "TEST05");
        {
          lua_pushstring(L, "__index");
          lua_pushcfunction(L, c_index);
          lua_rawset(L, -3);
        }
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
  lua_close(L);
}
// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
  // ===========================================================================
  int c_func(lua_State* L) {
    int ret = static_cast<int>(lua_tonumber(L, 1)) +
              static_cast<int>(lua_tonumber(L, 2));
    lua_settop(L, 0);
    lua_pushnumber(L, ret);
    return 1;
  }
  // ===========================================================================
  int c_index(lua_State* L) {
    std::printf("c_index\n");
    oboro::printStack(L);
    int** ppi = static_cast<int**>(lua_touserdata(L, 1));
    const char* key = lua_tostring(L, 2);
    lua_settop(L, 0);
    if (0 == std::strcmp("test", key)) {
      lua_pushnumber(L, **ppi);
    } else {
      lua_pushnil(L);
    }
    return 1;
  }
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus
