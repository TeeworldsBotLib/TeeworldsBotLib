#ifndef TWBL_SRC_TESTS_ASSERT_H
#define TWBL_SRC_TESTS_ASSERT_H

void _test_ok();
void _test_fail();
int _expect_streq(const char *Actual, const char *Expected, int Line);
int _expect_eq(int Actual, int Expected, int Line);
int _expect_float_eq(float Actual, float Expected, int Line);

#define EXPECT_STREQ(actual, expected) _expect_streq(actual, expected, __LINE__);
#define EXPECT_EQ(actual, expected) _expect_eq(actual, expected, __LINE__);
#define EXPECT_FLOAT_EQ(actual, expected) _expect_float_eq(actual, expected, __LINE__);

#endif
