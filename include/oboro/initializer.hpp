/** -*- mode:c++; coding:utf-8-unix; -*-
 *  @file initializer.hpp
 *  @brief initializer.hpp
 *
 *  initializer.hpp
 *
 *  Copyright 2014 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @copyright The MIT License (MIT)
 *  @since 2015/06/06
 *  @date 2015/06/06
 */

#include <lua.hpp>

#include "./debug.h"

namespace oboro {
// ////////////////////////////////////////////////////////////////////////////
// ============================================================================
class Initializer {
  // ==========================================================================
  // function  ----------------------------------------------------------------
 public:
  inline operator lua_State*() const;
  // ==========================================================================
  // variable  ----------------------------------------------------------------
 private:
  lua_State* L;
  // ==========================================================================
  // constructor  -------------------------------------------------------------
 public:
  inline explicit Initializer(lua_State* a_L = luaL_newstate());
  inline /* virtual */ ~Initializer() noexcept;
  // --------------------------------------------------------------------------
 private:
  Initializer(const Initializer&) = delete;
  Initializer(Initializer&&) = delete;
  Initializer& operator =(const Initializer&) noexcept = delete;
  Initializer& operator =(Initializer&&) noexcept = delete;
};
// ============================================================================
inline Initializer::Initializer(lua_State* a_L)
    : L(a_L) {
  OBORO_TRACE_DEBUG("oboro::Initializer::Initializer");
}
// ============================================================================
inline Initializer::~Initializer() noexcept {
  OBORO_TRACE_DEBUG("oboro::Initializer::~Initializer");
  lua_close(L);
}
// ============================================================================
inline Initializer::operator lua_State*() const {
  OBORO_TRACE_DEBUG("oboro::Initializer::operator lua_State*");
  return L;
}
}  // namespace oboro
