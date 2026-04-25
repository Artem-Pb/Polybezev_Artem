#include <check.h>

#include "../../src/decimal.h"

#define S21_TEST_ADD_DEC_DEC_INT_SUCCESS(name, dec1_var, dec2_var, \
                                         expected_var)             \
  START_TEST(name) {                                               \
    s21_decimal dec1 = dec1_var;                                   \
    s21_decimal dec2 = dec2_var;                                   \
    s21_decimal expected = expected_var;                           \
    s21_decimal result = {{0}};                                    \
    int code = s21_add(dec1, dec2, &result);                       \
    ck_assert_int_eq(code, S21_ARITHMETIC_OK);                     \
    for (int i = 0; i < 4; i++) {                                  \
      ck_assert_uint_eq(result.bits[i], expected.bits[i]);         \
    }                                                              \
  }                                                                \
  END_TEST

#define S21_TEST_ADD_DEC_DEC_INT_OVERFLOW(name, dec1_var, dec2_var) \
  START_TEST(name) {                                                \
    s21_decimal dec1 = dec1_var;                                    \
    s21_decimal dec2 = dec2_var;                                    \
    s21_decimal result = {{0}};                                     \
    int code = s21_add(dec1, dec2, &result);                        \
    ck_assert_int_eq(code, S21_ARITHMETIC_OVERFLOW);                \
  }                                                                 \
  END_TEST

#define S21_TEST_ADD_DEC_DEC_INT_UNDERFLOW(name, dec1_var, dec2_var) \
  START_TEST(name) {                                                 \
    s21_decimal dec1 = dec1_var;                                     \
    s21_decimal dec2 = dec2_var;                                     \
    s21_decimal result = {{0}};                                      \
    int code = s21_add(dec1, dec2, &result);                         \
    ck_assert_int_eq(code, S21_ARITHMETIC_UNDERFLOW);                \
  }                                                                  \
  END_TEST

#define S21_TEST_ADD_DEC_DEC_INT_ERROR(name, dec1_var, dec2_var) \
  START_TEST(name) {                                             \
    s21_decimal dec1 = dec1_var;                                 \
    s21_decimal dec2 = dec2_var;                                 \
    int code = s21_add(dec1, dec2, S21_NULL);                    \
    ck_assert_int_eq(code, S21_ARITHMETIC_OVERFLOW);             \
  }                                                              \
  END_TEST

/// @brief Basic addition of positive decimals with various scales.
static s21_decimal s21_add_test_basic_1_dec1 = {{0, 0, 0, 0}};
static s21_decimal s21_add_test_basic_1_dec2 = {{0, 0, 0, 0}};
static s21_decimal s21_add_test_basic_1_expected = {{0, 0, 0, 0}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_basic_1,
                                 s21_add_test_basic_1_dec1,
                                 s21_add_test_basic_1_dec2,
                                 s21_add_test_basic_1_expected)

static s21_decimal s21_add_test_basic_2_dec1 = {{1, 0, 0, 0}};
static s21_decimal s21_add_test_basic_2_dec2 = {{2, 0, 0, 0}};
static s21_decimal s21_add_test_basic_2_expected = {{3, 0, 0, 0}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_basic_2,
                                 s21_add_test_basic_2_dec1,
                                 s21_add_test_basic_2_dec2,
                                 s21_add_test_basic_2_expected)

static s21_decimal s21_add_test_basic_3_dec1 = {{10, 0, 0, 0x00010000}};
static s21_decimal s21_add_test_basic_3_dec2 = {{20, 0, 0, 0x00010000}};
static s21_decimal s21_add_test_basic_3_expected = {{30, 0, 0, 0x00010000}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_basic_3,
                                 s21_add_test_basic_3_dec1,
                                 s21_add_test_basic_3_dec2,
                                 s21_add_test_basic_3_expected)

static s21_decimal s21_add_test_basic_4_dec1 = {{12345, 0, 0, 0x00020000}};
static s21_decimal s21_add_test_basic_4_dec2 = {{6789, 0, 0, 0x00020000}};
static s21_decimal s21_add_test_basic_4_expected = {{19134, 0, 0, 0x00020000}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_basic_4,
                                 s21_add_test_basic_4_dec1,
                                 s21_add_test_basic_4_dec2,
                                 s21_add_test_basic_4_expected)

