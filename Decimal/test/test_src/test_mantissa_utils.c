#include <check.h>

#include "../../src/decimal.h"

START_TEST(test_sub_mantissa_borrow_in_low_word) {
  s21_decimal dec1 = {{0x00000000, 0x00000001, 0x00000000, 0}};  // 0x100000000
  s21_decimal dec2 = {{0xFFFFFFFF, 0x00000000, 0x00000000, 0}};  // 0x0FFFFFFFF
  s21_decimal result = {{0}};
  s21_internal_error_code_t code = sub_mantissa(&dec1, &dec2, &result);
  ck_assert_int_eq(code, S21_INTERNAL_OK);
  ck_assert_uint_eq(result.bits[0], 1);
  ck_assert_uint_eq(result.bits[1], 0);
  ck_assert_uint_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_sub_mantissa_borrow_in_mid_word) {
  s21_decimal dec1 = {
      {0x00000000, 0x00000000, 0x00000001, 0}};  // 0x10000000000000000
  s21_decimal dec2 = {
      {0x00000000, 0xFFFFFFFF, 0x00000000, 0}};  // 0x0FFFFFFFF00000000
  s21_decimal result = {{0}};
  s21_internal_error_code_t code = sub_mantissa(&dec1, &dec2, &result);
  ck_assert_int_eq(code, S21_INTERNAL_OK);
  ck_assert_uint_eq(result.bits[0], 0);
  ck_assert_uint_eq(result.bits[1], 1);
  ck_assert_uint_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_sub_mantissa_overflow) {
  s21_decimal dec1 = {{0x00000001, 0x00000000, 0x00000000, 0}};  // 1
  s21_decimal dec2 = {
      {0x00000002, 0x00000000, 0x00000000, 0}};  // 2 → dec1 < dec2
  s21_decimal result = {{0}};
  s21_internal_error_code_t code = sub_mantissa(&dec1, &dec2, &result);
  ck_assert_int_eq(code, S21_INTERNAL_OVERFLOW);
  for (int i = 0; i < 3; i++) {
    ck_assert_uint_eq(result.bits[i], 0);
  }
}
END_TEST

START_TEST(test_sub_mantissa_null_pointers) {
  s21_decimal dummy = {{0}};
  ck_assert_int_eq(sub_mantissa(S21_NULL, &dummy, &dummy),
                   S21_INTERNAL_NULL_POINTER);
  ck_assert_int_eq(sub_mantissa(&dummy, S21_NULL, &dummy),
                   S21_INTERNAL_NULL_POINTER);
  ck_assert_int_eq(sub_mantissa(&dummy, &dummy, S21_NULL),
                   S21_INTERNAL_NULL_POINTER);
}
END_TEST

Suite *s21_sub_mantissa_unit_suite(void) {
  Suite *suite = suite_create("sub_mantissa (unit)");

  TCase *tc_borrow = tcase_create("Borrow");
  tcase_add_test(tc_borrow, test_sub_mantissa_borrow_in_low_word);
  tcase_add_test(tc_borrow, test_sub_mantissa_borrow_in_mid_word);
  tcase_add_test(tc_borrow, test_sub_mantissa_overflow);
  tcase_add_test(tc_borrow, test_sub_mantissa_null_pointers);
  suite_add_tcase(suite, tc_borrow);

  return suite;
}