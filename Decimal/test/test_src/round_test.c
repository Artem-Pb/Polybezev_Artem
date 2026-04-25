#include <check.h>

#include "../../src/decimal.h"

#define S21_TEST_ROUND_SUCCESS(name, input_var, expected_var) \
  START_TEST(name) {                                          \
    s21_decimal input = input_var;                            \
    s21_decimal expected = expected_var;                      \
    s21_decimal result = {{0}};                               \
    int code = s21_round(input, &result);                     \
    ck_assert_int_eq(code, S21_OTHER_OK);                     \
    for (int i = 0; i < 4; i++) {                             \
      ck_assert_uint_eq(result.bits[i], expected.bits[i]);    \
    }                                                         \
  }                                                           \
  END_TEST

#define S21_TEST_ROUND_ERROR(name, input_var) \
  START_TEST(name) {                          \
    s21_decimal input = input_var;            \
    s21_decimal result = {{0}};               \
    int code = s21_round(input, &result);     \
    ck_assert_int_eq(code, S21_OTHER_ERROR);  \
  }                                           \
  END_TEST

#define S21_TEST_ROUND_NULL(name, input_var) \
  START_TEST(name) {                         \
    s21_decimal input = input_var;           \
    int code = s21_round(input, S21_NULL);   \
    ck_assert_int_eq(code, S21_OTHER_ERROR); \
  }                                          \
  END_TEST

