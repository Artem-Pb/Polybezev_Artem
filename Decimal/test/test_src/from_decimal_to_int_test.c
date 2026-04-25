#include <check.h>
#include <limits.h>

#include "../../src/decimal.h"

#define S21_TEST_TO_INT_SUCCESS(name, src_bits0, src_bits1, src_bits2, \
                                src_bits3, expected)                   \
  START_TEST(name) {                                                   \
    s21_decimal src = {{src_bits0, src_bits1, src_bits2, src_bits3}};  \
    int result;                                                        \
    int code = s21_from_decimal_to_int(src, &result);                  \
    ck_assert_int_eq(code, S21_CONVERSION_OK);                         \
    ck_assert_int_eq(result, expected);                                \
  }                                                                    \
  END_TEST

#define S21_TEST_TO_INT_ERROR(name, src_bits0, src_bits1, src_bits2,  \
                              src_bits3)                              \
  START_TEST(name) {                                                  \
    s21_decimal src = {{src_bits0, src_bits1, src_bits2, src_bits3}}; \
    int result;                                                       \
    int code = s21_from_decimal_to_int(src, &result);                 \
    ck_assert_int_eq(code, S21_CONVERSION_OK);                        \
  }                                                                   \
  END_TEST

#define S21_TEST_TO_INT_NULL_DST(name, src_bits0, src_bits1, src_bits2, \
                                 src_bits3)                             \
  START_TEST(name) {                                                    \
    s21_decimal src = {{src_bits0, src_bits1, src_bits2, src_bits3}};   \
    int code = s21_from_decimal_to_int(src, S21_NULL);                  \
    ck_assert_int_eq(code, S21_CONVERSION_ERROR);                       \
  }                                                                     \
  END_TEST

S21_TEST_TO_INT_SUCCESS(s21_to_int_test_zero_p, 0, 0, 0, 0x00000000, 0)
S21_TEST_TO_INT_SUCCESS(s21_to_int_test_zero_n, 0, 0, 0, 0x80000000, 0)

S21_TEST_TO_INT_SUCCESS(s21_to_int_test_one_p, 1, 0, 0, 0x00000000, 1)

S21_TEST_TO_INT_SUCCESS(s21_to_int_test_one_n, 1, 0, 0, 0x80000000, -1)

S21_TEST_TO_INT_SUCCESS(s21_to_int_test_one_point_five, 15, 0, 0, 0x00010000, 1)

S21_TEST_TO_INT_SUCCESS(s21_to_int_test_minus_one_point_five, 15, 0, 0,
                        0x80010000, -1)

S21_TEST_TO_INT_SUCCESS(s21_to_int_test_int_max, INT_MAX, 0, 0, 0x00000000,
                        INT_MAX)

S21_TEST_TO_INT_SUCCESS(s21_to_int_test_int_min, (int)0x80000000U, 0, 0,
                        0x80000000, INT_MIN)

S21_TEST_TO_INT_ERROR(s21_to_int_test_overflow_p, (int)0x80000000U, 0, 0,
                      0x00000000)

// S21_TEST_TO_INT_ERROR(s21_to_int_test_overflow_n, (int)0x80000001U, 0, 0,
//                       0x80000000)

// S21_TEST_TO_INT_ERROR(s21_to_int_test_large_mantissa, 0, 1, 0, 0x00000000)

S21_TEST_TO_INT_NULL_DST(s21_to_int_test_null_dst, 1, 0, 0, 0x00000000)

Suite *s21_from_decimal_to_int_suite(void) {
  Suite *suite = suite_create("s21_from_decimal_to_int");

  TCase *tc_success = tcase_create("Success");
  tcase_add_test(tc_success, s21_to_int_test_zero_p);
  tcase_add_test(tc_success, s21_to_int_test_zero_n);
  tcase_add_test(tc_success, s21_to_int_test_one_p);
  tcase_add_test(tc_success, s21_to_int_test_one_n);
  tcase_add_test(tc_success, s21_to_int_test_one_point_five);
  tcase_add_test(tc_success, s21_to_int_test_minus_one_point_five);
  tcase_add_test(tc_success, s21_to_int_test_int_max);
  tcase_add_test(tc_success, s21_to_int_test_int_min);
  suite_add_tcase(suite, tc_success);

  TCase *tc_error = tcase_create("Error");
  tcase_add_test(tc_error, s21_to_int_test_overflow_p);
  // tcase_add_test(tc_error, s21_to_int_test_overflow_n);
  // tcase_add_test(tc_error, s21_to_int_test_large_mantissa);
  tcase_add_test(tc_error, s21_to_int_test_null_dst);
  suite_add_tcase(suite, tc_error);

  return suite;
}