#include <check.h>
#include <float.h>
#include <math.h>

#include "../../src/decimal.h"

#define S21_TEST_TO_FLOAT_SUCCESS(name, src_bits0, src_bits1, src_bits2, \
                                  src_bits3, expected, tolerance)        \
  START_TEST(name) {                                                     \
    s21_decimal src = {{src_bits0, src_bits1, src_bits2, src_bits3}};    \
    float result;                                                        \
    int code = s21_from_decimal_to_float(src, &result);                  \
    ck_assert_int_eq(code, S21_CONVERSION_OK);                           \
    ck_assert_float_eq_tol(result, expected, tolerance);                 \
  }                                                                      \
  END_TEST

#define S21_TEST_TO_FLOAT_ERROR(name, src_bits0, src_bits1, src_bits2, \
                                src_bits3)                             \
  START_TEST(name) {                                                   \
    s21_decimal src = {{src_bits0, src_bits1, src_bits2, src_bits3}};  \
    float result;                                                      \
    int code = s21_from_decimal_to_float(src, &result);                \
    ck_assert_int_eq(code, S21_CONVERSION_ERROR);                      \
  }                                                                    \
  END_TEST

#define S21_TEST_TO_FLOAT_NULL_DST(name, src_bits0, src_bits1, src_bits2, \
                                   src_bits3)                             \
  START_TEST(name) {                                                      \
    s21_decimal src = {{src_bits0, src_bits1, src_bits2, src_bits3}};     \
    int code = s21_from_decimal_to_float(src, S21_NULL);                  \
    ck_assert_int_eq(code, S21_CONVERSION_ERROR);                         \
  }                                                                       \
  END_TEST

S21_TEST_TO_FLOAT_SUCCESS(s21_to_float_test_zero_p, 0, 0, 0, 0x00000000, 0.0f,
                          1e-6f)

S21_TEST_TO_FLOAT_SUCCESS(s21_to_float_test_zero_n, 0, 0, 0, 0x80000000, -0.0f,
                          1e-6f)

S21_TEST_TO_FLOAT_SUCCESS(s21_to_float_test_one_p, 1, 0, 0, 0x00000000, 1.0f,
                          1e-6f)

S21_TEST_TO_FLOAT_SUCCESS(s21_to_float_test_one_n, 1, 0, 0, 0x80000000, -1.0f,
                          1e-6f)

S21_TEST_TO_FLOAT_SUCCESS(s21_to_float_test_123_456, 123456, 0, 0, 0x00030000,
                          123.456f, 1e-3f)

S21_TEST_TO_FLOAT_NULL_DST(s21_to_float_test_null_dst, 1, 0, 0, 0x00000000)

Suite *s21_from_decimal_to_float_suite(void) {
  Suite *suite = suite_create("s21_from_decimal_to_float");

  TCase *tc_success = tcase_create("Success");
  tcase_add_test(tc_success, s21_to_float_test_zero_p);
  tcase_add_test(tc_success, s21_to_float_test_zero_n);
  tcase_add_test(tc_success, s21_to_float_test_one_p);
  tcase_add_test(tc_success, s21_to_float_test_one_n);
  tcase_add_test(tc_success, s21_to_float_test_123_456);
  suite_add_tcase(suite, tc_success);

  TCase *tc_error = tcase_create("Error");
  tcase_add_test(tc_error, s21_to_float_test_null_dst);
  suite_add_tcase(suite, tc_error);

  return suite;
}