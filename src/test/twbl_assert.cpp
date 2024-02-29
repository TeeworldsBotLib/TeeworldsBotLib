#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "twbl_assert.h"

void _test_ok()
{
	printf(".");
}

void _test_fail()
{
	fprintf(stderr, "TEST FAILED\n");
	exit(1);
}

int _expect_streq(const char *Actual, const char *Expected, int Line)
{
	if(!strcmp(Actual, Expected))
	{
		_test_ok();
		return 0;
	}
	fprintf(stderr, "assert failed in line %d\n", Line);
	fprintf(stderr, "expected: \"%s\"\n", Expected);
	fprintf(stderr, "     got: \"%s\"\n", Actual);
	_test_fail();
	return 1;
}

int _expect_eq(int Actual, int Expected, int Line)
{
	if(Actual == Expected)
	{
		_test_ok();
		return 0;
	}
	fprintf(stderr, "assert failed in line %d\n", Line);
	fprintf(stderr, "expected: %d\n", Expected);
	fprintf(stderr, "     got: %d\n", Actual);
	_test_fail();
	return 1;
}

int __float_close(float Num1, float Num2, float MaxDiff)
{
	float Diff = std::fabs(Num1 - Num2);
	Num1 = std::fabs(Num1);
	Num2 = std::fabs(Num2);
	float Largest = (Num2 > Num1) ? Num2 : Num1;

	if(Diff <= Largest * MaxDiff)
		return 0;
	return 1;
}

int _expect_float_eq(float Actual, float Expected, int Line)
{
	if(!__float_close(Actual, Expected, 0.00012))
	{
		_test_ok();
		return 0;
	}
	fprintf(stderr, "assert failed in line %d\n", Line);
	fprintf(stderr, "expected: %f\n", Expected);
	fprintf(stderr, "     got: %f\n", Actual);
	_test_fail();
	return 1;
}
