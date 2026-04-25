#include <check.h>

#include "../../src/decimal.h"

// Макросы для удобства
#define S21_TEST_SUB_SUCCESS(name, dec1_var, dec2_var, expected_var) \
  START_TEST(name) {                                                 \
    s21_decimal dec1 = dec1_var;                                     \
    s21_decimal dec2 = dec2_var;                                     \
    s21_decimal expected = expected_var;                             \
    s21_decimal result = {{0}};                                      \
    int code = s21_sub(dec1, dec2, &result);                         \
    ck_assert_int_eq(code, S21_ARITHMETIC_OK);                       \
    for (int i = 0; i < 4; i++) {                                    \
      ck_assert_uint_eq(result.bits[i], expected.bits[i]);           \
    }                                                                \
  }                                                                  \
  END_TEST

#define S21_TEST_SUB_OVERFLOW(name, dec1_var, dec2_var) \
  START_TEST(name) {                                    \
    s21_decimal dec1 = dec1_var;                        \
    s21_decimal dec2 = dec2_var;                        \
    s21_decimal result = {{0}};                         \
    int code = s21_sub(dec1, dec2, &result);            \
    ck_assert(code == S21_ARITHMETIC_OVERFLOW ||        \
              code == S21_ARITHMETIC_UNDERFLOW);        \
  }                                                     \
  END_TEST

#define S21_TEST_SUB_NULL(name, dec1_var, dec2_var)  \
  START_TEST(name) {                                 \
    s21_decimal dec1 = dec1_var;                     \
    s21_decimal dec2 = dec2_var;                     \
    int code = s21_sub(dec1, dec2, S21_NULL);        \
    ck_assert_int_eq(code, S21_ARITHMETIC_OVERFLOW); \
  }                                                  \
  END_TEST

// --------------------- Тесты ---------------------

// Basic positive subtraction
static s21_decimal basic1_a = {{5, 0, 0, 0}};
static s21_decimal basic1_b = {{3, 0, 0, 0}};
static s21_decimal basic1_res = {{2, 0, 0, 0}};
S21_TEST_SUB_SUCCESS(test_basic1, basic1_a, basic1_b, basic1_res)

static s21_decimal basic2_a = {{100, 0, 0, 0x00020000}};
static s21_decimal basic2_b = {{25, 0, 0, 0x00020000}};
static s21_decimal basic2_res = {{75, 0, 0, 0x00020000}};
S21_TEST_SUB_SUCCESS(test_basic2, basic2_a, basic2_b, basic2_res)

// Negative numbers
static s21_decimal neg1_a = {{10, 0, 0, 0x80000000}};
static s21_decimal neg1_b = {{5, 0, 0, 0}};
static s21_decimal neg1_res = {{15, 0, 0, 0x80000000}};
S21_TEST_SUB_SUCCESS(test_negative1, neg1_a, neg1_b, neg1_res)

static s21_decimal neg2_a = {{20, 0, 0, 0}};
static s21_decimal neg2_b = {{30, 0, 0, 0x80000000}};
static s21_decimal neg2_res = {{50, 0, 0, 0}};
S21_TEST_SUB_SUCCESS(test_negative2, neg2_a, neg2_b, neg2_res)

// Zero operands
static s21_decimal zero1_a = {{123, 0, 0, 0x00020000}};
static s21_decimal zero1_b = {{0, 0, 0, 0}};
static s21_decimal zero1_res = {{123, 0, 0, 0x00020000}};
S21_TEST_SUB_SUCCESS(test_zero1, zero1_a, zero1_b, zero1_res)

static s21_decimal zero2_a = {{0, 0, 0, 0}};
static s21_decimal zero2_b = {{456, 0, 0, 0x80030000}};
static s21_decimal zero2_res = {{456, 0, 0, 0x00030000}};
S21_TEST_SUB_SUCCESS(test_zero2, zero2_a, zero2_b, zero2_res)

// Equal numbers, same sign -> result zero
static s21_decimal eq_a = {{100, 0, 0, 0}};
static s21_decimal eq_b = {{100, 0, 0, 0}};
static s21_decimal eq_res = {{0, 0, 0, 0}};
S21_TEST_SUB_SUCCESS(test_equal_same_sign, eq_a, eq_b, eq_res)

// cmp < 0, same sign
static s21_decimal cmp_lt_a = {{5, 0, 0, 0}};
static s21_decimal cmp_lt_b = {{10, 0, 0, 0}};
static s21_decimal cmp_lt_res = {{5, 0, 0, 0x80000000}};
S21_TEST_SUB_SUCCESS(test_cmp_less, cmp_lt_a, cmp_lt_b, cmp_lt_res)

// Overflow / underflow examples
static s21_decimal over_a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
static s21_decimal over_b = {{1, 0, 0, 0x80000000}};
S21_TEST_SUB_OVERFLOW(test_overflow, over_a, over_b)

// Add mantissa overflow (diff sign)
static s21_decimal add_ov_a = {
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
static s21_decimal add_ov_b = {{1, 0, 0, 0x80000000}};
S21_TEST_SUB_OVERFLOW(test_add_overflow_sign_diff, add_ov_a, add_ov_b)

// NULL pointer
static s21_decimal null_a = {{5, 0, 0, 0}};
static s21_decimal null_b = {{3, 0, 0, 0}};
S21_TEST_SUB_NULL(test_null_ptr, null_a, null_b)

// Scale / normalization
static s21_decimal scale_a = {{1234, 0, 0, 0x00020000}};
static s21_decimal scale_b = {{56, 0, 0, 0x00040000}};
static s21_decimal scale_res = {{123344, 0, 0, 0x00040000}};
S21_TEST_SUB_SUCCESS(test_scale, scale_a, scale_b, scale_res)

// Precision / rounding
static s21_decimal prec_a = {{10001, 0, 0, 0x00040000}};
static s21_decimal prec_b = {{1, 0, 0, 0x00040000}};
static s21_decimal prec_res = {{10000, 0, 0, 0x00040000}};
S21_TEST_SUB_SUCCESS(test_precision, prec_a, prec_b, prec_res)

// --------------------- Suite ---------------------

Suite *s21_sub_suite(void) {
  Suite *suite = suite_create("s21_sub");

  TCase *basic_case = tcase_create("Basic");
  tcase_add_test(basic_case, test_basic1);
  tcase_add_test(basic_case, test_basic2);
  suite_add_tcase(suite, basic_case);

  TCase *negative_case = tcase_create("Negative");
  tcase_add_test(negative_case, test_negative1);
  tcase_add_test(negative_case, test_negative2);
  tcase_add_test(negative_case, test_cmp_less);
  suite_add_tcase(suite, negative_case);

  TCase *zero_case = tcase_create("Zero");
  tcase_add_test(zero_case, test_zero1);
  tcase_add_test(zero_case, test_zero2);
  suite_add_tcase(suite, zero_case);

  TCase *equal_case = tcase_create("Equal / Scale / Precision");
  tcase_add_test(equal_case, test_equal_same_sign);
  tcase_add_test(equal_case, test_scale);
  tcase_add_test(equal_case, test_precision);
  suite_add_tcase(suite, equal_case);

  TCase *overflow_case = tcase_create("Overflow / Underflow");
  tcase_add_test(overflow_case, test_overflow);
  tcase_add_test(overflow_case, test_add_overflow_sign_diff);
  suite_add_tcase(suite, overflow_case);

  TCase *null_case = tcase_create("NULL pointer");
  tcase_add_test(null_case, test_null_ptr);
  suite_add_tcase(suite, null_case);

  return suite;
}
