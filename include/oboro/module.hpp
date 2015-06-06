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
 *  @date 2015/06/06
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


#include <boost/format.hpp>

#include <string>

#undef OBORO_VERBOSITY
#define OBORO_VERBOSITY OBORO_VERBOSITY_ALL
#include "./debug.h"


namespace oboro {

// /////////////////////////////////////////////////////////////////////////////
// =============================================================================
class Module {
  // ===========================================================================
  // function  -----------------------------------------------------------------
 public:
  inline std::string const &    getPACKAGE() const noexcept;
  inline unsigned const &       getCURRENT() const noexcept;
  inline unsigned const &       getAGE() const noexcept;
  inline unsigned const &       getREVISION() const noexcept;
  inline unsigned const &       getMAJOR() const noexcept;
  inline std::string const &    getRELEASE() const noexcept;

  template <typename T>
  inline Module& def(const char*, T) noexcept;
  template <typename T>
  inline Module& def(T) noexcept;

  inline Module& end() noexcept;
  // ===========================================================================
  // variable  -----------------------------------------------------------------
 private:
  std::string   m_PACKAGE;
  unsigned      m_CURRENT;
  unsigned      m_AGE;
  unsigned      m_REVISION;
  unsigned      m_MAJOR;
  std::string   m_RELEASE;
  // ===========================================================================
  // constructor  --------------------------------------------------------------
 public:
  inline Module(const char* a_PACKAGE,
                unsigned a_CURRENT, unsigned a_AGE, unsigned a_REVISION);
  inline /* virtual */ ~Module() noexcept;
  // ---------------------------------------------------------------------------
 private:
  Module(const Module&) = delete;
  Module(Module&&) = delete;
  Module& operator =(const Module&) noexcept = delete;
  Module& operator =(Module&&) noexcept = delete;
};
// =============================================================================
inline Module::Module(const char* a_PACKAGE,
                      unsigned a_CURRENT, unsigned a_AGE, unsigned a_REVISION)
    : m_PACKAGE(a_PACKAGE)
    , m_CURRENT(a_CURRENT)
    , m_AGE(a_AGE)
    , m_REVISION(a_REVISION)
    , m_MAJOR(m_CURRENT - m_AGE)
    , m_RELEASE((boost::format("%1$d.%2$d-%3$d") %
                 m_MAJOR % m_AGE % m_REVISION).str().c_str()) {
  OBORO_TRACEF_DEBUG("oboro::Module::Module(\"%s\", \"%s\")",
                     m_PACKAGE.c_str(), m_RELEASE.c_str());
  OBORO_ASSERT(m_CURRENT > m_AGE, "ERROR!: invalid arguments.");
}
// =============================================================================
inline Module::~Module() noexcept {
  OBORO_TRACEF_DEBUG("oboro::Module(%s, \"%s\")::~Module()",
                     m_PACKAGE.c_str(), m_RELEASE.c_str());
}

// =============================================================================
inline std::string const &      Module::getPACKAGE() const noexcept {
  return m_PACKAGE;
}
// -----------------------------------------------------------------------------
inline unsigned const &         Module::getCURRENT() const noexcept {
  return m_CURRENT;
}
// -----------------------------------------------------------------------------
inline unsigned const &         Module::getAGE() const noexcept {
  return m_AGE;
}
// -----------------------------------------------------------------------------
inline unsigned const &         Module::getREVISION() const noexcept {
  return m_REVISION;
}
// -----------------------------------------------------------------------------
inline unsigned const &         Module::getMAJOR() const noexcept {
  return m_MAJOR;
}
// -----------------------------------------------------------------------------
inline std::string const &      Module::getRELEASE() const noexcept {
  return m_RELEASE;
}
// =============================================================================
template <typename T>
inline Module& Module::def(const char* a_Key, T a_Val) noexcept {
  OBORO_TRACEF_DEBUG("oboro::Module(%s, \"%s\")::def<T>(\"%s\", ...)",
                     m_PACKAGE.c_str(), m_RELEASE.c_str(), a_Key);
  return *this;
}
// =============================================================================
template <typename T>
inline Module& Module::def(T a_Val) noexcept {
  OBORO_TRACEF_DEBUG("oboro::Module(%s, \"%s\")::def<T>(...)",
                     m_PACKAGE.c_str(), m_RELEASE.c_str());
  return *this;
}
// =============================================================================
inline Module& Module::end() noexcept {
  OBORO_TRACEF_DEBUG("oboro::Module(%s, \"%s\")::end()",
                     m_PACKAGE.c_str(), m_RELEASE.c_str());
  return *this;
}

}  // namespace oboro


#endif  /* OBORO_MODULE_HPP_ */
