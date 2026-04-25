#include "decimal.h"

int s21_round(s21_decimal value, s21_decimal* result) {
  if (result == S21_NULL) return S21_OTHER_ERROR;
  clear_decimal(result);
  int sign = get_sign(&value);
  set_sign(&value, 0);
  *result = value;
  int cur_scale = get_scale(&value);
  if (cur_scale == 0) {
    set_sign(result, sign);
    return S21_OTHER_OK;
  }

  s21_decimal tmp = *result;
  for (int i = 0; i < cur_scale - 1; i++) {
    local_divide_mantissa_by_10(&tmp);
  }
  unsigned int last_digit = tmp.bits[0] % 10;

  for (int i = 0; i < cur_scale; i++) {
    local_divide_mantissa_by_10(result);
  }

  if (last_digit >= 5) {
    s21_decimal one = {{1, 0, 0, 0}};
    s21_decimal new_res = {{0}};
    if (add_mantissa(result, &one, &new_res) != S21_INTERNAL_OK) {
      clear_decimal(result);
      return S21_OTHER_ERROR;
    }
    *result = new_res;
  }

  set_scale(result, 0);
  set_sign(result, sign);
  return S21_OTHER_OK;
}