#include "decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (result == S21_NULL) return S21_OTHER_ERROR;
  clear_decimal(result);
  *result = value;

  int cur_scale = get_scale(result);
  if (cur_scale == 0) {
    return S21_OTHER_OK;
  }
  s21_internal_error_code_t st = decrease_scale(result, 0);
  if (st != S21_INTERNAL_OK) {
    clear_decimal(result);
    return S21_OTHER_ERROR;
  }

  set_scale(result, 0);
  return S21_OTHER_OK;
}