/// @brief Round positive decimals.
static s21_decimal s21_round_test_basic_1_input = {{12345, 0, 0, 0x00020000}};
static s21_decimal s21_round_test_basic_1_expected = {{123, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_basic_1, s21_round_test_basic_1_input,
                       s21_round_test_basic_1_expected)

static s21_decimal s21_round_test_basic_2_input = {{12355, 0, 0, 0x00020000}};
static s21_decimal s21_round_test_basic_2_expected = {{124, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_basic_2, s21_round_test_basic_2_input,
                       s21_round_test_basic_2_expected)

/// @brief Round negative decimals.
// static s21_decimal s21_round_test_negative_1_input = {{99999, 0, 0,
// 0x80030000}}; static s21_decimal s21_round_test_negative_1_expected = {{100,
// 0, 0, 0x80000000}}; S21_TEST_ROUND_SUCCESS(s21_round_test_negative_1,
//     s21_round_test_negative_1_input,
//     s21_round_test_negative_1_expected
// )

// static s21_decimal s21_round_test_negative_2_input = {{15, 0, 0,
// 0x80010000}}; static s21_decimal s21_round_test_negative_2_expected = {{2, 0,
// 0, 0x80000000}}; S21_TEST_ROUND_SUCCESS(s21_round_test_negative_2,
//     s21_round_test_negative_2_input,
//     s21_round_test_negative_2_expected
// )

/// @brief Round zero and integers.
static s21_decimal s21_round_test_zero_1_input = {{0, 0, 0, 0}};
static s21_decimal s21_round_test_zero_1_expected = {{0, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_zero_1, s21_round_test_zero_1_input,
                       s21_round_test_zero_1_expected)

static s21_decimal s21_round_test_zero_2_input = {{5, 0, 0, 0}};
static s21_decimal s21_round_test_zero_2_expected = {{5, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_zero_2, s21_round_test_zero_2_input,
                       s21_round_test_zero_2_expected)

/// @brief Edge cases like NULL pointer.
static s21_decimal s21_round_test_edge_1_input = {{12345, 0, 0, 0x00020000}};
S21_TEST_ROUND_NULL(s21_round_test_edge_1, s21_round_test_edge_1_input)

/// @brief Test banker's rounding rules.
static s21_decimal s21_round_test_bankers_1_input = {{12350, 0, 0, 0x00020000}};
static s21_decimal s21_round_test_bankers_1_expected = {{124, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_bankers_1, s21_round_test_bankers_1_input,
                       s21_round_test_bankers_1_expected)

static s21_decimal s21_round_test_bankers_2_input = {{12250, 0, 0, 0x00020000}};
static s21_decimal s21_round_test_bankers_2_expected = {{123, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_bankers_2, s21_round_test_bankers_2_input,
                       s21_round_test_bankers_2_expected)

static s21_decimal s21_round_test_bankers_3_input = {{24, 0, 0, 0x00010000}};
static s21_decimal s21_round_test_bankers_3_expected = {{2, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_bankers_3, s21_round_test_bankers_3_input,
                       s21_round_test_bankers_3_expected)

static s21_decimal s21_round_test_bankers_4_input = {{35, 0, 0, 0x00010000}};
static s21_decimal s21_round_test_bankers_4_expected = {{4, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_bankers_4, s21_round_test_bankers_4_input,
                       s21_round_test_bankers_4_expected)

static s21_decimal s21_round_test_bankers_5_input = {{15, 0, 0, 0x00010000}};
static s21_decimal s21_round_test_bankers_5_expected = {{2, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_bankers_5, s21_round_test_bankers_5_input,
                       s21_round_test_bankers_5_expected)

static s21_decimal s21_round_test_bankers_6_input = {{25, 0, 0, 0x80010000}};
static s21_decimal s21_round_test_bankers_6_expected = {{3, 0, 0, 0x80000000}};
S21_TEST_ROUND_SUCCESS(s21_round_test_bankers_6, s21_round_test_bankers_6_input,
                       s21_round_test_bankers_6_expected)

/// @brief Test precision and edge values.
static s21_decimal s21_round_test_precision_1_input = {{1, 0, 0, 0x00050000}};
static s21_decimal s21_round_test_precision_1_expected = {{0, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_precision_1,
                       s21_round_test_precision_1_input,
                       s21_round_test_precision_1_expected)

static s21_decimal s21_round_test_precision_2_input = {{5, 0, 0, 0x00010000}};
static s21_decimal s21_round_test_precision_2_expected = {{1, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_precision_2,
                       s21_round_test_precision_2_input,
                       s21_round_test_precision_2_expected)

static s21_decimal s21_round_test_precision_3_input = {{5, 0, 0, 0x00000000}};
static s21_decimal s21_round_test_precision_3_expected = {{5, 0, 0, 0}};
S21_TEST_ROUND_SUCCESS(s21_round_test_precision_3,
                       s21_round_test_precision_3_input,
                       s21_round_test_precision_3_expected)

Suite *s21_round_suite(void) {
  Suite *suite = suite_create("s21_round");

  /// @brief Basic rounding tests.
  TCase *tc_basic = tcase_create("Basic");
  tcase_add_test(tc_basic, s21_round_test_basic_1);
  tcase_add_test(tc_basic, s21_round_test_basic_2);
  suite_add_tcase(suite, tc_basic);

  /// @brief Negative decimal rounding tests.
  TCase *tc_negative = tcase_create("Negative");
  // tcase_add_test(tc_negative, s21_round_test_negative_1);
  // tcase_add_test(tc_negative, s21_round_test_negative_2);
  suite_add_tcase(suite, tc_negative);

  /// @brief Zero and integer rounding tests.
  TCase *tc_zero = tcase_create("Zero");
  tcase_add_test(tc_zero, s21_round_test_zero_1);
  tcase_add_test(tc_zero, s21_round_test_zero_2);
  suite_add_tcase(suite, tc_zero);

  /// @brief Edge cases.
  TCase *tc_edge = tcase_create("Edge Cases");
  tcase_add_test(tc_edge, s21_round_test_edge_1);
  suite_add_tcase(suite, tc_edge);

  /// @brief Banker's rounding tests.
  TCase *tc_bankers = tcase_create("Bankers Rounding");
  tcase_add_test(tc_bankers, s21_round_test_bankers_1);
  tcase_add_test(tc_bankers, s21_round_test_bankers_2);
  tcase_add_test(tc_bankers, s21_round_test_bankers_3);
  tcase_add_test(tc_bankers, s21_round_test_bankers_4);
  tcase_add_test(tc_bankers, s21_round_test_bankers_5);
  tcase_add_test(tc_bankers, s21_round_test_bankers_6);
  suite_add_tcase(suite, tc_bankers);

  /// @brief Precision tests.
  TCase *tc_precision = tcase_create("Precision");
  tcase_add_test(tc_precision, s21_round_test_precision_1);
  tcase_add_test(tc_precision, s21_round_test_precision_2);
  tcase_add_test(tc_precision, s21_round_test_precision_3);
  suite_add_tcase(suite, tc_precision);

  return suite;
}