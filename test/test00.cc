/** -*- mode:c++; coding:utf-8-unix; -*-
 *  @file test00.cc
 *  @brief test00.cc
 *
 *  test00.cc
 *
 *  Copyright 2014 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @copyright The MIT License (MIT)
 *  @since 2015/05/24
 *  @date 2023/10/09
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif  // HAVE_CONFIG_H

// #undef OBORO_VERBOSITY
// #define OBORO_VERBOSITY OBORO_VERBOSITY_ALL

#include <stdexcept>
#include <cstdio>

#include <oboro/initializer.hpp>
#include <oboro/oboro.hpp>

// ////////////////////////////////////////////////////////////////////////////
// ============================================================================
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

  // ==========================================================================
  int c_func(lua_State* L);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

// ////////////////////////////////////////////////////////////////////////////
// ============================================================================
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

  // ==========================================================================
  int c_func(lua_State* L) {
    ::oboro::printStack(L);
    int x = static_cast<int>(lua_tonumber(L, 1)) +
            static_cast<int>(lua_tonumber(L, 2));
    lua_settop(L, 0);
    lua_pushnumber(L, x);
    ::oboro::printStack(L);
    return 1;
  }

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

// ////////////////////////////////////////////////////////////////////////////
// ============================================================================
int main(int argc, char* argv[]) {
  OBORO_TRACE("TEST00");
  oboro::Initializer L;
  {
    luaL_openlibs(L);
    lua_register(L, "c_func", c_func);
    if (luaL_dostring(L,
                      "local _M = {}\n"
                      "function _M.hello()\n"
                      "    print([[hello]], c_func(1, 2))\n"
                      "end\n"
                      "return _M")) {
      ::std::fprintf(stderr, "ERROR!: luaL_dostring\n");
      throw ::std::runtime_error("ERROR!");
    }
    lua_setglobal(L, "Hello");
    {
      lua_getglobal(L, "Hello");
      lua_pushstring(L, "hello");
      lua_rawget(L, -2);
      if (lua_pcall(L, 0, 0, 0)) {
        ::std::fprintf(stderr, "ERROR!: lua_pcall: %s\n", lua_tostring(L, 1));
        throw ::std::runtime_error("ERROR!");
      }
    }
  }
  return 0;
}
