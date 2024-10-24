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

#ifdef __GNUC__
#define GNUC_ATTRIBUTE(x) __attribute__(x)
#else
#define GNUC_ATTRIBUTE(x)
#endif

#define FORMAT_TIME "%H:%M:%S"
#define FORMAT_SPACE "%Y-%m-%d %H:%M:%S"
#define FORMAT_NOSPACE "%Y-%m-%d_%H-%M-%S"

int str_length(const char *str);

/*
	Function: str_timestamp
		Copies a time stamp in the format year-month-day_hour-minute-second to the string.

	Parameters:
		buffer - Pointer to a buffer that shall receive the time stamp string.
		buffer_size - Size of the buffer.

	Remarks:
		- Guarantees that buffer string will contain zero-termination.
*/
void str_timestamp(char *buffer, int buffer_size);
void str_timestamp_format(char *buffer, int buffer_size, const char *format)
	GNUC_ATTRIBUTE((format(strftime, 3, 0)));
void str_timestamp_ex(time_t time, char *buffer, int buffer_size, const char *format)
	GNUC_ATTRIBUTE((format(strftime, 4, 0)));

/*
	Function: str_format
		Performs printf formatting into a buffer.

	Parameters:
		buffer - Pointer to the buffer to receive the formatted string.
		buffer_size - Size of the buffer.
		format - printf formatting string.
		... - Parameters for the formatting.

	Remarks:
		- See the C manual for syntax for the printf formatting string.
		- The strings are treated as zero-termineted strings.
		- Guarantees that dst string will contain zero-termination.
*/
void str_format(char *buffer, int buffer_size, const char *format, ...)
	GNUC_ATTRIBUTE((format(printf, 3, 4)));

/*
	Function: dbg_msg

	Prints a debug message.

	Parameters:
		sys - A string that describes what system the message belongs to
		fmt - A printf styled format string.

	See Also:
		<dbg_assert>
*/
void dbg_msg(const char *sys, const char *fmt, ...)
	GNUC_ATTRIBUTE((format(printf, 2, 3)));

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
