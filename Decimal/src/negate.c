#include "decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == S21_NULL) return S21_OTHER_ERROR;
  clear_decimal(result);
  *result = value;
  int sign = get_sign(&value);
  set_sign(result, !sign);
  return S21_OTHER_OK;
}