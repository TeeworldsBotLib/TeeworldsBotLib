#include <cstdarg>
#include <twbl/teeworlds/base/system.h>

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

#define dbg_assert(test, msg) dbg_assert_imp(__FILE__, __LINE__, test, msg)
void dbg_assert_imp(const char *filename, int line, bool test, const char *msg);
