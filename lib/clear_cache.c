/* ===-- clear_cache.c - Implement __clear_cache ---------------------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 * ===----------------------------------------------------------------------===
 */

#include "int_lib.h"

#if __APPLE__
#include <AvailabilityMacros.h>
#define	__DARWIN_VERSION__	((MAC_OS_X_VERSION_MIN_REQUIRED - MAC_OS_X_VERSION_10_0)/10 +4)
#if __DARWIN_VERSION__ >= 9
/* only appeared in 10.5+ (darwin9) */
  #include <libkern/OSCacheControl.h>
#else
  #include "OSCacheControl.h"		/* provided */
#endif
#endif

/*
 * The compiler generates calls to __clear_cache() when creating 
 * trampoline functions on the stack for use with nested functions.
 * It is expected to invalidate the instruction cache for the 
 * specified range.
 */

void __clear_cache(void* start, void* end)
{
#if __i386__ || __x86_64__
/*
 * Intel processors have a unified instruction and data cache
 * so there is nothing to do
 */
#else
    #if __APPLE__
        /* On Darwin, sys_icache_invalidate() provides this functionality */
        sys_icache_invalidate(start, end-start);
    #else
        compilerrt_abort();
    #endif
#endif
}

