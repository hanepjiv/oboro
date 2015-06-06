/** -*- coding:utf-8; -*-
 *  @file oboro.hpp
 *  @brief oboro.hpp
 *
 *  oboro.hpp
 *
 *  Copyright 2015 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @since 2015/05/29
 *  @date 2015/06/07
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


#ifndef OBORO_OBORO_HPP_
#define OBORO_OBORO_HPP_


#include <lua.hpp>

#include <boost/any.hpp>
#include <boost/format.hpp>

#include <cstdio>
#include <stdexcept>
#include <vector>
#include <string>
#include <utility>
#include <type_traits>

#include "./debug.h"


// #############################################################################
namespace oboro {
// =============================================================================
using NIL = struct {};
// =============================================================================
inline void     printStack(lua_State* L) noexcept;
// -----------------------------------------------------------------------------
template <typename T>
inline void     push(lua_State* L, T a_val) noexcept;
// -----------------------------------------------------------------------------
template <typename T>
inline void     rawseti(lua_State* L, int a_index, int a_origin, T a_val);
// -----------------------------------------------------------------------------
template <typename T>
inline void     rawset(lua_State* L, int a_index, const char* a_key, T a_val);
// -----------------------------------------------------------------------------
template <typename... Ts>
inline void     rawsets(lua_State* L, int a_index, int a_origin, Ts... a_args);
// -----------------------------------------------------------------------------
template <typename... Ts>
inline int      newtable(lua_State* L, Ts... a_args);
// -----------------------------------------------------------------------------
template <typename... Ts>
inline int      newmetatable(lua_State* L, const std::string& a_name,
                             Ts... a_args);
}  // namespace oboro
// #############################################################################
namespace oboro {
// =============================================================================
inline void     printStack(lua_State* L) noexcept {
  OBORO_TRACE_DEBUG("oboro::printStack");
  std::printf("// ========================================================= \n"
              "// Lua Stack  ----------------------------------------------\n");
  int n = lua_gettop(L);
  for (int i = n; i >= 1; --i) {
    int t = lua_type(L, i);
    std::printf("% 3d / % 3d : %10s : ", i, i - n - 1, lua_typename(L, t));
    switch (t) {
      case LUA_TNONE:                                                     break;
      case LUA_TNIL:                                                      break;
      case LUA_TBOOLEAN:       std::printf("%d", lua_toboolean(L, i));    break;
      case LUA_TLIGHTUSERDATA: std::printf("%p", lua_touserdata(L, i));   break;
      case LUA_TNUMBER:        std::printf("%+lf", lua_tonumber(L, i));   break;
      case LUA_TSTRING:        std::printf("[[%s]]", lua_tostring(L, i)); break;
      case LUA_TTABLE:         std::printf("%p", lua_topointer(L, i));    break;
      case LUA_TFUNCTION:
        if (lua_iscfunction(L, i)) {
          std::printf("C Function   : %p", lua_tocfunction(L, i));
        } else {
          std::printf("Lua Function : %p", lua_topointer(L, i));
        }
        break;
      case LUA_TUSERDATA:      std::printf("%p", lua_touserdata(L, i));   break;
      case LUA_TTHREAD:        std::printf("%p", lua_tothread(L, i));     break;
      default:                                                            break;
    }
    std::printf("\n");
  }
}
// =============================================================================
template <>
inline void     push(lua_State* L, NIL /* a_nil */) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<NIL>");
  OBORO_ASSERT(L, "ERROR! oboro::push<NIL>: invalid lua_State");
  lua_pushnil(L);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, bool a_val) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<bool>");
  OBORO_ASSERT(L, "ERROR! oboro::push<bool>: invalid lua_State");
  lua_pushboolean(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, void* a_val) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<void*>");
  OBORO_ASSERT(L, "ERROR! oboro::push<void*>: invalid lua_State");
  lua_pushlightuserdata(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, lua_Number a_val) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<lua_Number>");
  OBORO_ASSERT(L, "ERROR! oboro::push<lua_Number>: invalid lua_State");
  lua_pushnumber(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, lua_Integer a_val) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<lua_Integer>");
  OBORO_ASSERT(L, "ERROR! oboro::push<lua_Integer>: invalid lua_State");
  lua_pushinteger(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, const char* a_val) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<const char*>");
  OBORO_ASSERT(L, "ERROR! oboro::push<const char*>: invalid lua_State");
  lua_pushstring(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, char* a_val) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<char*>");
  OBORO_ASSERT(L, "ERROR! oboro::push<const char*>: invalid lua_State");
  lua_pushstring(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, lua_CFunction a_val) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<lua_CFunction>");
  OBORO_ASSERT(L, "ERROR! oboro::push<lua_CFunction>: invalid lua_State");
  lua_pushcfunction(L, a_val);
}
// =============================================================================
template <typename T>
inline void     rawseti(lua_State* L, int a_index, int a_origin, T a_val) {
  OBORO_TRACE_DEBUG("oboro::rawseti<T>");
  OBORO_ASSERT(L, "ERROR! oboro::rawseti: invalid lua_State");
  OBORO_ASSERT(0 != a_index, "ERROR! oboro::rawseti: invalid index");
  push(L, a_val);
  lua_rawseti(L, (0 < a_index) ? a_index : (a_index - 1), a_origin);
}
// =============================================================================
template <typename T>
inline void     rawset(lua_State* L, int a_index, const char* a_key, T a_val) {
  OBORO_TRACE_DEBUG("oboro::rawset<T>");
  OBORO_ASSERT(L, "ERROR! oboro::rawset: invalid lua_State");
  OBORO_ASSERT(0 != a_index, "ERROR! oboro::rawset: invalid index");
  OBORO_ASSERT(a_key, "ERROR! oboro::rawset: invalid key");
  push(L, a_key);
  push(L, a_val);
  lua_rawset(L, (0 < a_index) ? a_index : (a_index - 2));
}
// =============================================================================
template <typename T, typename... Ts>
inline void     rawsets(lua_State* L, int a_index, int a_origin,
                        std::pair<const char*, T> a_val, Ts... a_tails) {
  OBORO_TRACE_DEBUG("oboro::rawsets<std::pair<const char*, T>, Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::rawsets: invalid lua_State");
  OBORO_ASSERT(0 != a_index, "ERROR! oboro::rawsets: invalid index");
  OBORO_ASSERT(0 < a_origin, "ERROR! oboro::rawsets: invalid origin");
  oboro::rawset(L, a_index, std::get<0>(a_val), std::get<1>(a_val));
  oboro::rawsets(L, a_index, a_origin + 1, a_tails...);
}
// -----------------------------------------------------------------------------
template <typename T, typename... Ts>
inline void     rawsets(lua_State* L, int a_index, int a_origin,
                        T a_val, Ts... a_tails) {
  OBORO_TRACE_DEBUG("oboro::rawsets<T, Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::rawsets: invalid lua_State");
  OBORO_ASSERT(0 != a_index, "ERROR! oboro::rawsets: invalid index");
  OBORO_ASSERT(0 < a_origin, "ERROR! oboro::rawsets: invalid origin");
  oboro::rawseti(L, a_index, a_origin, a_val);
  oboro::rawsets(L, a_index, a_origin + 1, a_tails...);
}
// -----------------------------------------------------------------------------
template <typename T>
inline void     rawsets(lua_State* L, int a_index, int a_origin, T a_val) {
  OBORO_TRACE_DEBUG("oboro::rawsets<T>");
  OBORO_ASSERT(L, "ERROR! oboro::rawsets: invalid lua_State");
  OBORO_ASSERT(0 != a_index, "ERROR! oboro::rawsets: invalid index");
  OBORO_ASSERT(0 < a_origin, "ERROR! oboro::rawsets: invalid origin");
  oboro::rawseti(L, a_index, a_origin, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     rawsets(lua_State* L, int a_index, int a_origin) {
  OBORO_TRACE_DEBUG("oboro::rawsets<>");
  OBORO_ASSERT(L, "ERROR! oboro::rawsets: invalid lua_State");
  OBORO_ASSERT(0 != a_index, "ERROR! oboro::rawsets: invalid index");
  OBORO_ASSERT(0 < a_origin, "ERROR! oboro::rawsets: invalid origin");
}
// =============================================================================
template <typename... Ts> struct size_of_pair;
// -----------------------------------------------------------------------------
template <typename T0, typename T1>
struct size_of_pair< std::pair<T0, T1> > {
  static const size_t value = 1;
};
// -----------------------------------------------------------------------------
template <typename T>
struct size_of_pair<T> {
  static const size_t value = 0;
};
// -----------------------------------------------------------------------------
template <typename T0, typename T1, typename... Ts>
struct size_of_pair<std::pair<T0, T1>, Ts...> {
  static const size_t value = 1 + size_of_pair<Ts...>::value;
};
// -----------------------------------------------------------------------------
template <typename T, typename... Ts>
struct size_of_pair<T, Ts...> {
  static const size_t value = size_of_pair<Ts...>::value;
};
// =============================================================================
template <typename... Ts>
inline int      newtable(lua_State* L, Ts... a_args) {
  OBORO_TRACE_DEBUG("oboro::newtable<Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::newtable<Ts...>: invalid lua_State");
  OBORO_TRACEF_INFO("oboro::newtable<Ts...>: lua_createtable(L, %d, %d);",
                    sizeof...(Ts) - size_of_pair<Ts...>::value,
                    size_of_pair<Ts...>::value);
  lua_createtable(L,
                  static_cast<int>(sizeof...(Ts) - size_of_pair<Ts...>::value),
                  static_cast<int>(size_of_pair<Ts...>::value));
  oboro::rawsets(L, -1, 1, a_args...);
  return 1;
}
// -----------------------------------------------------------------------------
template <>
inline int      newtable(lua_State* L) {
  OBORO_TRACE_DEBUG("oboro::newtable<Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::newtable<Ts...>: invalid lua_State");
  lua_createtable(L, 0, 0);
  return 1;
}
// =============================================================================
template <typename... Ts>
inline int      newmetatable(lua_State* L, const std::string& a_name,
                             Ts... a_args) {
  OBORO_TRACE_DEBUG("oboro::newmetatable<Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::newmetatable<Ts...>: invalid lua_State");
  if (0 == luaL_newmetatable(L, a_name.c_str())) {
    OBORO_TRACEF_WARNING("oboro::newmetatable<Ts...>: "
                         "The registry already has \"%s\"", a_name.c_str());
  }
  oboro::rawsets(L, -1, 1, a_args...);
  return 1;
}
// -----------------------------------------------------------------------------
template <>
inline int      newmetatable(lua_State* L, const std::string& a_name) {
  OBORO_TRACE_DEBUG("oboro::newmetatable<Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::newmetatable<Ts...>: invalid lua_State");
  if (0 == luaL_newmetatable(L, a_name.c_str())) {
    OBORO_TRACEF_WARNING("oboro::newmetatable<Ts...>: "
                         "The registry already has \"%s\"", a_name.c_str());
  }
  return 1;
}
}  // namespace oboro


#endif  // OBORO_OBORO_HPP_
