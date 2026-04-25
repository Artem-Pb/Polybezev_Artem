#include <check.h>

#include "../../src/decimal.h"

#define S21_TEST_TRUNCATE_SUCCESS(name, input_var, expected_var) \
  START_TEST(name) {                                             \
    s21_decimal input = input_var;                               \
    s21_decimal expected = expected_var;                         \
    s21_decimal result = {{0}};                                  \
    int code = s21_truncate(input, &result);                     \
    ck_assert_int_eq(code, S21_OTHER_OK);                        \
    for (int i = 0; i < 4; i++) {                                \
      ck_assert_uint_eq(result.bits[i], expected.bits[i]);       \
    }                                                            \
  }                                                              \
  END_TEST

#define S21_TEST_TRUNCATE_ERROR(name, input_var) \
  START_TEST(name) {                             \
    s21_decimal input = input_var;               \
    s21_decimal result = {{0}};                  \
    int code = s21_truncate(input, &result);     \
    ck_assert_int_eq(code, S21_OTHER_ERROR);     \
  }                                              \
  END_TEST

#define S21_TEST_TRUNCATE_NULL(name, input_var) \
  START_TEST(name) {                            \
    s21_decimal input = input_var;              \
    int code = s21_truncate(input, S21_NULL);   \
    ck_assert_int_eq(code, S21_OTHER_ERROR);    \
  }                                             \
  END_TEST

/// @brief Truncate positive decimals.
static s21_decimal s21_truncate_test_basic_1_input = {
    {12345, 0, 0, 0x00020000}};
static s21_decimal s21_truncate_test_basic_1_expected = {{123, 0, 0, 0}};
S21_TEST_TRUNCATE_SUCCESS(s21_truncate_test_basic_1,
                          s21_truncate_test_basic_1_input,
                          s21_truncate_test_basic_1_expected)

static s21_decimal s21_truncate_test_basic_2_input = {
    {999999, 0, 0, 0x00060000}};
static s21_decimal s21_truncate_test_basic_2_expected = {{0, 0, 0, 0}};
S21_TEST_TRUNCATE_SUCCESS(s21_truncate_test_basic_2,
                          s21_truncate_test_basic_2_input,
                          s21_truncate_test_basic_2_expected)

/// @brief Truncate negative decimals.
static s21_decimal s21_truncate_test_negative_1_input = {
    {99999, 0, 0, 0x80030000}};
static s21_decimal s21_truncate_test_negative_1_expected = {
    {99, 0, 0, 0x80000000}};
S21_TEST_TRUNCATE_SUCCESS(s21_truncate_test_negative_1,
                          s21_truncate_test_negative_1_input,
                          s21_truncate_test_negative_1_expected)

static s21_decimal s21_truncate_test_negative_2_input = {{1, 0, 0, 0x80010000}};
static s21_decimal s21_truncate_test_negative_2_expected = {
    {0, 0, 0, 0x80000000}};
S21_TEST_TRUNCATE_SUCCESS(s21_truncate_test_negative_2,
                          s21_truncate_test_negative_2_input,
                          s21_truncate_test_negative_2_expected)

/// @brief Truncate zero and integers.
static s21_decimal s21_truncate_test_zero_1_input = {{0, 0, 0, 0}};
static s21_decimal s21_truncate_test_zero_1_expected = {{0, 0, 0, 0}};
S21_TEST_TRUNCATE_SUCCESS(s21_truncate_test_zero_1,
                          s21_truncate_test_zero_1_input,
                          s21_truncate_test_zero_1_expected)

static s21_decimal s21_truncate_test_zero_2_input = {{5, 0, 0, 0}};
static s21_decimal s21_truncate_test_zero_2_expected = {{5, 0, 0, 0}};
S21_TEST_TRUNCATE_SUCCESS(s21_truncate_test_zero_2,
                          s21_truncate_test_zero_2_input,
                          s21_truncate_test_zero_2_expected)

