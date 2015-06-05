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


namespace oboro {
// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
typedef struct NIL_ NIL;
struct NIL_     {};
// -----------------------------------------------------------------------------
using IdxTable  = std::vector<boost::any>;
// -----------------------------------------------------------------------------
using KeyVal    = std::pair<std::string, boost::any>;
using KeyTable  = std::vector<KeyVal>;
// =============================================================================
inline void     printStack(lua_State* L) noexcept;
// -----------------------------------------------------------------------------
template <typename T>
inline void     push(lua_State* L, T a_val);
// -----------------------------------------------------------------------------
template <typename T>
inline void     rawseti(lua_State* L, int a_idx, int a_i, T&& a_val);
// -----------------------------------------------------------------------------
template <typename T>
inline void     rawset(lua_State* L,
                       int a_idx, const char* a_key, T&& a_val);
// -----------------------------------------------------------------------------
template <typename T>
inline void     rawsets(lua_State*, int, T &&);
// -----------------------------------------------------------------------------
template <typename T>
inline void     createtable(lua_State*, int) noexcept;
// -----------------------------------------------------------------------------
template <typename T>
inline int      newtable(lua_State*, T &&);
// -----------------------------------------------------------------------------
template <typename T>
inline int      newmetatable(lua_State*, const std::string&, T &&);
}  // namespace oboro

