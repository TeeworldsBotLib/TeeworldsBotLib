#ifndef TWBL_SRC_SHARED_DETECT_H
#define TWBL_SRC_SHARED_DETECT_H

#if __has_include(<base/detect.h>)
#include <base/detect.h>
#else

/* windows Family */
#if defined(WIN64) || defined(_WIN64)
#define CONF_FAMILY_WINDOWS 1
#elif defined(WIN32) || defined(_WIN32) || defined(__CYGWIN32__) || defined(__MINGW32__)
#define CONF_FAMILY_WINDOWS 1
#endif

/* unix family */
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#define CONF_FAMILY_UNIX 1
#define CONF_PLATFORM_FREEBSD 1
#endif

#if (defined(__LINUX__) || defined(__linux__) || defined(CONF_WEBASM)) && !defined(__ANDROID__)
#define CONF_FAMILY_UNIX 1
#define CONF_PLATFORM_LINUX 1
#endif

#if defined(MACOSX) || defined(__APPLE__) || defined(__DARWIN__)
#define CONF_FAMILY_UNIX 1
#define CONF_PLATFORM_MACOS 1
#endif

#endif // __has_include(<base/detect.h>)

#endif
