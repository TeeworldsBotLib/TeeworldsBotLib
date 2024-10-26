#if __has_include(<base/system.h>)
// TODO: find a better conditon than having the file base/system.h
//       this is a polyfill of system.cpp when compiled as external library
//       so standalone tests can use things like dbg_msg()
#else

#include <cstdarg>
#include <cstdio>
#include <cstring>

#include "system.h"

int str_length(const char *str)
{
	return (int)strlen(str);
}

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#endif
void str_timestamp_ex(time_t time_data, char *buffer, int buffer_size, const char *format)
{
	struct tm *time_info;
	dbg_assert(buffer_size > 0, "buffer_size invalid");
	time_info = localtime(&time_data);
	strftime(buffer, buffer_size, format, time_info);
	buffer[buffer_size - 1] = 0; /* assure null termination */
}

void str_timestamp_format(char *buffer, int buffer_size, const char *format)
{
	time_t time_data;
	time(&time_data);
	str_timestamp_ex(time_data, buffer, buffer_size, format);
}

void str_timestamp(char *buffer, int buffer_size)
{
	str_timestamp_format(buffer, buffer_size, FORMAT_NOSPACE);
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

void str_format(char *buffer, int buffer_size, const char *format, ...)
{
	va_list ap;
	dbg_assert(buffer_size > 0, "buffer_size invalid");
	va_start(ap, format);

#if defined(CONF_FAMILY_WINDOWS) && !defined(__GNUC__)
	_vsprintf_p(buffer, buffer_size, format, ap);
#else
	vsnprintf(buffer, buffer_size, format, ap);
#endif

	va_end(ap);

	buffer[buffer_size - 1] = 0; /* assure null termination */
}

void str_append(char *dst, const char *src, int dst_size)
{
	int s;
	int i = 0;
	dbg_assert(dst_size > 0, "dst_size invalid");
	s = str_length(dst);
	while(s < dst_size)
	{
		dst[s] = src[i];
		if(!src[i]) /* check for null termination */
			break;
		s++;
		i++;
	}

	dst[dst_size - 1] = 0; /* assure null termination */
}

void str_copy(char *dst, const char *src, int dst_size)
{
	dbg_assert(dst_size > 0, "dst_size invalid");
	dst[0] = '\0';
	strncat(dst, src, dst_size - 1);
}

void str_truncate(char *dst, int dst_size, const char *src, int truncation_len)
{
	int size = dst_size;
	if(truncation_len < size)
	{
		size = truncation_len + 1;
	}
	str_copy(dst, src, size);
}

void dbg_break()
{
#ifdef __GNUC__
	__builtin_trap();
#else
	abort();
#endif
}

void dbg_msg(const char *sys, const char *fmt, ...)
{
	va_list args;
	char str[1024 * 4];
	char *msg;
	int i, len;

	char timestr[80];
	str_timestamp_format(timestr, sizeof(timestr), FORMAT_SPACE);

	str_format(str, sizeof(str), "[%s][%s]: ", timestr, sys);

	len = str_length(str);
	msg = (char *)str + len;

	va_start(args, fmt);
#if defined(CONF_FAMILY_WINDOWS) && !defined(__GNUC__)
	_vsprintf_p(msg, sizeof(str) - len, fmt, args);
#else
	vsnprintf(msg, sizeof(str) - len, fmt, args);
#endif
	va_end(args);

	puts(str);
}

void dbg_assert_imp(const char *filename, int line, bool test, const char *msg)
{
	if(!test)
	{
		fprintf(stderr, "assert: %s(%d): %s\n", filename, line, msg);
		dbg_break();
	}
}

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
static inline time_t filetime_to_unixtime(LPFILETIME filetime)
{
	time_t t;
	ULARGE_INTEGER li;
	li.LowPart = filetime->dwLowDateTime;
	li.HighPart = filetime->dwHighDateTime;

	li.QuadPart /= 10000000; // 100ns to 1s
	li.QuadPart -= 11644473600LL; // Windows epoch is in the past

	t = li.QuadPart;
	return t == (time_t)li.QuadPart ? t : (time_t)-1;
}

std::wstring windows_utf8_to_wide(const char *str)
{
	const int orig_length = str_length(str);
	if(orig_length == 0)
		return L"";
	const int size_needed = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, orig_length, nullptr, 0);
	dbg_assert(size_needed > 0, "Invalid UTF-8 passed to windows_utf8_to_wide");
	std::wstring wide_string(size_needed, L'\0');
	dbg_assert(MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, orig_length, wide_string.data(), size_needed) == size_needed, "MultiByteToWideChar failure");
	return wide_string;
}
#endif

int fs_file_time(const char *name, time_t *created, time_t *modified)
{
#if defined(CONF_FAMILY_WINDOWS)
	WIN32_FIND_DATAW finddata;
	const std::wstring wide_name = windows_utf8_to_wide(name);
	HANDLE handle = FindFirstFileW(wide_name.c_str(), &finddata);
	if(handle == INVALID_HANDLE_VALUE)
		return 1;

	*created = filetime_to_unixtime(&finddata.ftCreationTime);
	*modified = filetime_to_unixtime(&finddata.ftLastWriteTime);
	FindClose(handle);
#elif defined(CONF_FAMILY_UNIX)
	struct stat sb;
	if(stat(name, &sb))
		return 1;

	*created = sb.st_ctime;
	*modified = sb.st_mtime;
#else
#error not implemented
#endif

	return 0;
}

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
int fs_is_file(const char *path)
{
#if defined(CONF_FAMILY_WINDOWS)
	const std::wstring wide_path = windows_utf8_to_wide(path);
	DWORD attributes = GetFileAttributesW(wide_path.c_str());
	return attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY) ? 1 : 0;
#else
	struct stat sb;
	if(stat(path, &sb) == -1)
		return 0;
	return S_ISREG(sb.st_mode) ? 1 : 0;
#endif
}

#endif // __has_include(<base/system.h>)