static s21_decimal s21_add_test_basic_5_dec1 = {{123, 0, 0, 0x00020000}};
static s21_decimal s21_add_test_basic_5_dec2 = {{4567, 0, 0, 0x00030000}};
static s21_decimal s21_add_test_basic_5_expected = {{5797, 0, 0, 0x00030000}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_basic_5,
                                 s21_add_test_basic_5_dec1,
                                 s21_add_test_basic_5_dec2,
                                 s21_add_test_basic_5_expected)

/// @brief Addition involving negative decimals.
static s21_decimal s21_add_test_negative_1_dec1 = {{1, 0, 0, 0x80000000}};
static s21_decimal s21_add_test_negative_1_dec2 = {{1, 0, 0, 0}};
static s21_decimal s21_add_test_negative_1_expected = {{0, 0, 0, 0x80000000}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_negative_1,
                                 s21_add_test_negative_1_dec1,
                                 s21_add_test_negative_1_dec2,
                                 s21_add_test_negative_1_expected)

static s21_decimal s21_add_test_negative_2_dec1 = {{55, 0, 0, 0x80010000}};
static s21_decimal s21_add_test_negative_2_dec2 = {{45, 0, 0, 0x80010000}};
static s21_decimal s21_add_test_negative_2_expected = {{100, 0, 0, 0x80010000}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_negative_2,
                                 s21_add_test_negative_2_dec1,
                                 s21_add_test_negative_2_dec2,
                                 s21_add_test_negative_2_expected)

static s21_decimal s21_add_test_negative_3_dec1 = {{10000, 0, 0, 0x00020000}};
static s21_decimal s21_add_test_negative_3_dec2 = {{5025, 0, 0, 0x80020000}};
static s21_decimal s21_add_test_negative_3_expected = {
    {4975, 0, 0, 0x00020000}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_negative_3,
                                 s21_add_test_negative_3_dec1,
                                 s21_add_test_negative_3_dec2,
                                 s21_add_test_negative_3_expected)

/// @brief Addition where one or both operands are zero.
static s21_decimal s21_add_test_zero_1_dec1 = {{0, 0, 0, 0}};
static s21_decimal s21_add_test_zero_1_dec2 = {{123456, 0, 0, 0x00030000}};
static s21_decimal s21_add_test_zero_1_expected = {{123456, 0, 0, 0x00030000}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_zero_1, s21_add_test_zero_1_dec1,
                                 s21_add_test_zero_1_dec2,
                                 s21_add_test_zero_1_expected)

static s21_decimal s21_add_test_zero_2_dec1 = {{99999, 0, 0, 0x80020000}};
static s21_decimal s21_add_test_zero_2_dec2 = {{0, 0, 0, 0}};
static s21_decimal s21_add_test_zero_2_expected = {{99999, 0, 0, 0x80020000}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_zero_2, s21_add_test_zero_2_dec1,
                                 s21_add_test_zero_2_dec2,
                                 s21_add_test_zero_2_expected)

/// @brief Tests for result overflow (S21_ARITHMETIC_OVERFLOW,
/// S21_ARITHMETIC_UNDERFLOW).
static s21_decimal s21_add_test_overflow_1_dec1 = {
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
static s21_decimal s21_add_test_overflow_1_dec2 = {{1, 0, 0, 0x00000000}};
S21_TEST_ADD_DEC_DEC_INT_OVERFLOW(s21_add_test_overflow_1,
                                  s21_add_test_overflow_1_dec1,
                                  s21_add_test_overflow_1_dec2)

static s21_decimal s21_add_test_overflow_2_dec1 = {
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
static s21_decimal s21_add_test_overflow_2_dec2 = {{1, 0, 0, 0x80000000}};
S21_TEST_ADD_DEC_DEC_INT_UNDERFLOW(s21_add_test_overflow_2,
                                   s21_add_test_overflow_2_dec1,
                                   s21_add_test_overflow_2_dec2)

/// @brief Tests for edge conditions like NULL pointers or extreme valid inputs.
static s21_decimal s21_add_test_edge_1_dec1 = {{1, 0, 0, 0}};
static s21_decimal s21_add_test_edge_1_dec2 = {{2, 0, 0, 0}};
S21_TEST_ADD_DEC_DEC_INT_ERROR(s21_add_test_edge_1, s21_add_test_edge_1_dec1,
                               s21_add_test_edge_1_dec2)

static s21_decimal s21_add_test_edge_2_dec1 = {
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C000000}};
static s21_decimal s21_add_test_edge_2_dec2 = {
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C000000}};
S21_TEST_ADD_DEC_DEC_INT_OVERFLOW(s21_add_test_edge_2, s21_add_test_edge_2_dec1,
                                  s21_add_test_edge_2_dec2)

