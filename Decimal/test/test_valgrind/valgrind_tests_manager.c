#include "valgrind_test.h"

void decimal_init(s21_decimal* src, const int bits_0, const int bits_1,
                  const int bits_2, const unsigned int scale, const int sign) {
  clear_decimal(src);
  src->bits[0] = bits_0;
  src->bits[1] = bits_1;
  src->bits[2] = bits_2;

  set_scale(src, scale);

  if ((sign == 1) || sign < 0)
    set_sign(src, sign);
  else
    set_sign(src, 0);
}

void compare_func_test(const s21_decimal left, const s21_decimal rigth) {
  s21_is_equal(left, rigth);
  s21_is_greater(left, rigth);
  s21_is_greater_or_equal(left, rigth);
  s21_is_less(left, rigth);
  s21_is_not_equal(left, rigth);
}

void convert_func_test() {
  s21_decimal static_dec;
  decimal_init(&static_dec, 0, 0, 0, 0, 0);
  int int_src = 6574543;
  s21_from_int_to_decimal(int_src, &static_dec);
  decimal_init(&static_dec, 1234564, 0, 0, 0, 0);
  int int_ptr = 0;
  s21_from_decimal_to_int(static_dec, &int_ptr);
  decimal_init(&static_dec, 0, 0, 0, 0, 0);
  float fl_src = 45.678;
  s21_from_float_to_decimal(fl_src, &static_dec);
  fl_src = 0;
  s21_from_decimal_to_float(static_dec, &fl_src);
}

void arithmetic_func_test() {
  s21_decimal value_1;
  s21_decimal value_2;
  s21_decimal result;
  decimal_init(&value_1, 7564834, 3453453, 34535, 28, 0);
  decimal_init(&value_2, 123456, 345353, 3453, 27, 0);
  decimal_init(&result, 0, 0, 0, 0, 0);
  s21_add(value_1, value_2, &result);
  clear_decimal(&result);
  s21_mul(value_1, value_2, &result);
  clear_decimal(&result);
  s21_sub(value_1, value_2, &result);
  clear_decimal(&value_2);
  clear_decimal(&result);
  s21_sub(value_1, value_2, &result);
}

void other_func_test() {
  s21_decimal value;
  s21_decimal result;
  decimal_init(&value, 123456, 345353, 3453, 27, 0);
  decimal_init(&result, 0, 0, 0, 0, 0);

  s21_negate(value, &result);

  clear_decimal(&result);
  s21_truncate(value, &result);

  clear_decimal(&result);
  s21_round(value, &result);

  clear_decimal(&result);
  s21_floor(value, &result);
}