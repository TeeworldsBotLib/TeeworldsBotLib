#include <cstdio>

#include "setup.h"

void InitTest(const char *pName)
{
#ifndef TWBL_DEBUG
#define TEST_WARNING "tests will fail if not compiled with -DTWBL_DEBUG=ON"
#pragma message(TEST_WARNING)
	puts(TEST_WARNING);
#endif
	printf("[TEST] running test %s\n", pName);
}