/// @brief Tests specifically for scale handling and normalization.
static s21_decimal s21_add_test_scale_1_dec1_alt = {{123, 0, 0, 0x00020000}};
static s21_decimal s21_add_test_scale_1_dec2_alt = {{1, 0, 0, 0x00030000}};
static s21_decimal s21_add_test_scale_1_expected_alt = {
    {1231, 0, 0, 0x00030000}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_scale_1,
                                 s21_add_test_scale_1_dec1_alt,
                                 s21_add_test_scale_1_dec2_alt,
                                 s21_add_test_scale_1_expected_alt)

/// @brief Tests for precision and rounding behavior (where applicable for add).
static s21_decimal s21_add_test_precision_1_dec1 = {{1225, 0, 0, 0x00030000}};
static s21_decimal s21_add_test_precision_1_dec2 = {{5, 0, 0, 0x00040000}};
static s21_decimal s21_add_test_precision_1_expected = {
    {12255, 0, 0, 0x00040000}};
S21_TEST_ADD_DEC_DEC_INT_SUCCESS(s21_add_test_precision_1,
                                 s21_add_test_precision_1_dec1,
                                 s21_add_test_precision_1_dec2,
                                 s21_add_test_precision_1_expected)

Suite *s21_add_suite(void) {
  Suite *suite = suite_create("s21_add");

  /// @brief Basic addition of positive decimals with various scales.
  TCase *basic_case = tcase_create("Basic");
  tcase_add_test(basic_case, s21_add_test_basic_1);
  tcase_add_test(basic_case, s21_add_test_basic_2);
  tcase_add_test(basic_case, s21_add_test_basic_3);
  tcase_add_test(basic_case, s21_add_test_basic_4);
  tcase_add_test(basic_case, s21_add_test_basic_5);
  suite_add_tcase(suite, basic_case);

  /// @brief Addition involving negative decimals.
  TCase *negative_case = tcase_create("Negative");
  tcase_add_test(negative_case, s21_add_test_negative_1);
  tcase_add_test(negative_case, s21_add_test_negative_2);
  tcase_add_test(negative_case, s21_add_test_negative_3);
  suite_add_tcase(suite, negative_case);

  /// @brief Addition where one or both operands are zero.
  TCase *zero_case = tcase_create("Zero");
  tcase_add_test(zero_case, s21_add_test_zero_1);
  tcase_add_test(zero_case, s21_add_test_zero_2);
  suite_add_tcase(suite, zero_case);

  /// @brief Tests for result overflow (S21_ARITHMETIC_OVERFLOW,
  /// S21_ARITHMETIC_UNDERFLOW).
  TCase *overflow_case = tcase_create("Overflow");
  tcase_add_test(overflow_case, s21_add_test_overflow_1);
  tcase_add_test(overflow_case, s21_add_test_overflow_2);
  suite_add_tcase(suite, overflow_case);

  /// @brief Tests for edge conditions like NULL pointers or extreme valid
  /// inputs.
  TCase *edge_case = tcase_create("Edge Cases");
  tcase_add_test(edge_case, s21_add_test_edge_1);
  tcase_add_test(edge_case, s21_add_test_edge_2);
  suite_add_tcase(suite, edge_case);

  /// @brief Tests specifically for scale handling and normalization.
  TCase *scale_case = tcase_create("Scale");
  tcase_add_test(scale_case, s21_add_test_scale_1);
  suite_add_tcase(suite, scale_case);

  /// @brief Tests for precision and rounding behavior (where applicable for
  /// add).
  TCase *precision_case = tcase_create("Precision");
  tcase_add_test(precision_case, s21_add_test_precision_1);
  suite_add_tcase(suite, precision_case);

  return suite;
}