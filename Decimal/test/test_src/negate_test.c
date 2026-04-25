#include <check.h>

#include "../../src/decimal.h"

#define S21_TEST_NEGATE_SUCCESS(name, input_var, expected_var) \
  START_TEST(name) {                                           \
    s21_decimal input = input_var;                             \
    s21_decimal expected = expected_var;                       \
    s21_decimal result = {{0}};                                \
    int code = s21_negate(input, &result);                     \
    ck_assert_int_eq(code, S21_OTHER_OK);                      \
    for (int i = 0; i < 4; i++) {                              \
      ck_assert_uint_eq(result.bits[i], expected.bits[i]);     \
    }                                                          \
  }                                                            \
  END_TEST

#define S21_TEST_NEGATE_ERROR(name, input_var) \
  START_TEST(name) {                           \
    s21_decimal input = input_var;             \
    s21_decimal result = {{0}};                \
    int code = s21_negate(input, &result);     \
    ck_assert_int_eq(code, S21_OTHER_ERROR);   \
  }                                            \
  END_TEST

#define S21_TEST_NEGATE_NULL(name, input_var) \
  START_TEST(name) {                          \
    s21_decimal input = input_var;            \
    int code = s21_negate(input, S21_NULL);   \
    ck_assert_int_eq(code, S21_OTHER_ERROR);  \
  }                                           \
  END_TEST

/// @brief Negate positive numbers.
static s21_decimal s21_negate_test_basic_1_input = {{12345, 0, 0, 0x00020000}};
static s21_decimal s21_negate_test_basic_1_expected = {
    {12345, 0, 0, 0x80020000}};
S21_TEST_NEGATE_SUCCESS(s21_negate_test_basic_1, s21_negate_test_basic_1_input,
                        s21_negate_test_basic_1_expected)

static s21_decimal s21_negate_test_basic_2_input = {{1, 0, 0, 0}};
static s21_decimal s21_negate_test_basic_2_expected = {{1, 0, 0, 0x80000000}};
S21_TEST_NEGATE_SUCCESS(s21_negate_test_basic_2, s21_negate_test_basic_2_input,
                        s21_negate_test_basic_2_expected)

/// @brief Negate negative numbers.
static s21_decimal s21_negate_test_negative_1_input = {
    {99999, 0, 0, 0x80030000}};
static s21_decimal s21_negate_test_negative_1_expected = {
    {99999, 0, 0, 0x00030000}};
S21_TEST_NEGATE_SUCCESS(s21_negate_test_negative_1,
                        s21_negate_test_negative_1_input,
                        s21_negate_test_negative_1_expected)

static s21_decimal s21_negate_test_negative_2_input = {{1, 0, 0, 0x80000000}};
static s21_decimal s21_negate_test_negative_2_expected = {{1, 0, 0, 0}};
S21_TEST_NEGATE_SUCCESS(s21_negate_test_negative_2,
                        s21_negate_test_negative_2_input,
                        s21_negate_test_negative_2_expected)

/// @brief Negate zero.
static s21_decimal s21_negate_test_zero_1_input = {{0, 0, 0, 0}};
static s21_decimal s21_negate_test_zero_1_expected = {{0, 0, 0, 0x80000000}};
S21_TEST_NEGATE_SUCCESS(s21_negate_test_zero_1, s21_negate_test_zero_1_input,
                        s21_negate_test_zero_1_expected)

static s21_decimal s21_negate_test_zero_2_input = {{0, 0, 0, 0x80000000}};
static s21_decimal s21_negate_test_zero_2_expected = {{0, 0, 0, 0}};
S21_TEST_NEGATE_SUCCESS(s21_negate_test_zero_2, s21_negate_test_zero_2_input,
                        s21_negate_test_zero_2_expected)

/// @brief Edge cases like NULL pointer.
static s21_decimal s21_negate_test_edge_1_input = {{12345, 0, 0, 0x00020000}};
S21_TEST_NEGATE_NULL(s21_negate_test_edge_1, s21_negate_test_edge_1_input)

/// @brief Negate large numbers.
static s21_decimal s21_negate_test_large_1_input = {
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
static s21_decimal s21_negate_test_large_1_expected = {
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
S21_TEST_NEGATE_SUCCESS(s21_negate_test_large_1, s21_negate_test_large_1_input,
                        s21_negate_test_large_1_expected)

static s21_decimal s21_negate_test_large_2_input = {
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
static s21_decimal s21_negate_test_large_2_expected = {
    {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
S21_TEST_NEGATE_SUCCESS(s21_negate_test_large_2, s21_negate_test_large_2_input,
                        s21_negate_test_large_2_expected)

/// @brief Negate numbers with various scales.
static s21_decimal s21_negate_test_scale_1_input = {{123, 0, 0, 0x00050000}};
static s21_decimal s21_negate_test_scale_1_expected = {{123, 0, 0, 0x80050000}};
S21_TEST_NEGATE_SUCCESS(s21_negate_test_scale_1, s21_negate_test_scale_1_input,
                        s21_negate_test_scale_1_expected)

static s21_decimal s21_negate_test_scale_2_input = {{123, 0, 0, 0x1C000000}};
static s21_decimal s21_negate_test_scale_2_expected = {{123, 0, 0, 0x9C000000}};
S21_TEST_NEGATE_SUCCESS(s21_negate_test_scale_2, s21_negate_test_scale_2_input,
                        s21_negate_test_scale_2_expected)

Suite *s21_negate_suite(void) {
  Suite *suite = suite_create("s21_negate");

  /// @brief Basic positive number negation tests.
  TCase *tc_basic = tcase_create("Basic");
  tcase_add_test(tc_basic, s21_negate_test_basic_1);
  tcase_add_test(tc_basic, s21_negate_test_basic_2);
  suite_add_tcase(suite, tc_basic);

  /// @brief Negative number negation tests.
  TCase *tc_negative = tcase_create("Negative");
  tcase_add_test(tc_negative, s21_negate_test_negative_1);
  tcase_add_test(tc_negative, s21_negate_test_negative_2);
  suite_add_tcase(suite, tc_negative);

  /// @brief Zero negation tests.
  TCase *tc_zero = tcase_create("Zero");
  tcase_add_test(tc_zero, s21_negate_test_zero_1);
  tcase_add_test(tc_zero, s21_negate_test_zero_2);
  suite_add_tcase(suite, tc_zero);

  /// @brief Edge cases.
  TCase *tc_edge = tcase_create("Edge Cases");
  tcase_add_test(tc_edge, s21_negate_test_edge_1);
  suite_add_tcase(suite, tc_edge);

  /// @brief Large number negation tests.
  TCase *tc_large = tcase_create("Large Numbers");
  tcase_add_test(tc_large, s21_negate_test_large_1);
  tcase_add_test(tc_large, s21_negate_test_large_2);
  suite_add_tcase(suite, tc_large);

  /// @brief Scale and sign tests.
  TCase *tc_scale = tcase_create("Scale and Sign");
  tcase_add_test(tc_scale, s21_negate_test_scale_1);
  tcase_add_test(tc_scale, s21_negate_test_scale_2);
  suite_add_tcase(suite, tc_scale);

  return suite;
}