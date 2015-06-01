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
 *  @date 2015/05/29
 */


/* ########################################################################## */
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


#ifndef OBORO_OBORO_HPP_
#define OBORO_OBORO_HPP_


#include <lua.hpp>


namespace oboro {

// =============================================================================
inline void printStack(lua_State* L) {
  std::cout << "=================================================" << std::endl;
  int n = lua_gettop(L);
  for (int i = n; i >= 1; --i) {
    int t = lua_type(L, i);
    std::cout << i << " / " << i - n - 1 << "\t" << lua_typename(L, t) << "\t";
    switch (t) {
      case LUA_TNIL:                                                    break;
      case LUA_TBOOLEAN:       std::cout << lua_toboolean(L, i);        break;
      case LUA_TLIGHTUSERDATA: std::cout << lua_touserdata(L, i);       break;
      case LUA_TNUMBER:        std::cout << lua_tonumber(L, i);         break;
      case LUA_TSTRING:        std::cout << lua_tostring(L, i);         break;
      case LUA_TTABLE:                                                  break;
      case LUA_TFUNCTION:                                               break;
      case LUA_TUSERDATA:      std::cout << lua_touserdata(L, i);       break;
      case LUA_TTHREAD:        std::cout << lua_tothread(L, i);         break;
      default:                                                          break;
    }
    std::cout << std::endl;
  }
  std::cout << "-------------------------------------------------" << std::endl;
}

}  // namespace oboro


#endif  /* OBORO_OBORO_HPP_ */
