/** -*- coding:utf-8; mode:c; -*-
 *  @file config.h.in
 *  @brief config.h.in
 *
 *  config.h.in
 *
 *  Copyright 2014 hanepjiv
 *
 *  @author hanepjiv <hagumo@gmail.com>
 *  @since 2015/08/08
 *  @date 2015/09/25
 */


#ifndef @OBORO_PACKAGE_UPPER@_CONFIG_H_
#define @OBORO_PACKAGE_UPPER@_CONFIG_H_

#define PACKAGE                 "@OBORO_PACKAGE@"
#define PACKAGE_BUGREPORT       "@OBORO_BUGREPORT@"
#define PACKAGE_NAME            "@OBORO_PACKAGE@"
#define PACKAGE_STRING          "@OBORO_PACKAGE@ @OBORO_VERSION@"
#define PACKAGE_TARNAME         "@OBORO_PACKAGE@"
#define PACKAGE_URL             "@OBORO_URL@"
#define PACKAGE_VERSION         "@OBORO_VERSION@"
#define VERSION                 "@OBORO_VERSION@"

#if @Boost_FOUND@
#  define HAVE_BOOST 1
#else
#  undef HAVE_BOOST
#endif

#endif  /* @OBORO_PACKAGE_UPPER@_CONFIG_H_ */
