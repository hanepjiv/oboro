/** -*- mode:c++; coding:utf-8-unix; -*-
 *  @file module.hpp
 *  @brief module.hpp
 *
 *  module.hpp
 *
 *  Copyright 2014 hanepjiv
 *
 *  @author hanepjiv <hanepjiv@gmail.com>
 *  @copyright The MIT License (MIT)
 *  @since 2015/06/03
 *  @date 2016/10/16
 */

#ifndef OBORO_MODULE_HPP_
#define OBORO_MODULE_HPP_

#include <boost/format.hpp>

#include <string>
#include <cstdint>
#include <bitset>
#include <stdexcept>

#undef OBORO_VERBOSITY
#define OBORO_VERBOSITY OBORO_VERBOSITY_ALL
#include "./debug.h"

namespace oboro {

// ////////////////////////////////////////////////////////////////////////////
// ============================================================================
class Module {
  // ==========================================================================
  // define  ------------------------------------------------------------------
 public:
  enum class Flag : intptr_t { END, };
  // ==========================================================================
  // function  ----------------------------------------------------------------
 public:
  inline ::std::string const &             getPACKAGE() const noexcept;
  inline unsigned                        getCURRENT() const noexcept;
  inline unsigned                        getAGE() const noexcept;
  inline unsigned                        getREVISION() const noexcept;
  inline unsigned                        getMAJOR() const noexcept;
  inline ::std::string const &             getVERSION() const noexcept;

  template <typename T> inline Module&   def(const char*, T);
  template <typename T> inline Module&   def(T);
  inline Module&                         end();
  // ==========================================================================
  // variable  ----------------------------------------------------------------
 private:
  ::std::bitset<sizeof(::std::intptr_t)>     m_Flags;
  const unsigned                         m_CURRENT;
  const unsigned                         m_AGE;
  const unsigned                         m_REVISION;
  const ::std::string                      m_VERSION;
  const ::std::string                      m_PACKAGE;
  // ==========================================================================
  // constructor  -------------------------------------------------------------
 public:
  inline                 Module(const char* a_PACKAGE,
                                unsigned a_CURRENT,
                                unsigned a_AGE,
                                unsigned a_REVISION);
  inline /* virtual */  ~Module() noexcept;
  // --------------------------------------------------------------------------
 private:
  explicit               Module(const Module&)                   = delete;
  explicit               Module(Module&&)                        = delete;
  Module&                operator =(const Module&) noexcept      = delete;
  Module&                operator =(Module&&) noexcept           = delete;
};
// ============================================================================
inline Module::Module(const char* a_PACKAGE,
                      unsigned a_CURRENT,
                      unsigned a_AGE,
                      unsigned a_REVISION) :
    m_Flags(0),
    m_CURRENT(a_CURRENT),
    m_AGE(a_AGE),
    m_REVISION(a_REVISION),
    m_VERSION((::boost::format("%1$d.%2$d-%3$d") %
               (m_CURRENT - m_AGE) % m_AGE % m_REVISION).str().c_str()),
    m_PACKAGE(a_PACKAGE) {
  OBORO_TRACEF_DEBUG("oboro::Module::Module(\"%s\", \"%s\")",
                     m_PACKAGE.c_str(), m_VERSION.c_str());
  OBORO_ASSERT(m_CURRENT > m_AGE, "ERROR!: invalid arguments.");
}
// ============================================================================
inline Module::~Module() noexcept {
  OBORO_TRACEF_DEBUG("oboro::Module(%s, \"%s\")::~Module()",
                     m_PACKAGE.c_str(), m_VERSION.c_str());
}
// ============================================================================
inline ::std::string const & Module::getPACKAGE() const noexcept {
  return m_PACKAGE;
}
// ----------------------------------------------------------------------------
inline unsigned Module::getCURRENT() const noexcept {
  return m_CURRENT;
}
// ----------------------------------------------------------------------------
inline unsigned Module::getAGE() const noexcept {
  return m_AGE;
}
// ----------------------------------------------------------------------------
inline unsigned Module::getREVISION() const noexcept {
  return m_REVISION;
}
// ----------------------------------------------------------------------------
inline unsigned Module::getMAJOR() const noexcept {
  return (m_CURRENT - m_AGE);
}
// ----------------------------------------------------------------------------
inline ::std::string const & Module::getVERSION() const noexcept {
  return m_VERSION;
}
// ============================================================================
template <typename T>
inline Module& Module::def(const char* a_Key, T a_Val) {
  OBORO_TRACEF_DEBUG("oboro::Module(%s, \"%s\")::def<T>(\"%s\", ...)",
                     m_PACKAGE.c_str(), m_VERSION.c_str(), a_Key);
  if (m_Flags.test(static_cast<size_t>(Flag::END))) {
    throw ::std::runtime_error((::boost::format(
        "ERROR!: oboro::Module(%1%, \"%2%\")::def<T>(\"%3%\", ...)): "
        "already end.") % m_PACKAGE % m_VERSION % a_Key).str().c_str());
  }
  return *this;
}
// ============================================================================
template <typename T>
inline Module& Module::def(T a_Val) {
  OBORO_TRACEF_DEBUG("oboro::Module(%s, \"%s\")::def<T>(...)",
                     m_PACKAGE.c_str(), m_VERSION.c_str());
  if (m_Flags.test(static_cast<size_t>(Flag::END))) {
    throw ::std::runtime_error((::boost::format(
        "ERROR!: oboro::Module(%1%, \"%2%\")::def(...): "
        "already end.") % m_PACKAGE % m_VERSION).str().c_str());
  }
  return *this;
}
// ============================================================================
inline Module& Module::end() {
  OBORO_TRACEF_DEBUG("oboro::Module(%s, \"%s\")::end()",
                     m_PACKAGE.c_str(), m_VERSION.c_str());
  if (m_Flags.test(static_cast<size_t>(Flag::END))) {
    throw ::std::runtime_error((::boost::format(
        "ERROR!: oboro::Module(%1%, \"%2%\")::end(): "
        "already end.") % m_PACKAGE % m_VERSION).str().c_str());
  }
  m_Flags.set(static_cast<size_t>(Flag::END));
  return *this;
}

}  // namespace oboro

#endif  // OBORO_MODULE_HPP_
