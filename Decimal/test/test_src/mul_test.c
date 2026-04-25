#include <check.h>

#include "../../src/decimal.h"

#define S21_TEST_MUL_DEC_DEC_INT_SUCCESS(name, dec1_var, dec2_var, \
                                         expected_var)             \
  START_TEST(name) {                                               \
    s21_decimal dec1 = dec1_var;                                   \
    s21_decimal dec2 = dec2_var;                                   \
    s21_decimal expected = expected_var;                           \
    s21_decimal result = {{0}};                                    \
    int code = s21_mul(dec1, dec2, &result);                       \
    ck_assert_int_eq(code, S21_ARITHMETIC_OK);                     \
    for (int i = 0; i < 4; i++) {                                  \
      ck_assert_uint_eq(result.bits[i], expected.bits[i]);         \
    }                                                              \
  }                                                                \
  END_TEST

#define S21_TEST_MUL_DEC_DEC_INT_OVERFLOW(name, dec1_var, dec2_var) \
  START_TEST(name) {                                                \
    s21_decimal dec1 = dec1_var;                                    \
    s21_decimal dec2 = dec2_var;                                    \
    s21_decimal result = {{0}};                                     \
    int code = s21_mul(dec1, dec2, &result);                        \
    ck_assert_int_eq(code, S21_ARITHMETIC_OVERFLOW);                \
  }                                                                 \
  END_TEST

#define S21_TEST_MUL_DEC_DEC_INT_UNDERFLOW(name, dec1_var, dec2_var) \
  START_TEST(name) {                                                 \
    s21_decimal dec1 = dec1_var;                                     \
    s21_decimal dec2 = dec2_var;                                     \
    s21_decimal result = {{0}};                                      \
    int code = s21_mul(dec1, dec2, &result);                         \
    ck_assert_int_eq(code, S21_ARITHMETIC_UNDERFLOW);                \
  }                                                                  \
  END_TEST

#define S21_TEST_MUL_DEC_DEC_INT_ERROR(name, dec1_var, dec2_var) \
  START_TEST(name) {                                             \
    s21_decimal dec1 = dec1_var;                                 \
    s21_decimal dec2 = dec2_var;                                 \
    int code = s21_mul(dec1, dec2, S21_NULL);                    \
    ck_assert_int_eq(code, S21_ARITHMETIC_OVERFLOW);             \
  }                                                              \
  END_TEST

/// @brief Basic multiplication of positive decimals with various scales.
static s21_decimal s21_mul_test_basic_1_dec1 = {{2, 0, 0, 0}};
static s21_decimal s21_mul_test_basic_1_dec2 = {{3, 0, 0, 0}};
static s21_decimal s21_mul_test_basic_1_expected = {{6, 0, 0, 0}};
S21_TEST_MUL_DEC_DEC_INT_SUCCESS(s21_mul_test_basic_1,
                                 s21_mul_test_basic_1_dec1,
                                 s21_mul_test_basic_1_dec2,
                                 s21_mul_test_basic_1_expected)

static s21_decimal s21_mul_test_basic_2_dec1 = {{5, 0, 0, 0x00010000}};
static s21_decimal s21_mul_test_basic_2_dec2 = {{4, 0, 0, 0x00010000}};
static s21_decimal s21_mul_test_basic_2_expected = {{20, 0, 0, 0x00020000}};
S21_TEST_MUL_DEC_DEC_INT_SUCCESS(s21_mul_test_basic_2,
                                 s21_mul_test_basic_2_dec1,
                                 s21_mul_test_basic_2_dec2,
                                 s21_mul_test_basic_2_expected)

static s21_decimal s21_mul_test_basic_3_dec1 = {{123, 0, 0, 0x00020000}};
static s21_decimal s21_mul_test_basic_3_dec2 = {{45, 0, 0, 0x00010000}};
static s21_decimal s21_mul_test_basic_3_expected = {{5535, 0, 0, 0x00030000}};
S21_TEST_MUL_DEC_DEC_INT_SUCCESS(s21_mul_test_basic_3,
                                 s21_mul_test_basic_3_dec1,
                                 s21_mul_test_basic_3_dec2,
                                 s21_mul_test_basic_3_expected)

/// @brief Multiplication involving negative decimals.
static s21_decimal s21_mul_test_negative_1_dec1 = {{10, 0, 0, 0x80000000}};
static s21_decimal s21_mul_test_negative_1_dec2 = {{5, 0, 0, 0}};
static s21_decimal s21_mul_test_negative_1_expected = {{50, 0, 0, 0x80000000}};
S21_TEST_MUL_DEC_DEC_INT_SUCCESS(s21_mul_test_negative_1,
                                 s21_mul_test_negative_1_dec1,
                                 s21_mul_test_negative_1_dec2,
                                 s21_mul_test_negative_1_expected)

