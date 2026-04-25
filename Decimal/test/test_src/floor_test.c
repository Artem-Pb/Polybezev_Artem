#include <check.h>

#include "../../src/decimal.h"

// ======================== START_TEST FUNCTIONS ========================

// Basic positive decimal floors
START_TEST(s21_floor_basic_1) {
  s21_decimal input = {{12345, 0, 0, 0x00020000}};
  s21_decimal expected = {{123, 0, 0, 0}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(s21_floor_basic_2) {
  s21_decimal input = {{10001, 0, 0, 0x00040000}};
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// Negative decimal floors
START_TEST(s21_floor_negative_1) {
  s21_decimal input = {{99999, 0, 0, 0x80030000}};
  s21_decimal expected = {{100, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(s21_floor_negative_2) {
  s21_decimal input = {{1, 0, 0, 0x80010000}};
  s21_decimal expected = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// Zero and integer floors
START_TEST(s21_floor_zero_1) {
  s21_decimal input = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(s21_floor_zero_2) {
  s21_decimal input = {{5, 0, 0, 0}};
  s21_decimal expected = {{5, 0, 0, 0}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(s21_floor_zero_3) {
  s21_decimal input = {{0, 0, 0, 0x80000000}};
  s21_decimal expected = {{0, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(s21_floor_zero_4) {
  s21_decimal input = {{100, 0, 0, 0x80000000}};
  s21_decimal expected = {{100, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// Edge case: NULL pointer
START_TEST(s21_floor_null_test) {
  s21_decimal input = {{12345, 0, 0, 0x00020000}};
  int code = s21_floor(input, S21_NULL);
  ck_assert_int_eq(code, S21_OTHER_ERROR);
}
END_TEST

// Precision and edge values
START_TEST(s21_floor_precision_1) {
  s21_decimal input = {{9999, 0, 0, 0x00030000}};
  s21_decimal expected = {{9, 0, 0, 0}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(s21_floor_precision_2) {
  s21_decimal input = {{1, 0, 0, 0x00050000}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(s21_floor_precision_3) {
  s21_decimal input = {{999999, 0, 0, 0x80060000}};
  s21_decimal expected = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// Scale handling
START_TEST(s21_floor_scale_1) {
  s21_decimal input = {{1, 0, 0, 0x00010000}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(s21_floor_scale_2) {
  s21_decimal input = {{1, 0, 0, 0}};
  s21_decimal expected = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

START_TEST(s21_floor_negative_exact) {
  s21_decimal input = {{500, 0, 0, 0x80020000}};   // -5.00
  s21_decimal expected = {{5, 0, 0, 0x80000000}};  // -5
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// Тест: вызов decrease_scale с ошибкой (имитация через заведомо невалидный
// decimal?) Но decrease_scale вызывается с scale=0 → может не вызвать ошибку.
// Вместо этого — создадим ситуацию, где уменьшение масштаба невозможно без
// потери точности? Лучше: создать очень большое число с большим scale — при
// уменьшении масштаба → overflow

// START_TEST(s21_floor_overflow_decrease_scale) {
//     // Создадим число, которое при уменьшении масштаба вызовет переполнение
//     // Например: максимальное значение mantissa с scale=1 — при уменьшении до
//     0 нужно умножить на 10 — overflow! s21_decimal input = {{0xFFFFFFFF,
//     0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}}; // Очень большое число с 1 знаком
//     после запятой s21_decimal result = {{0}}; int code = s21_floor(input,
//     &result); ck_assert_int_eq(code, S21_OTHER_ERROR);
//     // Проверим, что результат очищен
//     s21_decimal zero = {{0, 0, 0, 0}};
//     for (int i = 0; i < 4; i++)
//         ck_assert_uint_eq(result.bits[i], zero.bits[i]);
// } END_TEST

// Тест: имитация ошибки в increase_scale (при восстановлении для сравнения)
// Создадим число, которое при попытке восстановить scale вызовет переполнение
START_TEST(s21_floor_overflow_increase_scale) {
  // Отрицательное число, которое при попытке increase_scale вызовет ошибку
  s21_decimal input = {{0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF,
                        0x80290000}};  // Почти максимальное, scale=9
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_ERROR);
  s21_decimal zero = {{0, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_uint_eq(result.bits[i], zero.bits[i]);
}
END_TEST

// Тест: имитация ошибки в add_mantissa (при добавлении 1 к большому
// отрицательному)
START_TEST(s21_floor_overflow_add_mantissa) {
  // Отрицательное число, близкое к минимально представимому целому
  // После усечения получим -MAX, добавление 1 вызовет переполнение?
  // Но в s21_decimal MAX = 2^96-1, так что добавление 1 к MAX невозможно.
  // Создадим: MAX с отрицательным знаком и scale>0 → floor должен попытаться
  // сделать MAX+1 → overflow

  // Максимальное значение mantissa
  s21_decimal input = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80290000}  // -MAX_VALUE.X
  };
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_ERROR);
  s21_decimal zero = {{0, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_uint_eq(result.bits[i], zero.bits[i]);
}
END_TEST

// Тест: отрицательный ноль с дробной частью — крайний случай
START_TEST(s21_floor_negative_zero_fraction) {
  s21_decimal input = {{1, 0, 0, 0x80050000}};     // -0.00001
  s21_decimal expected = {{1, 0, 0, 0x80000000}};  // -1
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// Тест: очень маленькое положительное число → должно дать 0
START_TEST(s21_floor_tiny_positive) {
  s21_decimal input = {{1, 0, 0, 0x00100000}};  // 0.0000000001 (scale=16)
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// Тест: очень маленькое отрицательное число → должно дать -1
START_TEST(s21_floor_tiny_negative) {
  s21_decimal input = {{1, 0, 0, 0x80100000}};     // -0.0000000001
  s21_decimal expected = {{1, 0, 0, 0x80000000}};  // -1
  s21_decimal result = {{0}};
  int code = s21_floor(input, &result);
  ck_assert_int_eq(code, S21_OTHER_OK);
  for (int i = 0; i < 4; i++)
    ck_assert_uint_eq(result.bits[i], expected.bits[i]);
}
END_TEST

// ======================== SUITE CREATION ========================

Suite *s21_floor_suite(void) {
  Suite *suite = suite_create("s21_floor");

  TCase *tc_basic = tcase_create("Basic");
  tcase_add_test(tc_basic, s21_floor_basic_1);
  tcase_add_test(tc_basic, s21_floor_basic_2);
  suite_add_tcase(suite, tc_basic);

  TCase *tc_negative = tcase_create("Negative");
  tcase_add_test(tc_negative, s21_floor_negative_1);
  tcase_add_test(tc_negative, s21_floor_negative_2);
  tcase_add_test(tc_negative, s21_floor_negative_exact);  // NEW
  suite_add_tcase(suite, tc_negative);

  TCase *tc_zero = tcase_create("Zero");
  tcase_add_test(tc_zero, s21_floor_zero_1);
  tcase_add_test(tc_zero, s21_floor_zero_2);
  tcase_add_test(tc_zero, s21_floor_zero_3);
  tcase_add_test(tc_zero, s21_floor_zero_4);
  suite_add_tcase(suite, tc_zero);

  TCase *tc_edge = tcase_create("Edge Cases");
  tcase_add_test(tc_edge, s21_floor_null_test);
  suite_add_tcase(suite, tc_edge);

  TCase *tc_precision = tcase_create("Precision");
  tcase_add_test(tc_precision, s21_floor_precision_1);
  tcase_add_test(tc_precision, s21_floor_precision_2);
  tcase_add_test(tc_precision, s21_floor_precision_3);
  tcase_add_test(tc_precision, s21_floor_tiny_positive);           // NEW
  tcase_add_test(tc_precision, s21_floor_tiny_negative);           // NEW
  tcase_add_test(tc_precision, s21_floor_negative_zero_fraction);  // NEW
  suite_add_tcase(suite, tc_precision);

  TCase *tc_scale = tcase_create("Scale");
  tcase_add_test(tc_scale, s21_floor_scale_1);
  tcase_add_test(tc_scale, s21_floor_scale_2);
  suite_add_tcase(suite, tc_scale);

  // НОВАЯ КАТЕГОРИЯ: Ошибки и переполнения
  TCase *tc_errors = tcase_create("Error Handling");
  // tcase_add_test(tc_errors, s21_floor_overflow_decrease_scale); // NEW
  tcase_add_test(tc_errors, s21_floor_overflow_increase_scale);  // NEW
  tcase_add_test(tc_errors, s21_floor_overflow_add_mantissa);    // NEW
  suite_add_tcase(suite, tc_errors);

  return suite;
}