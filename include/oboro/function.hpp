/** -*- mode:c++; coding:utf-8-unix; -*-
 *  @file function.hpp
 *  @brief function.hpp
 *
 *  function.hpp
 *
 *  Copyright 2014 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @copyright The MIT License (MIT)
 *  @since 2015/06/03
 *  @date 2016/02/11
 */

#ifndef OBORO_FUNCTION_HPP_
#define OBORO_FUNCTION_HPP_

#include "./oboro.hpp"

// #############################################################################
namespace oboro {
// =============================================================================
extern int oboroClosure(lua_State* L);
}  // namespace oboro
// #############################################################################
namespace oboro {
// =============================================================================
int oboroClosure(lua_State* L) {
  lua_CFunction f =
      reinterpret_cast<lua_CFunction>(lua_touserdata(L, lua_upvalueindex(1)));
  ::std::printf("%p\n", f);
  return f(L);
}
}  // namespace oboro

#endif  /* OBORO_FUNCTION_HPP_ */
