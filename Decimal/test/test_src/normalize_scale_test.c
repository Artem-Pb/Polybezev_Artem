#include <check.h>

#include "../../src/decimal.h"

// Вспомогательная функция для создания decimal с определенным scale
s21_decimal create_decimal_with_scale(uint32_t bits0, uint32_t bits1,
                                      uint32_t bits2, int scale,
                                      int is_negative) {
  s21_decimal dec = {{bits0, bits1, bits2, 0}};
  if (is_negative) {
    dec.bits[3] = (1 << 31) | (scale << 16);
  } else {
    dec.bits[3] = scale << 16;
  }
  return dec;
}

// Тест 1: Оба указателя NULL
START_TEST(test_normalize_scale_both_null) {
  s21_internal_error_code_t result = normalize_scale(S21_NULL, S21_NULL);
  ck_assert_int_eq(result, S21_INTERNAL_NULL_POINTER);
}
END_TEST

// Тест 2: Первый указатель NULL
START_TEST(test_normalize_scale_first_null) {
  s21_decimal dec2 = {{100, 0, 0, 0x00020000}};
  s21_internal_error_code_t result = normalize_scale(S21_NULL, &dec2);
  ck_assert_int_eq(result, S21_INTERNAL_NULL_POINTER);
}
END_TEST

// Тест 3: Второй указатель NULL
START_TEST(test_normalize_scale_second_null) {
  s21_decimal dec1 = {{100, 0, 0, 0x00020000}};
  s21_internal_error_code_t result = normalize_scale(&dec1, S21_NULL);
  ck_assert_int_eq(result, S21_INTERNAL_NULL_POINTER);
}
END_TEST

// Тест 4: Масштабы уже равны
START_TEST(test_normalize_scale_already_equal) {
  s21_decimal dec1 = {{100, 0, 0, 0x00020000}};
  s21_decimal dec2 = {{50, 0, 0, 0x00020000}};
  s21_internal_error_code_t result = normalize_scale(&dec1, &dec2);
  ck_assert_int_eq(result, S21_INTERNAL_OK);
  ck_assert_int_eq(get_scale(&dec1), 2);
  ck_assert_int_eq(get_scale(&dec2), 2);
}
END_TEST

// Тест 5: scale1 < scale2 - успешное увеличение scale1
START_TEST(test_normalize_scale_increase_first_success) {
  s21_decimal dec1 = {{100, 0, 0, 0x00010000}};  // scale=1
  s21_decimal dec2 = {{50, 0, 0, 0x00030000}};   // scale=3

  s21_internal_error_code_t result = normalize_scale(&dec1, &dec2);

  ck_assert_int_eq(result, S21_INTERNAL_OK);
  ck_assert_int_eq(get_scale(&dec1), 3);
  ck_assert_int_eq(get_scale(&dec2), 3);
  ck_assert_int_eq(dec1.bits[0], 10000);  // 100 * 10^2
}
END_TEST

// Тест 6: scale1 > scale2 - успешное увеличение scale2
START_TEST(test_normalize_scale_increase_second_success) {
  s21_decimal dec1 = {{100, 0, 0, 0x00030000}};  // scale=3
  s21_decimal dec2 = {{50, 0, 0, 0x00010000}};   // scale=1

  s21_internal_error_code_t result = normalize_scale(&dec1, &dec2);

  ck_assert_int_eq(result, S21_INTERNAL_OK);
  ck_assert_int_eq(get_scale(&dec1), 3);
  ck_assert_int_eq(get_scale(&dec2), 3);
  ck_assert_int_eq(dec2.bits[0], 5000);  // 50 * 10^2
}
END_TEST

// Тест 7: scale1 < scale2 - неудачное увеличение scale1, успешное уменьшение
// scale2
START_TEST(test_normalize_scale_decrease_second_success) {
  // Создаем dec1, который не может быть увеличен (почти максимальное значение)
  s21_decimal dec1 = {
      {0xFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};  // Почти MAX
  s21_decimal dec2 = {{50, 0, 0, 0x00050000}};           // scale=5

  s21_internal_error_code_t result = normalize_scale(&dec1, &dec2);

  ck_assert_int_eq(result, S21_INTERNAL_OK);
  // dec2 должен быть уменьшен до scale=0
  ck_assert_int_eq(get_scale(&dec2), 0);
  ck_assert_int_eq(dec2.bits[0], 0);  // 50 без масштаба
}
END_TEST

START_TEST(test_normalize_scale_decrease_first_success) {
  s21_decimal dec1 = {{100, 0, 0, 0x00050000}};
  s21_decimal dec2 = {{0xFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};

  s21_internal_error_code_t result = normalize_scale(&dec1, &dec2);

  ck_assert_int_eq(result, S21_INTERNAL_OK);
  ck_assert_int_eq(get_scale(&dec1), 0);
  ck_assert_int_eq(dec1.bits[0], 0);
}
END_TEST

// Тест 9: Ошибка при уменьшении scale2 (scale=0)
START_TEST(test_normalize_scale_decrease_second_error) {
  s21_decimal dec1 = {
      {0xFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};  // Почти MAX
  s21_decimal dec2 = {{50, 0, 0, 0x00000000}};  // scale=0 - нельзя уменьшить

  s21_internal_error_code_t result = normalize_scale(&dec1, &dec2);

  ck_assert_int_eq(result, S21_INTERNAL_OK);
}
END_TEST

// Тест 10: Ошибка при уменьшении scale1 (scale=0)
START_TEST(test_normalize_scale_decrease_first_error) {
  s21_decimal dec1 = {{100, 0, 0, 0x00000000}};  // scale=0 - нельзя уменьшить
  s21_decimal dec2 = {
      {0xFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};  // Почти MAX

  s21_internal_error_code_t result = normalize_scale(&dec1, &dec2);

  ck_assert_int_eq(result, S21_INTERNAL_OK);
}
END_TEST

// Тест 11: Большая разница в масштабах
START_TEST(test_normalize_scale_large_difference) {
  s21_decimal dec1 = {{123, 0, 0, 0x00010000}};  // scale=1
  s21_decimal dec2 = {{456, 0, 0, 0x00070000}};  // scale=7

  s21_internal_error_code_t result = normalize_scale(&dec1, &dec2);

  ck_assert_int_eq(result, S21_INTERNAL_OK);
  ck_assert_int_eq(get_scale(&dec1), 7);
  ck_assert_int_eq(get_scale(&dec2), 7);
  ck_assert_int_eq(dec1.bits[0], 123000000);  // 123 * 10^6
}
END_TEST

Suite *normalize_scale_suite(void) {
  Suite *suite = suite_create("normalize_scale");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_normalize_scale_both_null);
  tcase_add_test(tc_core, test_normalize_scale_first_null);
  tcase_add_test(tc_core, test_normalize_scale_second_null);
  tcase_add_test(tc_core, test_normalize_scale_already_equal);
  tcase_add_test(tc_core, test_normalize_scale_increase_first_success);
  tcase_add_test(tc_core, test_normalize_scale_increase_second_success);
  tcase_add_test(tc_core, test_normalize_scale_decrease_second_success);
  tcase_add_test(tc_core, test_normalize_scale_decrease_first_success);
  tcase_add_test(tc_core, test_normalize_scale_decrease_second_error);
  tcase_add_test(tc_core, test_normalize_scale_decrease_first_error);
  tcase_add_test(tc_core, test_normalize_scale_large_difference);

  suite_add_tcase(suite, tc_core);

  return suite;
}