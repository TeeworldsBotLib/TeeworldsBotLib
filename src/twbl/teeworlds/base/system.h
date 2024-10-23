#ifndef TWBL_SRC_SHARED_SYSTEM_H
#define TWBL_SRC_SHARED_SYSTEM_H

#include <cstdio>
#include <cstring>
#if __has_include(<base/system.h>)
#include <base/system.h>
#else

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

int str_length(const char *str)
{
	return (int)strlen(str);
}

void dbg_break()
{
#ifdef __GNUC__
	__builtin_trap();
#else
	abort();
#endif
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

#endif

#endif
