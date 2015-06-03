/** -*- coding:utf-8; -*-
 *  @file module.hpp
 *  @brief module.hpp
 *
 *  module.hpp
 *
 *  Copyright 2015 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @since 2015/06/03
 *  @date 2015/06/03
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


#ifndef OBORO_MODULE_HPP_
#define OBORO_MODULE_HPP_


#include <string>

#undef OBORO_VERBOSITY
#define OBORO_VERBOSITY OBORO_VERBOSITY_ALL
#include "./debug.h"


namespace oboro {

// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
class Module {
  // ===========================================================================
  // define  -------------------------------------------------------------------
 public:
  // ===========================================================================
  // exception  ----------------------------------------------------------------
 public:
  // ===========================================================================
  // static function  ----------------------------------------------------------
 public:
  // ===========================================================================
  // static variable  ----------------------------------------------------------
 public:
  // ===========================================================================
  // function  -----------------------------------------------------------------
 public:
  inline void end() noexcept;
  // ===========================================================================
  // variable  -----------------------------------------------------------------
 private:
  std::string m_Name;
  // ===========================================================================
  // constructor  --------------------------------------------------------------
 public:
  inline explicit Module(const char* a_Name);
  /* virtual */ ~Module() noexcept;
  // ---------------------------------------------------------------------------
 private:
  Module(const Module&) = delete;
  Module(Module&&) = delete;
  Module& operator =(const Module&) noexcept = delete;
  Module& operator =(Module&&) noexcept = delete;
};
// =============================================================================
inline Module::Module(const char* a_Name)
    : m_Name(a_Name) {
  OBORO_TRACEF_DEBUG("oboro::Module::Module(%s)", m_Name.c_str());
}
// =============================================================================
inline Module::~Module() noexcept {
  OBORO_TRACEF_DEBUG("oboro::Module::~Module(%s)", m_Name.c_str());
}
// =============================================================================
inline void Module::end() noexcept {
  OBORO_TRACEF_DEBUG("oboro::Module::end(%s)", m_Name.c_str());
}

}  // namespace oboro


#endif  /* OBORO_MODULE_HPP_ */
