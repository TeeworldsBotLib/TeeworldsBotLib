#ifndef TWBL_SRC_TWBL_TEEWORLDS_BASE_SYSTEM_H
#define TWBL_SRC_TWBL_TEEWORLDS_BASE_SYSTEM_H

#include <cstdint>
#if __has_include(<base/system.h>)
#elif __has_include(<base/str.h>)
#include <base/dbg.h>
#include <base/fs.h>
#include <base/io.h>
#include <base/log.h>
#include <base/math.h>
#include <base/mem.h>
#include <base/net.h>
#include <base/os.h>
#include <base/str.h>
#include <base/vmath.h>
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

void str_timestamp(char *buffer, int buffer_size);
void str_timestamp_format(char *buffer, int buffer_size, const char *format)
	GNUC_ATTRIBUTE((format(strftime, 3, 0)));
void str_timestamp_ex(time_t time, char *buffer, int buffer_size, const char *format)
	GNUC_ATTRIBUTE((format(strftime, 4, 0)));

void str_format(char *buffer, int buffer_size, const char *format, ...)
	GNUC_ATTRIBUTE((format(printf, 3, 4)));

void str_append(char *dst, const char *src, int dst_size);

template<int N>
void str_append(char (&dst)[N], const char *src)
{
	str_append(dst, src, N);
}

void str_copy(char *dst, const char *src, int dst_size);

template<int N>
void str_copy(char (&dst)[N], const char *src)
{
	str_copy(dst, src, N);
}

void str_truncate(char *dst, int dst_size, const char *src, int truncation_len);

#if defined(CONF_FAMILY_WINDOWS)
std::wstring windows_utf8_to_wide(const char *str);
#endif

int fs_file_time(const char *name, time_t *created, time_t *modified);

int fs_is_file(const char *path);

bool str_isnum(char c);
int str_isallnum_hex(const char *str);

int str_toint(const char *str);
bool str_toint(const char *str, int *out);
int str_toint_base(const char *str, int base);
unsigned long str_toulong_base(const char *str, int base);
int64_t str_toint64_base(const char *str, int base = 10);
float str_tofloat(const char *str);
bool str_tofloat(const char *str, float *out);

#endif // __has_include(<base/system.h>)
#endif // TWBL_SRC_TWBL_TEEWORLDS_BASE_SYSTEM_H