static s21_decimal s21_truncate_test_zero_3_input = {{0, 0, 0, 0x80000000}};
static s21_decimal s21_truncate_test_zero_3_expected = {{0, 0, 0, 0x80000000}};
S21_TEST_TRUNCATE_SUCCESS(s21_truncate_test_zero_3,
                          s21_truncate_test_zero_3_input,
                          s21_truncate_test_zero_3_expected)

static s21_decimal s21_truncate_test_zero_4_input = {{100, 0, 0, 0x80000000}};
static s21_decimal s21_truncate_test_zero_4_expected = {
    {100, 0, 0, 0x80000000}};
S21_TEST_TRUNCATE_SUCCESS(s21_truncate_test_zero_4,
                          s21_truncate_test_zero_4_input,
                          s21_truncate_test_zero_4_expected)

/// @brief Edge cases like NULL pointer.
static s21_decimal s21_truncate_test_edge_1_input = {{12345, 0, 0, 0x00020000}};
S21_TEST_TRUNCATE_NULL(s21_truncate_test_edge_1, s21_truncate_test_edge_1_input)

/// @brief Test precision.
static s21_decimal s21_truncate_test_precision_1_input = {
    {1, 0, 0, 0x00100000}};
static s21_decimal s21_truncate_test_precision_1_expected = {{0, 0, 0, 0}};
S21_TEST_TRUNCATE_SUCCESS(s21_truncate_test_precision_1,
                          s21_truncate_test_precision_1_input,
                          s21_truncate_test_precision_1_expected)

/// @brief Test different scales.
static s21_decimal s21_truncate_test_scale_1_input = {{123, 0, 0, 0x00000000}};
static s21_decimal s21_truncate_test_scale_1_expected = {{123, 0, 0, 0}};
S21_TEST_TRUNCATE_SUCCESS(s21_truncate_test_scale_1,
                          s21_truncate_test_scale_1_input,
                          s21_truncate_test_scale_1_expected)

static s21_decimal s21_truncate_test_scale_2_input = {{123, 0, 0, 0x00050000}};
static s21_decimal s21_truncate_test_scale_2_expected = {{0, 0, 0, 0}};
S21_TEST_TRUNCATE_SUCCESS(s21_truncate_test_scale_2,
                          s21_truncate_test_scale_2_input,
                          s21_truncate_test_scale_2_expected)

Suite *s21_truncate_suite(void) {
  Suite *suite = suite_create("s21_truncate");

  /// @brief Basic truncation tests.
  TCase *tc_basic = tcase_create("Basic");
  tcase_add_test(tc_basic, s21_truncate_test_basic_1);
  tcase_add_test(tc_basic, s21_truncate_test_basic_2);
  suite_add_tcase(suite, tc_basic);

  /// @brief Negative decimal truncation tests.
  TCase *tc_negative = tcase_create("Negative");
  tcase_add_test(tc_negative, s21_truncate_test_negative_1);
  tcase_add_test(tc_negative, s21_truncate_test_negative_2);
  suite_add_tcase(suite, tc_negative);

  /// @brief Zero and integer truncation tests.
  TCase *tc_zero = tcase_create("Zero");
  tcase_add_test(tc_zero, s21_truncate_test_zero_1);
  tcase_add_test(tc_zero, s21_truncate_test_zero_2);
  tcase_add_test(tc_zero, s21_truncate_test_zero_3);
  tcase_add_test(tc_zero, s21_truncate_test_zero_4);
  suite_add_tcase(suite, tc_zero);

  /// @brief Edge cases.
  TCase *tc_edge = tcase_create("Edge Cases");
  tcase_add_test(tc_edge, s21_truncate_test_edge_1);
  suite_add_tcase(suite, tc_edge);

  /// @brief Precision tests.
  TCase *tc_precision = tcase_create("Precision");
  tcase_add_test(tc_precision, s21_truncate_test_precision_1);
  suite_add_tcase(suite, tc_precision);

  /// @brief Scale tests.
  TCase *tc_scale = tcase_create("Scale");
  tcase_add_test(tc_scale, s21_truncate_test_scale_1);
  tcase_add_test(tc_scale, s21_truncate_test_scale_2);
  suite_add_tcase(suite, tc_scale);

  return suite;
}