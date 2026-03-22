#ifndef TWBL_SRC_TWBL_TEEWORLDS_BASE_DBG_H
#define TWBL_SRC_TWBL_TEEWORLDS_BASE_DBG_H

#if __has_include(<base/dbg.h>)
#include <base/dbg.h>
#elif __has_include(<base/system.h>)
#include <base/system.h>
#else

#include <cstdio>
#include <cstring>
#include <ctime>

#include <twbl/teeworlds/base/detect.h>

#ifdef CONF_FAMILY_UNIX
#include <sys/stat.h>
#endif

#ifdef CONF_FAMILY_WINDOWS
#define NOMINMAX
#include <windows.h>

#include <string>
#endif

#ifdef __GNUC__
#define GNUC_ATTRIBUTE(x) __attribute__(x)
#else
#define GNUC_ATTRIBUTE(x)
#endif

#define dbg_assert(test, msg) dbg_assert_imp(__FILE__, __LINE__, test, msg)

void dbg_msg(const char *sys, const char *fmt, ...)
	GNUC_ATTRIBUTE((format(printf, 2, 3)));

void dbg_break();
void dbg_assert_imp(const char *filename, int line, bool test, const char *msg);

#endif // __has_include(<base/system.h>)
#endif // TWBL_SRC_TWBL_TEEWORLDS_BASE_DBG_H
