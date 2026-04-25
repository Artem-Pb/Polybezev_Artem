#include <check.h>
#include <math.h>

#include "../../src/decimal.h"

#define S21_TEST_FROM_FLOAT_SUCCESS(name, src, expected_bits0, expected_bits1, \
                                    expected_bits2, expected_bits3)            \
  START_TEST(name) {                                                           \
    s21_decimal result = {{0}};                                                \
    int code = s21_from_float_to_decimal(src, &result);                        \
    ck_assert_int_eq(code, S21_CONVERSION_OK);                                 \
    ck_assert_int_eq(result.bits[0], expected_bits0);                          \
    ck_assert_int_eq(result.bits[1], expected_bits1);                          \
    ck_assert_int_eq(result.bits[2], expected_bits2);                          \
    ck_assert_int_eq(result.bits[3], expected_bits3);                          \
  }                                                                            \
  END_TEST

#define S21_TEST_FROM_FLOAT_ERROR(name, src)            \
  START_TEST(name) {                                    \
    s21_decimal result = {{0}};                         \
    int code = s21_from_float_to_decimal(src, &result); \
    ck_assert_int_eq(code, S21_CONVERSION_ERROR);       \
    ck_assert_int_eq(result.bits[0], 0);                \
    ck_assert_int_eq(result.bits[1], 0);                \
    ck_assert_int_eq(result.bits[2], 0);                \
    ck_assert_int_eq(result.bits[3], 0);                \
  }                                                     \
  END_TEST

#define S21_TEST_FROM_FLOAT_NULL_DST(name, src)          \
  START_TEST(name) {                                     \
    int code = s21_from_float_to_decimal(src, S21_NULL); \
    ck_assert_int_eq(code, S21_CONVERSION_ERROR);        \
  }                                                      \
  END_TEST

S21_TEST_FROM_FLOAT_SUCCESS(s21_from_float_test_zero_p, 0.0f, 0, 0, 0,
                            0x00000000)

S21_TEST_FROM_FLOAT_SUCCESS(s21_from_float_test_zero_n, -0.0f, 0, 0, 0,
                            -2147483648)

S21_TEST_FROM_FLOAT_SUCCESS(s21_from_float_test_one_p, 1.0f, 1, 0, 0,
                            0x00000000)

S21_TEST_FROM_FLOAT_SUCCESS(s21_from_float_test_one_n, -1.0f, 1, 0, 0,
                            -2147483648)

S21_TEST_FROM_FLOAT_SUCCESS(s21_from_float_test_123_456, 123.456f, 123456, 0, 0,
                            0x00030000)

S21_TEST_FROM_FLOAT_ERROR(s21_from_float_test_tiny, 1e-29f)

S21_TEST_FROM_FLOAT_NULL_DST(s21_from_float_test_null_dst, 1.0f)

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *suite = suite_create("s21_from_float_to_decimal");

  TCase *tc_success = tcase_create("Success");
  tcase_add_test(tc_success, s21_from_float_test_zero_p);
  tcase_add_test(tc_success, s21_from_float_test_zero_n);
  tcase_add_test(tc_success, s21_from_float_test_one_p);
  tcase_add_test(tc_success, s21_from_float_test_one_n);
  tcase_add_test(tc_success, s21_from_float_test_123_456);
  suite_add_tcase(suite, tc_success);

  TCase *tc_error = tcase_create("Error");
  tcase_add_test(tc_error, s21_from_float_test_tiny);
  tcase_add_test(tc_error, s21_from_float_test_null_dst);
  suite_add_tcase(suite, tc_error);

  return suite;
}