///////////////////////////////////////////////////////////////////////////////
//                                                                             
//  Copyright (C) 2008-2012  Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>     
//                                                                             
//  See accompanying file COPYING.TXT file for licensing details.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CPPCMS_CONFIG_H
#define CPPCMS_CONFIG_H

/* Have stdint.h */
#define CPPCMS_HAVE_STDINT_H

/* Have _atol64 */
/* #undef CPPCMS_HAVE_ATOI64 */

/* Have atoll */
#define CPPCMS_HAVE_ATOLL

#if !defined(CPPCMS_HAVE_ATOLL) && defined(CPPCMS_HAVE_ATOI64)
#define atoll _atoi64
#endif

/* Have stat */

#define CPPCMS_HAVE_STAT

/* Have _stat */

/* #undef CPPCMS_HAVE__STAT */

/* Have tm.tm_zone */

#define CPPCMS_HAVE_BSD_TM

/* Have snprintf */
#define CPPCMS_HAVE_SNPRINTF


/* Have inttypes.h */
#define CPPCMS_HAVE_INTTYPES_H

/* "Have C++0x std::uXXstring" */
#define CPPCMS_HAVE_CPP0X_UXSTRING

#ifdef CPPCMS_HAVE_CPP0X_UXSTRING
# define CPPCMS_HAS_CHAR16_T
# define CPPCMS_HAS_CHAR32_T
#endif

/* "Have C++0x auto" */
#define CPPCMS_HAVE_CPP_0X_AUTO

/* "Have C++0x decltype" */
#define CPPCMS_HAVE_CPP_0X_DECLTYPE

/* "Have g++ typeof" */
#define CPPCMS_HAVE_GCC_TYPEOF

/* "Enable ICU support" */
/* #undef CPPCMS_HAVE_ICU */

/* Use STD locales instead of ICU ones */
/* #undef CPPCMS_DISABLE_ICU_LOCALIZATION */

/* "Enable ICONV support" */
/* #undef CPPCMS_HAVE_ICONV */

/* "Enable GNU GCrypt library */
/* #undef CPPCMS_HAVE_GCRYPT */

/* "Enable OpenSSL library */
#define CPPCMS_HAVE_OPENSSL

/* "Have std::wstring" */
#define CPPCMS_HAVE_STD_WSTRING

#ifndef CPPCMS_HAVE_STD_WSTRING
# define CPPCMS_NO_STD_WSTRING
#endif 

/* Have canonicalize_file_name */

/* #undef CPPCMS_HAVE_CANONICALIZE_FILE_NAME */

/* "Have g++ typeof" */
#define CPPCMS_HAVE_UNDERSCORE_TYPEOF

/* Define to the full name of this package. */
#define CPPCMS_PACKAGE_NAME "CppCMS"

/* Define to the full name and version of this package. */
#define CPPCMS_PACKAGE_STRING "CppCMS/1.0.4"

/* Define to the version of this package. */
#define CPPCMS_PACKAGE_VERSION "1.0.4"

/* Define to module suffix. */
#define CPPCMS_LIBRARY_SUFFIX ".dylib"

/* Define to module suffix. */
#define CPPCMS_LIBRARY_PREFIX "lib"

#define CPPCMS_HAS_FCGI
#define CPPCMS_HAS_SCGI
#define CPPCMS_HAS_HTTP
/* #undef CPPCMS_NO_TCP_CACHE */
/* #undef CPPCMS_NO_CACHE */
/* #undef CPPCMS_NO_PREFOK_CACHE */
/* #undef CPPCMS_NO_GZIP */
/* #undef CPPCMS_SQLITE_LINK_STATIC */


#endif
