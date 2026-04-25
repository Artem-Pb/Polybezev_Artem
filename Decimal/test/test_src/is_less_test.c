#include <check.h>

#include "../../src/decimal.h"

#define S21_TEST_IS_LESS_TRUE(name, a, b) \
  START_TEST(name) {                      \
    int result = s21_is_less(a, b);       \
    ck_assert_int_eq(result, 1);          \
  }                                       \
  END_TEST

#define S21_TEST_IS_LESS_FALSE(name, a, b) \
  START_TEST(name) {                       \
    int result = s21_is_less(a, b);        \
    ck_assert_int_eq(result, 0);           \
  }                                        \
  END_TEST

static s21_decimal s21_is_less_test_zero_one_a = {{0, 0, 0, 0x00000000}};
static s21_decimal s21_is_less_test_zero_one_b = {{1, 0, 0, 0x00000000}};
S21_TEST_IS_LESS_TRUE(s21_is_less_test_zero_one, s21_is_less_test_zero_one_a,
                      s21_is_less_test_zero_one_b)

static s21_decimal s21_is_less_test_one_zero_a = {{1, 0, 0, 0x00000000}};
static s21_decimal s21_is_less_test_one_zero_b = {{0, 0, 0, 0x00000000}};
S21_TEST_IS_LESS_FALSE(s21_is_less_test_one_zero, s21_is_less_test_one_zero_a,
                       s21_is_less_test_one_zero_b)

static s21_decimal s21_is_less_test_minus_one_zero_a = {{1, 0, 0, 0x80000000}};
static s21_decimal s21_is_less_test_minus_one_zero_b = {{0, 0, 0, 0x00000000}};
S21_TEST_IS_LESS_TRUE(s21_is_less_test_minus_one_zero,
                      s21_is_less_test_minus_one_zero_a,
                      s21_is_less_test_minus_one_zero_b)

static s21_decimal s21_is_less_test_zero_minus_one_a = {{0, 0, 0, 0x00000000}};
static s21_decimal s21_is_less_test_zero_minus_one_b = {{1, 0, 0, 0x80000000}};
S21_TEST_IS_LESS_FALSE(s21_is_less_test_zero_minus_one,
                       s21_is_less_test_zero_minus_one_a,
                       s21_is_less_test_zero_minus_one_b)

static s21_decimal s21_is_less_test_one_two_a = {{1, 0, 0, 0x00000000}};
static s21_decimal s21_is_less_test_one_two_b = {{2, 0, 0, 0x00000000}};
S21_TEST_IS_LESS_TRUE(s21_is_less_test_one_two, s21_is_less_test_one_two_a,
                      s21_is_less_test_one_two_b)

static s21_decimal s21_is_less_test_two_one_a = {{2, 0, 0, 0x00000000}};
static s21_decimal s21_is_less_test_two_one_b = {{1, 0, 0, 0x00000000}};
S21_TEST_IS_LESS_FALSE(s21_is_less_test_two_one, s21_is_less_test_two_one_a,
                       s21_is_less_test_two_one_b)

static s21_decimal s21_is_less_test_minus_two_minus_one_a = {
    {2, 0, 0, 0x80000000}};
static s21_decimal s21_is_less_test_minus_two_minus_one_b = {
    {1, 0, 0, 0x80000000}};
S21_TEST_IS_LESS_TRUE(s21_is_less_test_minus_two_minus_one,
                      s21_is_less_test_minus_two_minus_one_a,
                      s21_is_less_test_minus_two_minus_one_b)

static s21_decimal s21_is_less_test_minus_one_minus_two_a = {
    {1, 0, 0, 0x80000000}};
static s21_decimal s21_is_less_test_minus_one_minus_two_b = {
    {2, 0, 0, 0x80000000}};
S21_TEST_IS_LESS_FALSE(s21_is_less_test_minus_one_minus_two,
                       s21_is_less_test_minus_one_minus_two_a,
                       s21_is_less_test_minus_one_minus_two_b)

static s21_decimal s21_is_less_test_scale1_a = {{10, 0, 0, 0x00010000}};  // 1.0
static s21_decimal s21_is_less_test_scale2_b = {{15, 0, 0, 0x00010000}};  // 1.5
S21_TEST_IS_LESS_TRUE(s21_is_less_test_scale1_scale2, s21_is_less_test_scale1_a,
                      s21_is_less_test_scale2_b)

static s21_decimal s21_is_less_test_zero_zero_a = {{0, 0, 0, 0x00000000}};
static s21_decimal s21_is_less_test_zero_zero_b = {{0, 0, 0, 0x00000000}};
S21_TEST_IS_LESS_FALSE(s21_is_less_test_zero_zero, s21_is_less_test_zero_zero_a,
                       s21_is_less_test_zero_zero_b)

static s21_decimal s21_is_less_test_minus_zero_minus_zero_a = {
    {0, 0, 0, 0x80000000}};
static s21_decimal s21_is_less_test_minus_zero_minus_zero_b = {
    {0, 0, 0, 0x80000000}};
S21_TEST_IS_LESS_FALSE(s21_is_less_test_minus_zero_minus_zero,
                       s21_is_less_test_minus_zero_minus_zero_a,
                       s21_is_less_test_minus_zero_minus_zero_b)

Suite *s21_is_less_suite(void) {
  Suite *suite = suite_create("s21_is_less");

  TCase *tc_less = tcase_create("Less");
  tcase_add_test(tc_less, s21_is_less_test_zero_one);
  tcase_add_test(tc_less, s21_is_less_test_minus_one_zero);
  tcase_add_test(tc_less, s21_is_less_test_one_two);
  tcase_add_test(tc_less, s21_is_less_test_minus_two_minus_one);
  tcase_add_test(tc_less, s21_is_less_test_scale1_scale2);
  suite_add_tcase(suite, tc_less);

  TCase *tc_not_less = tcase_create("Not Less");
  tcase_add_test(tc_not_less, s21_is_less_test_one_zero);
  tcase_add_test(tc_not_less, s21_is_less_test_zero_minus_one);
  tcase_add_test(tc_not_less, s21_is_less_test_two_one);
  tcase_add_test(tc_not_less, s21_is_less_test_minus_one_minus_two);
  tcase_add_test(tc_not_less, s21_is_less_test_zero_zero);
  tcase_add_test(tc_not_less, s21_is_less_test_minus_zero_minus_zero);
  suite_add_tcase(suite, tc_not_less);

  return suite;
}