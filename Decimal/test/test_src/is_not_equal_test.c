#include <check.h>

#include "../../src/decimal.h"

#define S21_TEST_IS_NOT_EQUAL_TRUE(name, a, b) \
  START_TEST(name) {                           \
    int result = s21_is_not_equal(a, b);       \
    ck_assert_int_eq(result, 1);               \
  }                                            \
  END_TEST

#define S21_TEST_IS_NOT_EQUAL_FALSE(name, a, b) \
  START_TEST(name) {                            \
    int result = s21_is_not_equal(a, b);        \
    ck_assert_int_eq(result, 0);                \
  }                                             \
  END_TEST

static s21_decimal s21_is_not_equal_test_one_zero_a = {{1, 0, 0, 0x00000000}};
static s21_decimal s21_is_not_equal_test_one_zero_b = {{0, 0, 0, 0x00000000}};
S21_TEST_IS_NOT_EQUAL_TRUE(s21_is_not_equal_test_one_zero,
                           s21_is_not_equal_test_one_zero_a,
                           s21_is_not_equal_test_one_zero_b)

static s21_decimal s21_is_not_equal_test_zero_one_a = {{0, 0, 0, 0x00000000}};
static s21_decimal s21_is_not_equal_test_zero_one_b = {{1, 0, 0, 0x00000000}};
S21_TEST_IS_NOT_EQUAL_TRUE(s21_is_not_equal_test_zero_one,
                           s21_is_not_equal_test_zero_one_a,
                           s21_is_not_equal_test_zero_one_b)

static s21_decimal s21_is_not_equal_test_one_one_a = {{1, 0, 0, 0x00000000}};
static s21_decimal s21_is_not_equal_test_one_one_b = {{1, 0, 0, 0x00000000}};
S21_TEST_IS_NOT_EQUAL_FALSE(s21_is_not_equal_test_one_one,
                            s21_is_not_equal_test_one_one_a,
                            s21_is_not_equal_test_one_one_b)

static s21_decimal s21_is_not_equal_test_zero_zero_a = {{0, 0, 0, 0x00000000}};
static s21_decimal s21_is_not_equal_test_zero_zero_b = {{0, 0, 0, 0x00000000}};
S21_TEST_IS_NOT_EQUAL_FALSE(s21_is_not_equal_test_zero_zero,
                            s21_is_not_equal_test_zero_zero_a,
                            s21_is_not_equal_test_zero_zero_b)

static s21_decimal s21_is_not_equal_test_minus_zero_minus_zero_a = {
    {0, 0, 0, 0x80000000}};
static s21_decimal s21_is_not_equal_test_minus_zero_minus_zero_b = {
    {0, 0, 0, 0x80000000}};
S21_TEST_IS_NOT_EQUAL_FALSE(s21_is_not_equal_test_minus_zero_minus_zero,
                            s21_is_not_equal_test_minus_zero_minus_zero_a,
                            s21_is_not_equal_test_minus_zero_minus_zero_b)

static s21_decimal s21_is_not_equal_test_zero_minus_zero_a = {
    {0, 0, 0, 0x00000000}};
static s21_decimal s21_is_not_equal_test_zero_minus_zero_b = {
    {0, 0, 0, 0x80000000}};
S21_TEST_IS_NOT_EQUAL_FALSE(s21_is_not_equal_test_zero_minus_zero,
                            s21_is_not_equal_test_zero_minus_zero_a,
                            s21_is_not_equal_test_zero_minus_zero_b)

static s21_decimal s21_is_not_equal_test_scale1_a = {{10, 0, 0, 0x00010000}};
static s21_decimal s21_is_not_equal_test_scale2_b = {{15, 0, 0, 0x00010000}};
S21_TEST_IS_NOT_EQUAL_TRUE(s21_is_not_equal_test_scale1_scale2,
                           s21_is_not_equal_test_scale1_a,
                           s21_is_not_equal_test_scale2_b)

Suite *s21_is_not_equal_suite(void) {
  Suite *suite = suite_create("s21_is_not_equal");

  TCase *tc_not_equal = tcase_create("Not Equal");
  tcase_add_test(tc_not_equal, s21_is_not_equal_test_one_zero);
  tcase_add_test(tc_not_equal, s21_is_not_equal_test_zero_one);
  tcase_add_test(tc_not_equal, s21_is_not_equal_test_scale1_scale2);
  suite_add_tcase(suite, tc_not_equal);

  TCase *tc_equal = tcase_create("Equal");
  tcase_add_test(tc_equal, s21_is_not_equal_test_one_one);
  tcase_add_test(tc_equal, s21_is_not_equal_test_zero_zero);
  tcase_add_test(tc_equal, s21_is_not_equal_test_minus_zero_minus_zero);
  tcase_add_test(tc_equal, s21_is_not_equal_test_zero_minus_zero);
  suite_add_tcase(suite, tc_equal);

  return suite;
}