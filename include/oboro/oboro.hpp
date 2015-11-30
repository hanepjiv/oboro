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
 *  @date 2015/11/30
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

#include <boost/scope_exit.hpp>

#include <cstdio>
#include <typeinfo>
#include <utility>
#include <stdexcept>

#include "./debug.h"


// #############################################################################
namespace oboro {

// =============================================================================
using NIL        = struct {};
using TABLE      = struct {};
// =============================================================================
inline void     print(lua_State* L, int a_Index) noexcept;
inline void     printStack(lua_State* L) noexcept;
// -----------------------------------------------------------------------------
template <class T, bool THROW = true>
inline bool     is(lua_State* L, int a_Index);
// -----------------------------------------------------------------------------
template <class T>
inline void     push(lua_State* L, T a_Value) noexcept;
// -----------------------------------------------------------------------------
template <class T>
inline void     rawseti(lua_State* L,
                        int a_TblIdx, int a_Index, T a_Value) noexcept;
template <class T>
inline void     rawset(lua_State* L,
                       int a_TblIdx, const char* a_Key, T a_Value) noexcept;
template <class... Ts>
inline void     rawsets(lua_State* L,
                        int a_TblIdx, int a_Index, Ts&&... a_Args) noexcept;
// -----------------------------------------------------------------------------
template <class... Ts>
inline void     newtable(lua_State* L, Ts&&... a_Args) noexcept;

template <class... Ts>
inline void     newmetatable(lua_State* L, const char* a_Name,
                             Ts&&... a_Args) noexcept;
// -----------------------------------------------------------------------------
template <class T>
inline T        get(lua_State* L, int a_Index);
// -----------------------------------------------------------------------------
template <class T, bool POP = false>
inline T        gettable(lua_State* L, int a_TblIdx, int a_Index);

template <class T, bool POP = false>
inline T        gettable(lua_State* L, int a_TblIdx, const char* a_Key);
}  // namespace oboro
// #############################################################################
namespace oboro {
// =============================================================================
inline void     print(lua_State* L, int i) noexcept {
  int t = lua_type(L, i);
  ::std::printf("% 3d / % 3d : %10s : ",
                i, i - lua_gettop(L) - 1, lua_typename(L, t));
  switch (t) {
    case LUA_TNONE:                                                       break;
    case LUA_TNIL:                                                        break;
    case LUA_TBOOLEAN:       ::std::printf("%d", lua_toboolean(L, i));    break;
    case LUA_TLIGHTUSERDATA: ::std::printf("%p", lua_touserdata(L, i));   break;
    case LUA_TNUMBER:        ::std::printf("%+lf", lua_tonumber(L, i));   break;
    case LUA_TSTRING:        ::std::printf("[[%s]]", lua_tostring(L, i)); break;
    case LUA_TTABLE:         ::std::printf("%p", lua_topointer(L, i));    break;
    case LUA_TFUNCTION:
      if (lua_iscfunction(L, i)) {
        ::std::printf("C Function   : %p", lua_tocfunction(L, i));
      } else {
        ::std::printf("Lua Function : %p", lua_topointer(L, i));
      }                                                                   break;
    case LUA_TUSERDATA:      ::std::printf("%p", lua_touserdata(L, i));   break;
    case LUA_TTHREAD:        ::std::printf("%p", lua_tothread(L, i));     break;
    default:                                                              break;
  }
  ::std::printf("\n");
}
// =============================================================================
inline void     printStack(lua_State* L) noexcept {
  OBORO_TRACE_DEBUG("oboro::printStack");
  ::std::printf("// =======================================================\n"
                "// Lua Stack  --------------------------------------------\n");
  int n = lua_gettop(L);
  for (int i = n; i >= 1; --i) {
    print(L, i);
  }
}
// =============================================================================
// -----------------------------------------------------------------------------
template <>
inline bool     is<int, false>(lua_State* L, int a_Index) {
  OBORO_TRACE_DEBUG("oboro::is<int, false>");
  OBORO_ASSERT(L, "ERROR! oboro::is<int, false>: invalid lua_State");
  return lua_isnumber(L, a_Index);
}
// -----------------------------------------------------------------------------
template <>
inline bool     is<int, true>(lua_State* L, int a_Index) {
  OBORO_TRACE_DEBUG("oboro::is<int, true>");
  OBORO_ASSERT(L, "ERROR! oboro::is<int, true>: invalid lua_State");
  if (!is<int, false>(L, a_Index)) {
    throw ::std::runtime_error("ERROR!: oboro::is<int, true>");
  }
  return true;
}
// -----------------------------------------------------------------------------
template <>
inline bool     is<lua_Number, false>(lua_State* L, int a_Index) {
  OBORO_TRACE_DEBUG("oboro::is<lua_Number, false>");
  OBORO_ASSERT(L, "ERROR! oboro::is<lua_Number, false>: invalid lua_State");
  return lua_isnumber(L, a_Index);
}
// -----------------------------------------------------------------------------
template <>
inline bool     is<lua_Number, true>(lua_State* L, int a_Index) {
  OBORO_TRACE_DEBUG("oboro::is<lua_Number, true>");
  OBORO_ASSERT(L, "ERROR! oboro::is<lua_Number, true>: invalid lua_State");
  if (!is<lua_Number, false>(L, a_Index)) {
    throw ::std::runtime_error("ERROR!: oboro::is<lua_Number, true>");
  }
  return true;
}
// -----------------------------------------------------------------------------
template <>
inline bool     is<bool, false>(lua_State* L, int a_Index) {
  OBORO_TRACE_DEBUG("oboro::is<bool, false>");
  OBORO_ASSERT(L, "ERROR! oboro::is<bool, false>: invalid lua_State");
  return lua_isboolean(L, a_Index);
}
// -----------------------------------------------------------------------------
template <>
inline bool     is<bool, true>(lua_State* L, int a_Index) {
  OBORO_TRACE_DEBUG("oboro::is<bool, true>");
  OBORO_ASSERT(L, "ERROR! oboro::is<bool, true>: invalid lua_State");
  if (!is<bool, false>(L, a_Index)) {
    throw ::std::runtime_error("ERROR!: oboro::is<bool, true>");
  }
  return true;
}
// -----------------------------------------------------------------------------
template <>
inline bool     is<const char*, false>(lua_State* L, int a_Index) {
  OBORO_TRACE_DEBUG("oboro::is<const char*, false>");
  OBORO_ASSERT(L, "ERROR! oboro::is<const char*, false>: invalid lua_State");
  return lua_isstring(L, a_Index);
}
// -----------------------------------------------------------------------------
template <>
inline bool     is<const char*, true>(lua_State* L, int a_Index) {
  OBORO_TRACE_DEBUG("oboro::is<const char*, true>");
  OBORO_ASSERT(L, "ERROR! oboro::is<const char*, true>: invalid lua_State");
  if (!is<const char*, false>(L, a_Index)) {
    throw ::std::runtime_error("ERROR!: oboro::is<const char*, true>");
  }
  return true;
}
// -----------------------------------------------------------------------------
template <>
inline bool     is<TABLE, false>(lua_State* L, int a_Index) {
  OBORO_TRACE_DEBUG("oboro::is<TABLE, false>");
  OBORO_ASSERT(L, "ERROR! oboro::is<TABLE, false>: invalid lua_State");
  return lua_istable(L, a_Index);
}
// -----------------------------------------------------------------------------
template <>
inline bool     is<TABLE, true>(lua_State* L, int a_Index) {
  OBORO_TRACE_DEBUG("oboro::is<TABLE, true>");
  OBORO_ASSERT(L, "ERROR! oboro::is<TABLE, true>: invalid lua_State");
  if (!is<TABLE, false>(L, a_Index)) {
    throw ::std::runtime_error("ERROR!: oboro::is<TABLE, true>");
  }
  return true;
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
inline void     push(lua_State* L, bool a_Value) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<bool>");
  OBORO_ASSERT(L, "ERROR! oboro::push<bool>: invalid lua_State");
  lua_pushboolean(L, a_Value);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, void* a_Value) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<void*>");
  OBORO_ASSERT(L, "ERROR! oboro::push<void*>: invalid lua_State");
  lua_pushlightuserdata(L, a_Value);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, double a_Value) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<double>");
  OBORO_ASSERT(L, "ERROR! oboro::push<double>: invalid lua_State");
  lua_pushnumber(L, a_Value);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, int a_Value) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<int>");
  OBORO_ASSERT(L, "ERROR! oboro::push<int>: invalid lua_State");
  lua_pushinteger(L, a_Value);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, const char* a_Value) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<const char*>");
  OBORO_ASSERT(L, "ERROR! oboro::push<const char*>: invalid lua_State");
  lua_pushstring(L, a_Value);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, char* a_Value) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<char*>");
  OBORO_ASSERT(L, "ERROR! oboro::push<const char*>: invalid lua_State");
  lua_pushstring(L, a_Value);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, lua_CFunction a_Value) noexcept {
  OBORO_TRACE_DEBUG("oboro::push<lua_CFunction>");
  OBORO_ASSERT(L, "ERROR! oboro::push<lua_CFunction>: invalid lua_State");
  lua_pushcfunction(L, a_Value);
}
// =============================================================================
template <class T>
inline void     rawseti(lua_State* L,
                        int a_TblIdx, int a_Index, T a_Value) noexcept {
  OBORO_TRACE_DEBUG("oboro::rawseti<T>");
  OBORO_ASSERT(L, "ERROR! oboro::rawseti: invalid lua_State");
  OBORO_ASSERT(0 != a_TblIdx, "ERROR! oboro::rawseti: invalid index");
  oboro::push(L, a_Value);
  lua_rawseti(L, (0 < a_TblIdx) ? a_TblIdx : (a_TblIdx - 1), a_Index);
}
// =============================================================================
template <class T>
inline void     rawset(lua_State* L,
                       int a_TblIdx, const char* a_Key, T a_Value) noexcept {
  OBORO_TRACE_DEBUG("oboro::rawset<T>");
  OBORO_ASSERT(L, "ERROR! oboro::rawset: invalid lua_State");
  OBORO_ASSERT(0 != a_TblIdx, "ERROR! oboro::rawset: invalid index");
  OBORO_ASSERT(a_Key, "ERROR! oboro::rawset: invalid key");
  oboro::push(L, a_Key);
  oboro::push(L, a_Value);
  lua_rawset(L, (0 < a_TblIdx) ? a_TblIdx : (a_TblIdx - 2));
}
// =============================================================================
template <class T, class... Ts>
inline void     rawsets(lua_State* L, int a_TblIdx, int a_Index,
                        ::std::pair<const char*, T> a_Value,
                        Ts&&... a_tails) noexcept {
  OBORO_TRACE_DEBUG("oboro::rawsets<::std::pair<const char*, T>, Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::rawsets: invalid lua_State");
  OBORO_ASSERT(0 != a_TblIdx, "ERROR! oboro::rawsets: invalid index");
  OBORO_ASSERT(0 < a_Index, "ERROR! oboro::rawsets: invalid origin");
  oboro::rawset(L, a_TblIdx, ::std::get<0>(a_Value), ::std::get<1>(a_Value));
  oboro::rawsets(L, a_TblIdx, a_Index + 1, ::std::forward<Ts>(a_tails)...);
}
// -----------------------------------------------------------------------------
template <class T, class... Ts>
inline void     rawsets(lua_State* L, int a_TblIdx, int a_Index,
                        T a_Value, Ts&&... a_tails) noexcept {
  OBORO_TRACE_DEBUG("oboro::rawsets<T, Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::rawsets: invalid lua_State");
  OBORO_ASSERT(0 != a_TblIdx, "ERROR! oboro::rawsets: invalid index");
  OBORO_ASSERT(0 < a_Index, "ERROR! oboro::rawsets: invalid origin");
  oboro::rawseti(L, a_TblIdx, a_Index, a_Value);
  oboro::rawsets(L, a_TblIdx, a_Index + 1, ::std::forward<Ts>(a_tails)...);
}
// -----------------------------------------------------------------------------
template <class T>
inline void     rawsets(lua_State* L,
                        int a_TblIdx, int a_Index, T a_Value) noexcept {
  OBORO_TRACE_DEBUG("oboro::rawsets<T>");
  OBORO_ASSERT(L, "ERROR! oboro::rawsets: invalid lua_State");
  OBORO_ASSERT(0 != a_TblIdx, "ERROR! oboro::rawsets: invalid index");
  OBORO_ASSERT(0 < a_Index, "ERROR! oboro::rawsets: invalid origin");
  oboro::rawseti(L, a_TblIdx, a_Index, a_Value);
}
// -----------------------------------------------------------------------------
template <>
inline void     rawsets(lua_State* L, int a_TblIdx, int a_Index) noexcept {
  OBORO_TRACE_DEBUG("oboro::rawsets<>");
  OBORO_ASSERT(L, "ERROR! oboro::rawsets: invalid lua_State");
  OBORO_ASSERT(0 != a_TblIdx, "ERROR! oboro::rawsets: invalid index");
  OBORO_ASSERT(0 < a_Index, "ERROR! oboro::rawsets: invalid origin");
}
// =============================================================================
template <class... Ts> struct size_of_pair;
// -----------------------------------------------------------------------------
template <class T0, class T1>
struct size_of_pair< ::std::pair<T0, T1> > {
  static const size_t value = 1;
};
// -----------------------------------------------------------------------------
template <class T>
struct size_of_pair<T> {
  static const size_t value = 0;
};
// -----------------------------------------------------------------------------
template <class T0, class T1, class... Ts>
struct size_of_pair<::std::pair<T0, T1>, Ts...> {
  static const size_t value = 1 + size_of_pair<Ts...>::value;
};
// -----------------------------------------------------------------------------
template <class T, class... Ts>
struct size_of_pair<T, Ts...> {
  static const size_t value = size_of_pair<Ts...>::value;
};
// =============================================================================
template <class... Ts>
inline void     newtable(lua_State* L, Ts&&... a_Args) noexcept {
  OBORO_TRACE_DEBUG("oboro::newtable<Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::newtable<Ts...>: invalid lua_State");
  OBORO_TRACEF_INFO("oboro::newtable<Ts...>: lua_createtable(L, %d, %d);",
                    sizeof...(Ts) - size_of_pair<Ts...>::value,
                    size_of_pair<Ts...>::value);
  lua_createtable(L,
                  static_cast<int>(sizeof...(Ts) - size_of_pair<Ts...>::value),
                  static_cast<int>(size_of_pair<Ts...>::value));
  oboro::rawsets(L, -1, 1, ::std::forward<Ts>(a_Args)...);
}
// -----------------------------------------------------------------------------
template <>
inline void     newtable(lua_State* L) noexcept {
  OBORO_TRACE_DEBUG("oboro::newtable<Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::newtable<Ts...>: invalid lua_State");
  lua_createtable(L, 0, 0);
}
// =============================================================================
template <class... Ts>
inline void     newmetatable(lua_State* L, const char* a_Name,
                             Ts&&... a_Args) noexcept {
  OBORO_TRACE_DEBUG("oboro::newmetatable<Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::newmetatable<Ts...>: invalid lua_State");
  if (0 == luaL_newmetatable(L, a_Name)) {
    OBORO_TRACEF_WARNING("oboro::newmetatable<Ts...>: "
                         "The registry already has \"%s\"", a_Name);
  }
  oboro::rawsets(L, -1, 1, ::std::forward<Ts>(a_Args)...);
}
// -----------------------------------------------------------------------------
template <>
inline void      newmetatable(lua_State* L, const char* a_Name) noexcept {
  OBORO_TRACE_DEBUG("oboro::newmetatable<Ts...>");
  OBORO_ASSERT(L, "ERROR! oboro::newmetatable<Ts...>: invalid lua_State");
  if (0 == luaL_newmetatable(L, a_Name)) {
    OBORO_TRACEF_WARNING("oboro::newmetatable<Ts...>: "
                         "The registry already has \"%s\"", a_Name);
  }
}
// =============================================================================
template <>
inline int       get(lua_State* L, int i) {
  OBORO_TRACE_DEBUG("oboro::get<int>");
  OBORO_ASSERT(L, "ERROR! oboro::get<int>: invalid lua_State");
  is<lua_Number>(L, i);
  return static_cast<int>(lua_tointeger(L, i));
}
// -----------------------------------------------------------------------------
template <>
inline lua_Number get(lua_State* L, int i) {
  OBORO_TRACE_DEBUG("oboro::get<lua_Number>");
  OBORO_ASSERT(L, "ERROR! oboro::get<lua_Number>: invalid lua_State");
  is<lua_Number>(L, i);
  return lua_tonumber(L, i);
}
// -----------------------------------------------------------------------------
template <>
inline bool      get(lua_State* L, int i) {
  OBORO_TRACE_DEBUG("oboro::get<bool>");
  OBORO_ASSERT(L, "ERROR! oboro::get<bool>: invalid lua_State");
  is<bool>(L, i);
  return lua_toboolean(L, i);
}
// -----------------------------------------------------------------------------
template <>
inline const char* get(lua_State* L, int i) {
  OBORO_TRACE_DEBUG("oboro::get<const char*>");
  OBORO_ASSERT(L, "ERROR! oboro::get<const char*>: invalid lua_State");
  is<const char*>(L, i);
  return lua_tostring(L, i);
}
// -----------------------------------------------------------------------------
template <>
inline TABLE get(lua_State* L, int i) {
  OBORO_TRACE_DEBUG("oboro::get<TABLE>");
  OBORO_ASSERT(L, "ERROR! oboro::get<TABLE>: invalid lua_State");
  is<TABLE>(L, i);
  return TABLE();
}
// =============================================================================
template <class T, bool POP> struct gettableImpl {
  inline T operator()(lua_State* L, int a_TblIdx, int a_Index);
  inline T operator()(lua_State* L, int a_TblIdx, const char* a_Key);
};
// -----------------------------------------------------------------------------
template <class T> struct gettableImpl<T, false> {
  inline T helper(lua_State* L, int a_TblIdx) {
    is<TABLE>(L, a_TblIdx);
    lua_gettable(L,  a_TblIdx);
    return get<T>(L, -1);
  }
  inline T operator()(lua_State* L, int a_TblIdx, int a_Index) {
    lua_pushinteger(L, a_Index);
    return helper(L, (0 < a_TblIdx) ? a_TblIdx : (a_TblIdx - 1));
  }
  inline T operator()(lua_State* L, int a_TblIdx, const char* a_Key) {
    lua_pushstring(L, a_Key);
    return helper(L, (0 < a_TblIdx) ? a_TblIdx : (a_TblIdx - 1));
  }
};
// -----------------------------------------------------------------------------
template <class T> struct gettableImpl<T, true> {
  inline T operator()(lua_State* L, int a_TblIdx, int a_Index) {
    BOOST_SCOPE_EXIT_ALL(L) { lua_pop(L, 1); };
    return gettableImpl<T, false>()(L, a_TblIdx, a_Index);
  }
  inline T operator()(lua_State* L, int a_TblIdx, const char* a_Key) {
    BOOST_SCOPE_EXIT_ALL(L) { lua_pop(L, 1); };
    return gettableImpl<T, false>()(L, a_TblIdx, a_Key);
  }
};
// -----------------------------------------------------------------------------
template <class T, bool POP>
inline T         gettable(lua_State* L, int a_TblIdx, int a_Index) {
  OBORO_TRACE_DEBUG("oboro::gettable<T, POP>(..., a_Index)");
  OBORO_ASSERT(L,        "ERROR! oboro::gettable<T, POP>(..., a_Index)");
  try {
    return gettableImpl<T, POP>()(L, a_TblIdx, a_Index);
  } catch (...) {
    ::std::fprintf(stderr, "ERROR!: oboro::gettable<%s, %s>(%p, %d, %d);\n",
                   typeid(T).name(), (POP ? "true" : "false"),
                   L, a_TblIdx, a_TblIdx);
    throw;
  }
}
// -----------------------------------------------------------------------------
// UNDEFINED
template <>
inline TABLE gettable<TABLE, true>(lua_State* L, int a_TblIdx, int a_Index);
// -----------------------------------------------------------------------------
template <class T, bool POP>
inline T         gettable(lua_State* L, int a_TblIdx, const char* a_Key) {
  OBORO_TRACE_DEBUG("oboro::gettable<T, false>(..., a_Key)");
  OBORO_ASSERT(L,        "ERROR! oboro::gettable<T, false>(..., a_Key)");
  OBORO_ASSERT(a_Key,    "ERROR! oboro::gettable<T, false>(..., a_Key)");
  try {
    return gettableImpl<T, POP>()(L, a_TblIdx, a_Key);
  } catch (...) {
    ::std::fprintf(stderr, "ERROR!: oboro::gettable<%s, %s>(%p, %d, \"%s\");\n",
                   typeid(T).name(), (POP ? "true" : "false"),
                   L, a_TblIdx, a_Key);
    throw;
  }
}
// -----------------------------------------------------------------------------
// UNDEFINED
template <>
inline TABLE gettable<TABLE, true>(lua_State* L,
                                   int a_TblIdx, const char* a_Key);

}  // namespace oboro


#endif  // OBORO_OBORO_HPP_