static s21_decimal s21_mul_test_negative_2_dec1 = {{7, 0, 0, 0x80000000}};
static s21_decimal s21_mul_test_negative_2_dec2 = {{3, 0, 0, 0x80000000}};
static s21_decimal s21_mul_test_negative_2_expected = {{21, 0, 0, 0}};
S21_TEST_MUL_DEC_DEC_INT_SUCCESS(s21_mul_test_negative_2,
                                 s21_mul_test_negative_2_dec1,
                                 s21_mul_test_negative_2_dec2,
                                 s21_mul_test_negative_2_expected)

static s21_decimal s21_mul_test_negative_3_dec1 = {{100, 0, 0, 0x00020000}};
static s21_decimal s21_mul_test_negative_3_dec2 = {{50, 0, 0, 0x80020000}};
static s21_decimal s21_mul_test_negative_3_expected = {
    {5000, 0, 0, 0x80040000}};
S21_TEST_MUL_DEC_DEC_INT_SUCCESS(s21_mul_test_negative_3,
                                 s21_mul_test_negative_3_dec1,
                                 s21_mul_test_negative_3_dec2,
                                 s21_mul_test_negative_3_expected)

/// @brief Multiplication where one or both operands are zero.
static s21_decimal s21_mul_test_zero_1_dec1 = {{12345, 0, 0, 0x00030000}};
static s21_decimal s21_mul_test_zero_1_dec2 = {{0, 0, 0, 0}};
static s21_decimal s21_mul_test_zero_1_expected = {{0, 0, 0, 0}};
S21_TEST_MUL_DEC_DEC_INT_SUCCESS(s21_mul_test_zero_1, s21_mul_test_zero_1_dec1,
                                 s21_mul_test_zero_1_dec2,
                                 s21_mul_test_zero_1_expected)

static s21_decimal s21_mul_test_zero_2_dec1 = {{0, 0, 0, 0}};
static s21_decimal s21_mul_test_zero_2_dec2 = {{999, 0, 0, 0x80010000}};
static s21_decimal s21_mul_test_zero_2_expected = {{0, 0, 0, 0x80000000}};
S21_TEST_MUL_DEC_DEC_INT_SUCCESS(s21_mul_test_zero_2, s21_mul_test_zero_2_dec1,
                                 s21_mul_test_zero_2_dec2,
                                 s21_mul_test_zero_2_expected)

