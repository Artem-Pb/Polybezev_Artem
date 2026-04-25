#include <check.h>

#include "../../src/decimal.h"

#define S21_TEST_IS_GREATER_OR_EQUAL_TRUE(name, a, b) \
  START_TEST(name) {                                  \
    int result = s21_is_greater_or_equal(a, b);       \
    ck_assert_int_eq(result, 1);                      \
  }                                                   \
  END_TEST

#define S21_TEST_IS_GREATER_OR_EQUAL_FALSE(name, a, b) \
  START_TEST(name) {                                   \
    int result = s21_is_greater_or_equal(a, b);        \
    ck_assert_int_eq(result, 0);                       \
  }                                                    \
  END_TEST

static s21_decimal s21_is_greater_or_equal_test_one_zero_a = {
    {1, 0, 0, 0x00000000}};
static s21_decimal s21_is_greater_or_equal_test_one_zero_b = {
    {0, 0, 0, 0x00000000}};
S21_TEST_IS_GREATER_OR_EQUAL_TRUE(s21_is_greater_or_equal_test_one_zero,
                                  s21_is_greater_or_equal_test_one_zero_a,
                                  s21_is_greater_or_equal_test_one_zero_b)

static s21_decimal s21_is_greater_or_equal_test_zero_one_a = {
    {0, 0, 0, 0x00000000}};
static s21_decimal s21_is_greater_or_equal_test_zero_one_b = {
    {1, 0, 0, 0x00000000}};
S21_TEST_IS_GREATER_OR_EQUAL_FALSE(s21_is_greater_or_equal_test_zero_one,
                                   s21_is_greater_or_equal_test_zero_one_a,
                                   s21_is_greater_or_equal_test_zero_one_b)

static s21_decimal s21_is_greater_or_equal_test_one_one_a = {
    {1, 0, 0, 0x00000000}};
static s21_decimal s21_is_greater_or_equal_test_one_one_b = {
    {1, 0, 0, 0x00000000}};
S21_TEST_IS_GREATER_OR_EQUAL_TRUE(s21_is_greater_or_equal_test_one_one,
                                  s21_is_greater_or_equal_test_one_one_a,
                                  s21_is_greater_or_equal_test_one_one_b)

static s21_decimal s21_is_greater_or_equal_test_zero_minus_one_a = {
    {0, 0, 0, 0x00000000}};
static s21_decimal s21_is_greater_or_equal_test_zero_minus_one_b = {
    {1, 0, 0, 0x80000000}};
S21_TEST_IS_GREATER_OR_EQUAL_TRUE(s21_is_greater_or_equal_test_zero_minus_one,
                                  s21_is_greater_or_equal_test_zero_minus_one_a,
                                  s21_is_greater_or_equal_test_zero_minus_one_b)

static s21_decimal s21_is_greater_or_equal_test_minus_one_zero_a = {
    {1, 0, 0, 0x80000000}};
static s21_decimal s21_is_greater_or_equal_test_minus_one_zero_b = {
    {0, 0, 0, 0x00000000}};
S21_TEST_IS_GREATER_OR_EQUAL_FALSE(
    s21_is_greater_or_equal_test_minus_one_zero,
    s21_is_greater_or_equal_test_minus_one_zero_a,
    s21_is_greater_or_equal_test_minus_one_zero_b)

static s21_decimal s21_is_greater_or_equal_test_minus_one_minus_one_a = {
    {1, 0, 0, 0x80000000}};
static s21_decimal s21_is_greater_or_equal_test_minus_one_minus_one_b = {
    {1, 0, 0, 0x80000000}};
S21_TEST_IS_GREATER_OR_EQUAL_TRUE(
    s21_is_greater_or_equal_test_minus_one_minus_one,
    s21_is_greater_or_equal_test_minus_one_minus_one_a,
    s21_is_greater_or_equal_test_minus_one_minus_one_b)

static s21_decimal s21_is_greater_or_equal_test_zero_zero_a = {
    {0, 0, 0, 0x00000000}};
static s21_decimal s21_is_greater_or_equal_test_zero_zero_b = {
    {0, 0, 0, 0x00000000}};
S21_TEST_IS_GREATER_OR_EQUAL_TRUE(s21_is_greater_or_equal_test_zero_zero,
                                  s21_is_greater_or_equal_test_zero_zero_a,
                                  s21_is_greater_or_equal_test_zero_zero_b)

static s21_decimal s21_is_greater_or_equal_test_minus_zero_minus_zero_a = {
    {0, 0, 0, 0x80000000}};
static s21_decimal s21_is_greater_or_equal_test_minus_zero_minus_zero_b = {
    {0, 0, 0, 0x80000000}};
S21_TEST_IS_GREATER_OR_EQUAL_TRUE(
    s21_is_greater_or_equal_test_minus_zero_minus_zero,
    s21_is_greater_or_equal_test_minus_zero_minus_zero_a,
    s21_is_greater_or_equal_test_minus_zero_minus_zero_b)

Suite *s21_is_greater_or_equal_suite(void) {
  Suite *suite = suite_create("s21_is_greater_or_equal");

  TCase *tc_greater_or_equal = tcase_create("Greater Or Equal");
  tcase_add_test(tc_greater_or_equal, s21_is_greater_or_equal_test_one_zero);
  tcase_add_test(tc_greater_or_equal, s21_is_greater_or_equal_test_one_one);
  tcase_add_test(tc_greater_or_equal,
                 s21_is_greater_or_equal_test_zero_minus_one);
  tcase_add_test(tc_greater_or_equal,
                 s21_is_greater_or_equal_test_minus_one_minus_one);
  tcase_add_test(tc_greater_or_equal, s21_is_greater_or_equal_test_zero_zero);
  tcase_add_test(tc_greater_or_equal,
                 s21_is_greater_or_equal_test_minus_zero_minus_zero);
  suite_add_tcase(suite, tc_greater_or_equal);

  TCase *tc_not_greater_or_equal = tcase_create("Not Greater Or Equal");
  tcase_add_test(tc_not_greater_or_equal,
                 s21_is_greater_or_equal_test_zero_one);
  tcase_add_test(tc_not_greater_or_equal,
                 s21_is_greater_or_equal_test_minus_one_zero);
  suite_add_tcase(suite, tc_not_greater_or_equal);

  return suite;
}