namespace oboro {
// /////////////////////////////////////////////////////////////////////////////
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
      case LUA_TFUNCTION: {
        if (lua_iscfunction(L, i)) {
          std::printf("C Function   : %p", lua_tocfunction(L, i));
        } else {
          std::printf("Lua Function : %p", lua_topointer(L, i));
        }
        break;
      }
      case LUA_TUSERDATA:      std::printf("%p", lua_touserdata(L, i));   break;
      case LUA_TTHREAD:        std::printf("%p", lua_tothread(L, i));     break;
      default:                                                            break;
    }
    std::printf("\n");
  }
}
// =============================================================================
template <>
inline void     push(lua_State* L, NIL /* a_nil */) {
  OBORO_TRACE_DEBUG("oboro::push<NIL>");
  OBORO_ASSERT(L, "ERROR! oboro::push<NIL>: invalid lua_State");
  lua_pushnil(L);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, bool a_val) {
  OBORO_TRACE_DEBUG("oboro::push<bool>");
  OBORO_ASSERT(L, "ERROR! oboro::push<bool>: invalid lua_State");
  lua_pushboolean(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, void* a_val) {
  OBORO_TRACE_DEBUG("oboro::push<void*>");
  OBORO_ASSERT(L, "ERROR! oboro::push<void*>: invalid lua_State");
  lua_pushlightuserdata(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, lua_Number a_val) {
  OBORO_TRACE_DEBUG("oboro::push<lua_Number>");
  OBORO_ASSERT(L, "ERROR! oboro::push<lua_Number>: invalid lua_State");
  lua_pushnumber(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, lua_Integer a_val) {
  OBORO_TRACE_DEBUG("oboro::push<lua_Integer>");
  OBORO_ASSERT(L, "ERROR! oboro::push<lua_Integer>: invalid lua_State");
  lua_pushinteger(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, const char* a_val) {
  OBORO_TRACE_DEBUG("oboro::push<const char*>");
  OBORO_ASSERT(L, "ERROR! oboro::push<const char*>: invalid lua_State");
  lua_pushstring(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, char* a_val) {
  OBORO_TRACE_DEBUG("oboro::push<char*>");
  OBORO_ASSERT(L, "ERROR! oboro::push<const char*>: invalid lua_State");
  lua_pushstring(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, lua_CFunction a_val) {
  OBORO_TRACE_DEBUG("oboro::push<lua_CFunction>");
  OBORO_ASSERT(L, "ERROR! oboro::push<lua_CFunction>: invalid lua_State");
  lua_pushcfunction(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, IdxTable const & a_val) {
  OBORO_TRACE_DEBUG("oboro::push<IdxTable>");
  OBORO_ASSERT(L, "ERROR! oboro::push<IdxTable>: invalid lua_State");
  newtable(L, a_val);
}
// -----------------------------------------------------------------------------
template <>
inline void     push(lua_State* L, KeyTable const & a_val) {
  OBORO_TRACE_DEBUG("oboro::push<KeyTable>");
  OBORO_ASSERT(L, "ERROR! oboro::push<KeyTable>: invalid lua_State");
  newtable(L, a_val);
}
// =============================================================================
template <typename T>
inline void     rawseti(lua_State* L,
                        int a_idx, int a_i, T&& a_val) {
  OBORO_TRACE_DEBUG("oboro::rawseti<T>");
  OBORO_ASSERT(L, "ERROR! oboro::rawseti: invalid lua_State");
  OBORO_ASSERT(0 != a_idx, "ERROR! oboro::rawseti: invalid index");
  push(L, a_val);
  lua_rawseti(L, (0 < a_idx) ? a_idx : (a_idx - 1), a_i);
}
// -----------------------------------------------------------------------------
template <>
inline void     rawseti(lua_State* L,
                        int a_idx, int a_i, IdxTable const &a_val) {
  newtable(L, a_val);
  lua_rawseti(L, (0 < a_idx) ? a_idx : (a_idx - 1), a_i);
}
// -----------------------------------------------------------------------------
template <>
inline void     rawseti(lua_State* L,
                        int a_idx, int a_i, KeyTable const &a_val) {
  newtable(L, a_val);
  lua_rawseti(L, (0 < a_idx) ? a_idx : (a_idx - 1), a_i);
}
// =============================================================================
template <typename T>
inline void     rawset(lua_State* L,
                       int a_idx, const char* a_key, T&& a_val) {
  OBORO_TRACE_DEBUG("oboro::rawset<T>");
  OBORO_ASSERT(L, "ERROR! oboro::rawset: invalid lua_State");
  OBORO_ASSERT(0 != a_idx, "ERROR! oboro::rawset: invalid index");
  OBORO_ASSERT(a_key, "ERROR! oboro::rawset: invalid key");
  push(L, a_key);
  push(L, a_val);
  lua_rawset(L, (0 < a_idx) ? a_idx : (a_idx - 2));
}
// -----------------------------------------------------------------------------
template <>
inline void     rawset(lua_State* L, int a_idx,
                       const char* a_key, IdxTable const &a_val) {
  push(L, a_key);
  newtable(L, a_val);
  lua_rawset(L, (0 < a_idx) ? a_idx : (a_idx - 2));
}
// -----------------------------------------------------------------------------
template <>
inline void     rawset(lua_State* L, int a_idx,
                       const char* a_key, KeyTable const &a_val) {
  push(L, a_key);
  newtable(L, a_val);
  lua_rawset(L, (0 < a_idx) ? a_idx : (a_idx - 2));
}
// =============================================================================
template <>
inline void     rawsets(lua_State* L, int a_idx, IdxTable const & a_Table) {
  OBORO_TRACE_DEBUG("oboro::rawsets<IdxTable const &>");
  OBORO_ASSERT(L, "ERROR! oboro::rawsets<IdxTable const &>: invalid lua_State");

  const size_t s = a_Table.size();
  if (0 == s) { return; }

  for (size_t i = 0; i < s; ++i) {
    using boost::any_cast;
    const boost::any& v = a_Table[i];
    const int j = static_cast<int>(i) + 1;
    if        (false) {
    } else if (v.type() == typeid(NIL)) {
      rawseti(L, a_idx, j, any_cast<NIL>(v));
    } else if (v.type() == typeid(bool)) {
      rawseti(L, a_idx, j, any_cast<bool>(v));
    } else if (v.type() == typeid(void*)) {
      rawseti(L, a_idx, j, any_cast<void*>(v));
    } else if (v.type() == typeid(lua_Number)) {
      rawseti(L, a_idx, j, any_cast<lua_Number>(v));
    } else if (v.type() == typeid(lua_Integer)) {
      rawseti(L, a_idx, j, any_cast<lua_Integer>(v));
    } else if (v.type() == typeid(char*)) {
      rawseti(L, a_idx, j, any_cast<char*>(v));
    } else if (v.type() == typeid(const char*)) {
      rawseti(L, a_idx, j, any_cast<const char*>(v));
    } else if (v.type() == typeid(lua_CFunction)) {
      rawseti(L, a_idx, j, any_cast<lua_CFunction>(v));
    } else if (v.type() == typeid(IdxTable const &)) {
      rawseti(L, a_idx, j, any_cast<IdxTable const &>(v));
    } else if (v.type() == typeid(KeyTable const &)) {
      rawseti(L, a_idx, j, any_cast<KeyTable const &>(v));
    } else {
      throw std::invalid_argument((boost::format(
          "ERROR!: oboro::rawsets<const IdxTable&>: unknown type %1%.") %
                                   v.type().name()).str());
    }
  }
}
// -----------------------------------------------------------------------------
template <>
inline void     rawsets(lua_State* L, int a_idx, IdxTable & a_Table) {
  OBORO_TRACE_DEBUG("oboro::rawsets<IdxTable &>");
  rawsets(L, a_idx, static_cast<IdxTable const &>(a_Table));
}
// -----------------------------------------------------------------------------
template <>
inline void     rawsets(lua_State* L, int a_idx, IdxTable && a_Table) {
  OBORO_TRACE_DEBUG("oboro::rawsets<IdxTable &&>");
  rawsets(L, a_idx, static_cast<IdxTable const &>(a_Table));
}
// -----------------------------------------------------------------------------
template <>
inline void     rawsets(lua_State* L, int a_idx, KeyTable const & a_Table) {
  OBORO_TRACE_DEBUG("oboro::rawsets<KeyTable const &>");
  OBORO_ASSERT(L,
               "ERROR! oboro::rawsets<KeyTable const &>: invalid lua_State");

  if (0 == a_Table.size()) { return; }

  for (const KeyVal& v : a_Table) {
    using std::get;
    using boost::any_cast;
    if        (false) {
    } else if (get<1>(v).type() == typeid(NIL)) {
      rawset(L, a_idx, get<0>(v).c_str(), any_cast<NIL>(get<1>(v)));
    } else if (get<1>(v).type() == typeid(bool)) {
      rawset(L, a_idx, get<0>(v).c_str(), any_cast<bool>(get<1>(v)));
    } else if (get<1>(v).type() == typeid(void*)) {
      rawset(L, a_idx, get<0>(v).c_str(), any_cast<void*>(get<1>(v)));
    } else if (get<1>(v).type() == typeid(lua_Number)) {
      rawset(L, a_idx, get<0>(v).c_str(), any_cast<lua_Number>(get<1>(v)));
    } else if (get<1>(v).type() == typeid(lua_Integer)) {
      rawset(L, a_idx, get<0>(v).c_str(), any_cast<lua_Integer>(get<1>(v)));
    } else if (get<1>(v).type() == typeid(char*)) {
      rawset(L, a_idx, get<0>(v).c_str(), any_cast<char*>(get<1>(v)));
    } else if (get<1>(v).type() == typeid(const char*)) {
      rawset(L, a_idx, get<0>(v).c_str(), any_cast<const char*>(get<1>(v)));
    } else if (get<1>(v).type() == typeid(lua_CFunction)) {
      rawset(L, a_idx, get<0>(v).c_str(), any_cast<lua_CFunction>(get<1>(v)));
    } else if (get<1>(v).type() == typeid(IdxTable const &)) {
      rawset(L, a_idx,
             get<0>(v).c_str(), any_cast<IdxTable const &>(get<1>(v)));
    } else if (get<1>(v).type() == typeid(KeyTable const &)) {
      rawset(L, a_idx,
             get<0>(v).c_str(), any_cast<KeyTable const &>(get<1>(v)));
    } else {
      throw std::invalid_argument((boost::format(
          "ERROR!: oboro::rawsets<const KeyTable&>: unknown type %1%.") %
                                   std::get<1>(v).type().name()).str());
    }
  }
}
// -----------------------------------------------------------------------------
template <>
inline void     rawsets(lua_State* L, int a_idx, KeyTable & a_Table) {
  OBORO_TRACE_DEBUG("oboro::rawsets<KeyTable &>");
  rawsets(L, a_idx, static_cast<KeyTable const &>(a_Table));
}
// -----------------------------------------------------------------------------
template <>
inline void     rawsets(lua_State* L, int a_idx, KeyTable && a_Table) {
  OBORO_TRACE_DEBUG("oboro::rawsets<KeyTable &&>");
  rawsets(L, a_idx, static_cast<KeyTable const &>(a_Table));
}
// =============================================================================
template <>
inline void     createtable<IdxTable>(lua_State* L, int s) noexcept {
  OBORO_TRACE_DEBUG("oboro::createtable<IdxTable>");
  OBORO_ASSERT(L, "ERROR! oboro::createtable<IdxTable>: invalid lua_State");
  lua_createtable(L, static_cast<int>(s), 0);
}
// -----------------------------------------------------------------------------
template <>
inline void     createtable<KeyTable>(lua_State* L, int s) noexcept {
  OBORO_TRACE_DEBUG("oboro::createtable<KeyTable>");
  OBORO_ASSERT(L, "ERROR! oboro::createtable<KeyTable>: invalid lua_State");
  lua_createtable(L, 0, static_cast<int>(s));
}
// =============================================================================
template <typename T>
inline int      newtable(lua_State* L, T && a_Table) {
  OBORO_TRACE_DEBUG("oboro::newtable<T>");
  OBORO_ASSERT(L, "ERROR! oboro::newtable<T>: invalid lua_State");
  createtable<typename std::decay<T>::type>(L,
                                            static_cast<int>(a_Table.size()));
  if (!a_Table.empty()) {
    rawsets(L, -1, std::forward<T>(a_Table));
  }
  return 1;
}
// =============================================================================
template <typename T>
inline int      newmetatable(lua_State* L,
                             const std::string& a_name, T && a_Table) {
  OBORO_TRACE_DEBUG("oboro::newmetatable<T &&>");
  OBORO_ASSERT(L, "ERROR! oboro::newmetatable<T &&>: invalid lua_State");
  if (0 == luaL_newmetatable(L, a_name.c_str())) {
    OBORO_TRACEF_WARNING("oboro::newmetatable<T &&>: "
                         "The registry already has \"%s\"", a_name.c_str());
  }
  if (!a_Table.empty()) {
    rawsets(L, -1, std::forward<T>(a_Table));
  }
  return 1;
}

}  // namespace oboro


#endif  // OBORO_OBORO_HPP_
