#include <check.h>
#include <limits.h>

#include "../../src/decimal.h"

#define S21_TEST_FROM_INT_SUCCESS(name, src, expected_bits0, expected_bits1, \
                                  expected_bits2, expected_bits3)            \
  START_TEST(name) {                                                         \
    s21_decimal result = {{0}};                                              \
    int code = s21_from_int_to_decimal(src, &result);                        \
    ck_assert_int_eq(code, S21_CONVERSION_OK);                               \
    ck_assert_int_eq(result.bits[0], expected_bits0);                        \
    ck_assert_int_eq(result.bits[1], expected_bits1);                        \
    ck_assert_int_eq(result.bits[2], expected_bits2);                        \
    ck_assert_int_eq(result.bits[3], expected_bits3);                        \
  }                                                                          \
  END_TEST

#define S21_TEST_FROM_INT_ERROR(name, src)            \
  START_TEST(name) {                                  \
    s21_decimal result = {{0}};                       \
    int code = s21_from_int_to_decimal(src, &result); \
    ck_assert_int_eq(code, S21_CONVERSION_OK);        \
  }                                                   \
  END_TEST

S21_TEST_FROM_INT_SUCCESS(s21_from_int_test_zero, 0, 0, 0, 0, 0x00000000)

S21_TEST_FROM_INT_SUCCESS(s21_from_int_test_one, 1, 1, 0, 0, 0x00000000)

S21_TEST_FROM_INT_SUCCESS(s21_from_int_test_minus_one, -1, 1, 0, 0, -2147483648)

S21_TEST_FROM_INT_SUCCESS(s21_from_int_test_int_max, INT_MAX, INT_MAX, 0, 0,
                          0x00000000)

S21_TEST_FROM_INT_SUCCESS(s21_from_int_test_int_min, INT_MIN, (int)0x80000000U,
                          0, 0, -2147483648)

S21_TEST_FROM_INT_ERROR(s21_from_int_test_null_dst, 5)

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *suite = suite_create("s21_from_int_to_decimal");

  TCase *tc_success = tcase_create("Success");
  tcase_add_test(tc_success, s21_from_int_test_zero);
  tcase_add_test(tc_success, s21_from_int_test_one);
  tcase_add_test(tc_success, s21_from_int_test_minus_one);
  tcase_add_test(tc_success, s21_from_int_test_int_max);
  tcase_add_test(tc_success, s21_from_int_test_int_min);
  suite_add_tcase(suite, tc_success);

  TCase *tc_error = tcase_create("Error");
  tcase_add_test(tc_error, s21_from_int_test_null_dst);
  suite_add_tcase(suite, tc_error);

  return suite;
}