#include "decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result == S21_NULL) {
    return S21_OTHER_ERROR;
  }
  clear_decimal(result);
  *result = value;

  int current_scale = get_scale(result);

  if (current_scale == 0) {
    set_scale(result, 0);
    return S21_OTHER_OK;
  }

  int sign = get_sign(result);

  s21_internal_error_code_t internal_status = decrease_scale(result, 0);

  if (internal_status != S21_INTERNAL_OK) {
    clear_decimal(result);
    return S21_OTHER_ERROR;
  }

  if (sign == 1) {
    s21_decimal rebuilt = *result;
    if (increase_scale(&rebuilt, current_scale) != S21_INTERNAL_OK) {
      clear_decimal(result);
      return S21_OTHER_ERROR;
    }

    if (compare_mantissa(&rebuilt, &value) != 0) {
      s21_decimal abs_truncated = *result;
      set_sign(&abs_truncated, 0);
      s21_decimal one = {{1, 0, 0, 0}};
      s21_decimal inc_result = {{0}};
      if (add_mantissa(&abs_truncated, &one, &inc_result) != S21_INTERNAL_OK) {
        clear_decimal(result);
        return S21_OTHER_ERROR;
      }
      *result = inc_result;
      set_sign(result, 1);
    } else {
      set_sign(result, 1);
    }
  }

  set_scale(result, 0);
  return S21_OTHER_OK;
}