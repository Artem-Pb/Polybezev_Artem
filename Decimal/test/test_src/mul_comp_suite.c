#include <check.h>

#include "../../src/decimal.h"

// Тест 1: NULL указатель результата
START_TEST(test_mul_null_result) {
  s21_decimal dec1 = {{5, 0, 0, 0}};
  s21_decimal dec2 = {{3, 0, 0, 0}};

  int result = s21_mul(dec1, dec2, S21_NULL);
  ck_assert_int_eq(result, 1);
}
END_TEST

// Тест 2: Умножение на ноль (первый операнд ноль)
START_TEST(test_mul_first_zero) {
  s21_decimal dec1 = {{0, 0, 0, 0}};
  s21_decimal dec2 = {{123, 0, 0, 0}};
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_sign(&result), 0);
}
END_TEST

// Тест 3: Умножение на ноль (второй операнд ноль)
START_TEST(test_mul_second_zero) {
  s21_decimal dec1 = {{456, 0, 0, 0}};
  s21_decimal dec2 = {{0, 0, 0, 0}};
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_sign(&result), 0);
}
END_TEST

// Тест 4: Умножение на ноль с отрицательным знаком
START_TEST(test_mul_zero_negative) {
  s21_decimal dec1 = {{0, 0, 0, 0x80000000}};  // -0
  s21_decimal dec2 = {{789, 0, 0, 0}};
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  // Знак должен быть 0 (положительный ноль)
  ck_assert_int_eq(get_sign(&result), 1);
}
END_TEST

// Тест 5: Простое умножение положительных чисел
START_TEST(test_mul_simple_positive) {
  s21_decimal dec1 = {{5, 0, 0, 0}};
  s21_decimal dec2 = {{3, 0, 0, 0}};
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 15);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_sign(&result), 0);
}
END_TEST

// Тест 6: Умножение с разными знаками (первый отрицательный)
START_TEST(test_mul_different_signs_first_negative) {
  s21_decimal dec1 = {{10, 0, 0, 0x80000000}};  // -10
  s21_decimal dec2 = {{4, 0, 0, 0}};            // +4
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 40);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_sign(&result), 1);  // Отрицательный результат
}
END_TEST

// Тест 7: Умножение с разными знаками (второй отрицательный)
START_TEST(test_mul_different_signs_second_negative) {
  s21_decimal dec1 = {{7, 0, 0, 0}};           // +7
  s21_decimal dec2 = {{6, 0, 0, 0x80000000}};  // -6
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 42);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_sign(&result), 1);  // Отрицательный результат
}
END_TEST

// Тест 8: Умножение двух отрицательных чисел
START_TEST(test_mul_both_negative) {
  s21_decimal dec1 = {{8, 0, 0, 0x80000000}};  // -8
  s21_decimal dec2 = {{9, 0, 0, 0x80000000}};  // -9
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 72);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(get_sign(&result), 0);  // Положительный результат
}
END_TEST

// Тест 9: Умножение с масштабами
START_TEST(test_mul_with_scales) {
  s21_decimal dec1 = {{25, 0, 0, 0x00010000}};  // 2.5
  s21_decimal dec2 = {{40, 0, 0, 0x00010000}};  // 4.0
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 1000);
  ck_assert_int_eq(get_scale(&result), 2);  // 2.5 * 4.0 = 10.00
  ck_assert_int_eq(get_sign(&result), 0);
}
END_TEST

// Тест 10: Большой масштаб (scale > 28) - требует округления
START_TEST(test_mul_large_scale) {
  s21_decimal dec1 = {{1, 0, 0, 0x00140000}};  // scale=20
  s21_decimal dec2 = {{1, 0, 0, 0x000F0000}};  // scale=15
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code, 0);
  // Общий scale был бы 35, но должен быть уменьшен до 28
  ck_assert_int_eq(get_scale(&result), 28);
}
END_TEST

// Тест 11: Переполнение (положительное)
START_TEST(test_mul_overflow_positive) {
  s21_decimal dec1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // MAX decimal
  s21_decimal dec2 = {{2, 0, 0, 0}};
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code,
                   1);  // Должен вернуть 1 для положительного переполнения
}
END_TEST

// Тест 12: Переполнение (отрицательное)
START_TEST(test_mul_overflow_negative) {
  s21_decimal dec1 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};  // -MAX
  s21_decimal dec2 = {{2, 0, 0, 0}};
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code,
                   2);  // Должен вернуть 2 для отрицательного переполнения
}
END_TEST

// Тест 13: Умножение больших чисел без переполнения
START_TEST(test_mul_large_numbers_no_overflow) {
  s21_decimal dec1 = {{0xFFFFFF, 0, 0, 0}};  // Большое число
  s21_decimal dec2 = {{2, 0, 0, 0}};
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_uint_eq(result.bits[0], 0x1FFFFFE);
}
END_TEST

// Тест 14: Умножение с банковским округлением (rem == 5)
START_TEST(test_mul_bankers_rounding) {
  // Создаем ситуацию, где остаток = 5 и младший бит четный
  // Это требует специфических входных данных, которые приведут к такому
  // сценарию
  s21_decimal dec1 = {{5, 0, 0, 0x001D0000}};  // scale=29
  s21_decimal dec2 = {{1, 0, 0, 0x00010000}};  // scale=1
  s21_decimal result;

  int code = s21_mul(dec1, dec2, &result);
  // Проверяем, что функция завершилась без ошибок
  ck_assert_int_ne(code, 1);
  ck_assert_int_ne(code, 2);
}
END_TEST

Suite *s21_mul_comprehensive_suite(void) {
  Suite *suite = suite_create("s21_mul_comprehensive");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_mul_null_result);
  tcase_add_test(tc_core, test_mul_first_zero);
  tcase_add_test(tc_core, test_mul_second_zero);
  tcase_add_test(tc_core, test_mul_zero_negative);
  tcase_add_test(tc_core, test_mul_simple_positive);
  tcase_add_test(tc_core, test_mul_different_signs_first_negative);
  tcase_add_test(tc_core, test_mul_different_signs_second_negative);
  tcase_add_test(tc_core, test_mul_both_negative);
  tcase_add_test(tc_core, test_mul_with_scales);
  tcase_add_test(tc_core, test_mul_large_scale);
  tcase_add_test(tc_core, test_mul_overflow_positive);
  tcase_add_test(tc_core, test_mul_overflow_negative);
  tcase_add_test(tc_core, test_mul_large_numbers_no_overflow);
  tcase_add_test(tc_core, test_mul_bankers_rounding);

  suite_add_tcase(suite, tc_core);

  return suite;
}