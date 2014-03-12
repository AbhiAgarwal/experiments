//
//  Copyright (C) 2009-2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOSTER_BUILD_CONFIG_H
#define BOOSTER_BUILD_CONFIG_H

//
// GCC's __sync_* operations
//
#define BOOSTER_HAS_GCC_SYNC

//
// STDC++ library atomic ops in <bits/atomicity.h>
//

/* #undef BOOSTER_HAVE_GCC_BITS_EXCHANGE_AND_ADD */

//
// STDC++ library atomic ops in <ext/atomicity.h>
//

/* #undef BOOSTER_HAVE_GCC_EXT_EXCHANGE_AND_ADD */

//
// FreeBSD atomic operations
//

/* #undef BOOSTER_HAVE_FREEBSD_ATOMIC */

//
// Solaris atomic operations
//

/* #undef BOOSTER_HAVE_SOLARIS_ATOMIC */

//
// Mac OS X atomic operations
//

#define BOOSTER_HAVE_MAC_OS_X_ATOMIC

//
// Have <stdint.h>
//

#define BOOSTER_HAVE_STDINT_H

//
// Have <inttypes.h>
//

#define BOOSTER_HAVE_INTTYPES_H

//
// Have IPv6 support
//

#define BOOSTER_AIO_HAVE_PF_INET6
 
#define BOOSTER_HAVE_EXECINFO

/* Define to module suffix. */
#define BOOSTER_LIBRARY_SUFFIX ".dylib"

/* Define to module suffix. */
#define BOOSTER_LIBRARY_PREFIX "lib"

#endif