/// @brief Tests for result overflow (S21_ARITHMETIC_OVERFLOW,
/// S21_ARITHMETIC_UNDERFLOW).
static s21_decimal s21_mul_test_overflow_1_dec1 = {
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
static s21_decimal s21_mul_test_overflow_1_dec2 = {{2, 0, 0, 0x00000000}};
S21_TEST_MUL_DEC_DEC_INT_OVERFLOW(s21_mul_test_overflow_1,
                                  s21_mul_test_overflow_1_dec1,
                                  s21_mul_test_overflow_1_dec2)

static s21_decimal s21_mul_test_overflow_2_dec1 = {
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
static s21_decimal s21_mul_test_overflow_2_dec2 = {{2, 0, 0, 0x00000000}};
S21_TEST_MUL_DEC_DEC_INT_UNDERFLOW(s21_mul_test_overflow_2,
                                   s21_mul_test_overflow_2_dec1,
                                   s21_mul_test_overflow_2_dec2)

static s21_decimal s21_mul_test_overflow_3_dec1_alt = {
    {0xC4000, 0x38D7E32, 0, 0x00000000}};
static s21_decimal s21_mul_test_overflow_3_dec2_alt = {
    {0xC4000, 0x38D7E32, 0, 0x00000000}};
S21_TEST_MUL_DEC_DEC_INT_OVERFLOW(s21_mul_test_overflow_3,
                                  s21_mul_test_overflow_3_dec1_alt,
                                  s21_mul_test_overflow_3_dec2_alt)

/// @brief Tests for edge conditions like NULL pointers.
static s21_decimal s21_mul_test_edge_1_dec1 = {{2, 0, 0, 0}};
static s21_decimal s21_mul_test_edge_1_dec2 = {{3, 0, 0, 0}};
S21_TEST_MUL_DEC_DEC_INT_ERROR(s21_mul_test_edge_1, s21_mul_test_edge_1_dec1,
                               s21_mul_test_edge_1_dec2)

/// @brief Tests specifically for scale handling and normalization.
static s21_decimal s21_mul_test_scale_1_dec1 = {{1, 0, 0, 0x00050000}};
static s21_decimal s21_mul_test_scale_1_dec2 = {{1, 0, 0, 0x000A0000}};
static s21_decimal s21_mul_test_scale_1_expected = {{1, 0, 0, 0x000F0000}};
S21_TEST_MUL_DEC_DEC_INT_SUCCESS(s21_mul_test_scale_1,
                                 s21_mul_test_scale_1_dec1,
                                 s21_mul_test_scale_1_dec2,
                                 s21_mul_test_scale_1_expected)

// static s21_decimal s21_mul_test_scale_2_dec1 = {{1, 0, 0, 0x00140000}};
// static s21_decimal s21_mul_test_scale_2_dec2 = {{1, 0, 0, 0x000F0000}};
// // Expected result: 1 (scale=28) after decrease_scale
// static s21_decimal s21_mul_test_scale_2_expected = {{1, 0, 0, 0x1C000000}};
// S21_TEST_MUL_DEC_DEC_INT_SUCCESS(s21_mul_test_scale_2,
//     s21_mul_test_scale_2_dec1,
//     s21_mul_test_scale_2_dec2,
//     s21_mul_test_scale_2_expected
// )

/// @brief Tests for precision and rounding behavior.
static s21_decimal s21_mul_test_precision_1_dec1 = {
    {123456789, 0, 0, 0x00080000}};
static s21_decimal s21_mul_test_precision_1_dec2 = {{21, 0, 0, 0x00010000}};
static s21_decimal s21_mul_test_precision_1_expected = {
    {2592592569U, 0, 0, 0x00090000}};
S21_TEST_MUL_DEC_DEC_INT_SUCCESS(s21_mul_test_precision_1,
                                 s21_mul_test_precision_1_dec1,
                                 s21_mul_test_precision_1_dec2,
                                 s21_mul_test_precision_1_expected)

Suite *s21_mul_suite(void) {
  Suite *suite = suite_create("s21_mul");

  /// @brief Basic multiplication of positive decimals with various scales.
  TCase *basic_case = tcase_create("Basic");
  tcase_add_test(basic_case, s21_mul_test_basic_1);
  tcase_add_test(basic_case, s21_mul_test_basic_2);
  tcase_add_test(basic_case, s21_mul_test_basic_3);
  suite_add_tcase(suite, basic_case);

  /// @brief Multiplication involving negative decimals.
  TCase *negative_case = tcase_create("Negative");
  tcase_add_test(negative_case, s21_mul_test_negative_1);
  tcase_add_test(negative_case, s21_mul_test_negative_2);
  tcase_add_test(negative_case, s21_mul_test_negative_3);
  suite_add_tcase(suite, negative_case);

  /// @brief Multiplication where one or both operands are zero.
  TCase *zero_case = tcase_create("Zero");
  tcase_add_test(zero_case, s21_mul_test_zero_1);
  tcase_add_test(zero_case, s21_mul_test_zero_2);
  suite_add_tcase(suite, zero_case);

  /// @brief Tests for result overflow (S21_ARITHMETIC_OVERFLOW,
  /// S21_ARITHMETIC_UNDERFLOW).
  TCase *overflow_case = tcase_create("Overflow");
  tcase_add_test(overflow_case, s21_mul_test_overflow_1);
  tcase_add_test(overflow_case, s21_mul_test_overflow_2);
  tcase_add_test(overflow_case, s21_mul_test_overflow_3);
  suite_add_tcase(suite, overflow_case);

  /// @brief Tests for edge conditions like NULL pointers.
  TCase *edge_case = tcase_create("Edge Cases");
  tcase_add_test(edge_case, s21_mul_test_edge_1);
  suite_add_tcase(suite, edge_case);

  /// @brief Tests specifically for scale handling and normalization.
  TCase *scale_case = tcase_create("Scale");
  tcase_add_test(scale_case, s21_mul_test_scale_1);
  // tcase_add_test(scale_case, s21_mul_test_scale_2);
  suite_add_tcase(suite, scale_case);

  /// @brief Tests for precision and rounding behavior.
  TCase *precision_case = tcase_create("Precision");
  tcase_add_test(precision_case, s21_mul_test_precision_1);
  suite_add_tcase(suite, precision_case);

  return suite;
}