#ifndef TWBL_SRC_TWBL_TEEWORLDS_BASE_SYSTEM_H
#define TWBL_SRC_TWBL_TEEWORLDS_BASE_SYSTEM_H

#if __has_include(<base/system.h>)
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

int str_length(const char *str);

void dbg_break();
void dbg_assert_imp(const char *filename, int line, bool test, const char *msg);

/**
 * @ingroup Debug
 *
 * Breaks into the debugger based on a test.
 *
 * @param test Result of the test.
 * @param msg Message that should be printed if the test fails.
 *
 * @remark Also works in release mode.
 *
 * @see dbg_break
 */
#define dbg_assert(test, msg) dbg_assert_imp(__FILE__, __LINE__, test, msg)
void dbg_assert_imp(const char *filename, int line, bool test, const char *msg);

#if defined(CONF_FAMILY_WINDOWS)
std::wstring windows_utf8_to_wide(const char *str);
#endif

int fs_file_time(const char *name, time_t *created, time_t *modified);

/**
 * Checks if a file exists.
 *
 * @ingroup Filesystem
 *
 * @param path the path to check.
 *
 * @return 1 if a file with the given path exists,
 * 0 on failure or if the file does not exist.
 *
 * @remark The strings are treated as zero-terminated strings.
 */
int fs_is_file(const char *path);

#endif // __has_include(<base/system.h>)
#endif // TWBL_SRC_TWBL_TEEWORLDS_BASE_SYSTEM_H
