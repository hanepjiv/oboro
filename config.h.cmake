/** -*- coding:utf-8; mode:c; -*-
 *  @file config.h.in
 *  @brief config.h.in
 *
 *  config.h.in
 *
 *  Copyright 2015 hanepjiv
 *
 *  @author hanepjiv <hagumo@gmail.com>
 *  @since 2015/08/08
 *  @date 2015/08/11
 */


#ifndef @OBORO_PACKAGE_UPPER@_CONFIG_H_
#define @OBORO_PACKAGE_UPPER@_CONFIG_H_

#define PACKAGE                         "@OBORO_PACKAGE@"
#define PACKAGE_BUGREPORT               "@OBORO_BUGREPORT@"
#define PACKAGE_NAME                    "@OBORO_PACKAGE@"
#define PACKAGE_STRING                  "@OBORO_PACKAGE@ @OBORO_RELEASE@"
#define PACKAGE_TARNAME                 "@OBORO_PACKAGE@"
#define PACKAGE_URL                     "@OBORO_URL@"
#define PACKAGE_VERSION                 "@OBORO_RELEASE@"
#define VERSION                         "@OBORO_RELEASE@"

#if @Boost_FOUND@
#  define HAVE_BOOST 1
#else
#  undef HAVE_BOOST
#endif

#endif  /* @OBORO_PACKAGE_UPPER@_CONFIG_H_ */
