#include <check.h>

#include "../../src/decimal.h"

#define S21_TEST_IS_EQUAL_TRUE(name, a, b) \
  START_TEST(name) {                       \
    int result = s21_is_equal(a, b);       \
    ck_assert_int_eq(result, 1);           \
  }                                        \
  END_TEST

#define S21_TEST_IS_EQUAL_FALSE(name, a, b) \
  START_TEST(name) {                        \
    int result = s21_is_equal(a, b);        \
    ck_assert_int_eq(result, 0);            \
  }                                         \
  END_TEST

static s21_decimal s21_is_equal_test_zero_p_zero_p_a = {{0, 0, 0, 0x00000000}};
static s21_decimal s21_is_equal_test_zero_p_zero_p_b = {{0, 0, 0, 0x00000000}};
S21_TEST_IS_EQUAL_TRUE(s21_is_equal_test_zero_p_zero_p,
                       s21_is_equal_test_zero_p_zero_p_a,
                       s21_is_equal_test_zero_p_zero_p_b)

static s21_decimal s21_is_equal_test_zero_n_zero_n_a = {{0, 0, 0, 0x80000000}};
static s21_decimal s21_is_equal_test_zero_n_zero_n_b = {{0, 0, 0, 0x80000000}};
S21_TEST_IS_EQUAL_TRUE(s21_is_equal_test_zero_n_zero_n,
                       s21_is_equal_test_zero_n_zero_n_a,
                       s21_is_equal_test_zero_n_zero_n_b)

static s21_decimal s21_is_equal_test_zero_p_zero_n_a = {{0, 0, 0, 0x00000000}};
static s21_decimal s21_is_equal_test_zero_p_zero_n_b = {{0, 0, 0, 0x80000000}};
S21_TEST_IS_EQUAL_TRUE(s21_is_equal_test_zero_p_zero_n,
                       s21_is_equal_test_zero_p_zero_n_a,
                       s21_is_equal_test_zero_p_zero_n_b)

static s21_decimal s21_is_equal_test_one_p_one_p_a = {{1, 0, 0, 0x00000000}};
static s21_decimal s21_is_equal_test_one_p_one_p_b = {{1, 0, 0, 0x00000000}};
S21_TEST_IS_EQUAL_TRUE(s21_is_equal_test_one_p_one_p,
                       s21_is_equal_test_one_p_one_p_a,
                       s21_is_equal_test_one_p_one_p_b)

static s21_decimal s21_is_equal_test_one_n_one_n_a = {{1, 0, 0, 0x80000000}};
static s21_decimal s21_is_equal_test_one_n_one_n_b = {{1, 0, 0, 0x80000000}};
S21_TEST_IS_EQUAL_TRUE(s21_is_equal_test_one_n_one_n,
                       s21_is_equal_test_one_n_one_n_a,
                       s21_is_equal_test_one_n_one_n_b)

static s21_decimal s21_is_equal_test_one_p_one_n_a = {{1, 0, 0, 0x00000000}};
static s21_decimal s21_is_equal_test_one_p_one_n_b = {{1, 0, 0, 0x80000000}};
S21_TEST_IS_EQUAL_FALSE(s21_is_equal_test_one_p_one_n,
                        s21_is_equal_test_one_p_one_n_a,
                        s21_is_equal_test_one_p_one_n_b)

static s21_decimal s21_is_equal_test_one_two_a = {{1, 0, 0, 0x00000000}};
static s21_decimal s21_is_equal_test_one_two_b = {{2, 0, 0, 0x00000000}};
S21_TEST_IS_EQUAL_FALSE(s21_is_equal_test_one_two, s21_is_equal_test_one_two_a,
                        s21_is_equal_test_one_two_b)

static s21_decimal s21_is_equal_test_scale1_a = {{10, 0, 0, 0x00010000}};
static s21_decimal s21_is_equal_test_scale2_b = {{100, 0, 0, 0x00020000}};
S21_TEST_IS_EQUAL_TRUE(s21_is_equal_test_scale1_scale2,
                       s21_is_equal_test_scale1_a, s21_is_equal_test_scale2_b)

Suite *s21_is_equal_suite(void) {
  Suite *suite = suite_create("s21_is_equal");

  TCase *tc_equal = tcase_create("Equal");
  tcase_add_test(tc_equal, s21_is_equal_test_zero_p_zero_p);
  tcase_add_test(tc_equal, s21_is_equal_test_zero_n_zero_n);
  tcase_add_test(tc_equal, s21_is_equal_test_zero_p_zero_n);
  tcase_add_test(tc_equal, s21_is_equal_test_one_p_one_p);
  tcase_add_test(tc_equal, s21_is_equal_test_one_n_one_n);
  tcase_add_test(tc_equal, s21_is_equal_test_scale1_scale2);
  suite_add_tcase(suite, tc_equal);

  TCase *tc_not_equal = tcase_create("Not Equal");
  tcase_add_test(tc_not_equal, s21_is_equal_test_one_p_one_n);
  tcase_add_test(tc_not_equal, s21_is_equal_test_one_two);
  suite_add_tcase(suite, tc_not_equal);

  return suite;
}