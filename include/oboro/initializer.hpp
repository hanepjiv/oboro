/** -*- coding:utf-8; -*-
 *  @file initializer.hpp
 *  @brief initializer.hpp
 *
 *  initializer.hpp
 *
 *  Copyright 2014 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @since 2015/06/06
 *  @date 2015/06/06
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


#include <lua.hpp>

#include "./debug.h"


namespace oboro {
// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
class Initializer {
  // ===========================================================================
  // function  -----------------------------------------------------------------
 public:
  inline operator lua_State*() const;
  // ===========================================================================
  // variable  -----------------------------------------------------------------
 private:
  lua_State* L;
  // ===========================================================================
  // constructor  --------------------------------------------------------------
 public:
  inline explicit Initializer(lua_State* a_L = luaL_newstate());
  inline /* virtual */ ~Initializer() noexcept;
  // ---------------------------------------------------------------------------
 private:
  Initializer(const Initializer&) = delete;
  Initializer(Initializer&&) = delete;
  Initializer& operator =(const Initializer&) noexcept = delete;
  Initializer& operator =(Initializer&&) noexcept = delete;
};
// =============================================================================
inline Initializer::Initializer(lua_State* a_L)
    : L(a_L) {
  OBORO_TRACE_DEBUG("oboro::Initializer::Initializer");
}
// =============================================================================
inline Initializer::~Initializer() noexcept {
  OBORO_TRACE_DEBUG("oboro::Initializer::~Initializer");
  lua_close(L);
}
// =============================================================================
inline Initializer::operator lua_State*() const {
  OBORO_TRACE_DEBUG("oboro::Initializer::operator lua_State*");
  return L;
}
}  // namespace oboro
