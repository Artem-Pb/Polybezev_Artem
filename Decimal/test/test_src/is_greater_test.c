#include <check.h>

#include "../../src/decimal.h"

#define S21_TEST_IS_GREATER_TRUE(name, a, b) \
  START_TEST(name) {                         \
    int result = s21_is_greater(a, b);       \
    ck_assert_int_eq(result, 1);             \
  }                                          \
  END_TEST

#define S21_TEST_IS_GREATER_FALSE(name, a, b) \
  START_TEST(name) {                          \
    int result = s21_is_greater(a, b);        \
    ck_assert_int_eq(result, 0);              \
  }                                           \
  END_TEST

static s21_decimal s21_is_greater_test_zero_zero_a = {{0, 0, 0, 0x00000000}};
static s21_decimal s21_is_greater_test_zero_zero_b = {{0, 0, 0, 0x00000000}};
S21_TEST_IS_GREATER_FALSE(s21_is_greater_test_zero_zero,
                          s21_is_greater_test_zero_zero_a,
                          s21_is_greater_test_zero_zero_b)

static s21_decimal s21_is_greater_test_one_zero_a = {{1, 0, 0, 0x00000000}};
static s21_decimal s21_is_greater_test_one_zero_b = {{0, 0, 0, 0x00000000}};
S21_TEST_IS_GREATER_TRUE(s21_is_greater_test_one_zero,
                         s21_is_greater_test_one_zero_a,
                         s21_is_greater_test_one_zero_b)

static s21_decimal s21_is_greater_test_zero_minus_one_a = {
    {0, 0, 0, 0x00000000}};
static s21_decimal s21_is_greater_test_zero_minus_one_b = {
    {1, 0, 0, 0x80000000}};
S21_TEST_IS_GREATER_TRUE(s21_is_greater_test_zero_minus_one,
                         s21_is_greater_test_zero_minus_one_a,
                         s21_is_greater_test_zero_minus_one_b)

static s21_decimal s21_is_greater_test_minus_one_zero_a = {
    {1, 0, 0, 0x80000000}};
static s21_decimal s21_is_greater_test_minus_one_zero_b = {
    {0, 0, 0, 0x00000000}};
S21_TEST_IS_GREATER_FALSE(s21_is_greater_test_minus_one_zero,
                          s21_is_greater_test_minus_one_zero_a,
                          s21_is_greater_test_minus_one_zero_b)

static s21_decimal s21_is_greater_test_two_one_a = {{2, 0, 0, 0x00000000}};
static s21_decimal s21_is_greater_test_two_one_b = {{1, 0, 0, 0x00000000}};
S21_TEST_IS_GREATER_TRUE(s21_is_greater_test_two_one,
                         s21_is_greater_test_two_one_a,
                         s21_is_greater_test_two_one_b)

static s21_decimal s21_is_greater_test_one_two_a = {{1, 0, 0, 0x00000000}};
static s21_decimal s21_is_greater_test_one_two_b = {{2, 0, 0, 0x00000000}};
S21_TEST_IS_GREATER_FALSE(s21_is_greater_test_one_two,
                          s21_is_greater_test_one_two_a,
                          s21_is_greater_test_one_two_b)

static s21_decimal s21_is_greater_test_minus_one_minus_two_a = {
    {1, 0, 0, 0x80000000}};
static s21_decimal s21_is_greater_test_minus_one_minus_two_b = {
    {2, 0, 0, 0x80000000}};
S21_TEST_IS_GREATER_TRUE(s21_is_greater_test_minus_one_minus_two,
                         s21_is_greater_test_minus_one_minus_two_a,
                         s21_is_greater_test_minus_one_minus_two_b)

static s21_decimal s21_is_greater_test_minus_two_minus_one_a = {
    {2, 0, 0, 0x80000000}};
static s21_decimal s21_is_greater_test_minus_two_minus_one_b = {
    {1, 0, 0, 0x80000000}};
S21_TEST_IS_GREATER_FALSE(s21_is_greater_test_minus_two_minus_one,
                          s21_is_greater_test_minus_two_minus_one_a,
                          s21_is_greater_test_minus_two_minus_one_b)

static s21_decimal s21_is_greater_test_15_10_a = {
    {15, 0, 0, 0x00010000}};  // 1.5
static s21_decimal s21_is_greater_test_15_10_b = {
    {10, 0, 0, 0x00010000}};  // 1.0
S21_TEST_IS_GREATER_TRUE(s21_is_greater_test_15_10, s21_is_greater_test_15_10_a,
                         s21_is_greater_test_15_10_b)

Suite *s21_is_greater_suite(void) {
  Suite *suite = suite_create("s21_is_greater");

  TCase *tc_greater = tcase_create("Greater");
  tcase_add_test(tc_greater, s21_is_greater_test_one_zero);
  tcase_add_test(tc_greater, s21_is_greater_test_zero_minus_one);
  tcase_add_test(tc_greater, s21_is_greater_test_two_one);
  tcase_add_test(tc_greater, s21_is_greater_test_minus_one_minus_two);
  tcase_add_test(tc_greater, s21_is_greater_test_15_10);
  suite_add_tcase(suite, tc_greater);

  TCase *tc_not_greater = tcase_create("Not Greater");
  tcase_add_test(tc_not_greater, s21_is_greater_test_zero_zero);
  tcase_add_test(tc_not_greater, s21_is_greater_test_minus_one_zero);
  tcase_add_test(tc_not_greater, s21_is_greater_test_one_two);
  tcase_add_test(tc_not_greater, s21_is_greater_test_minus_two_minus_one);
  suite_add_tcase(suite, tc_not_greater);

  return suite;
}