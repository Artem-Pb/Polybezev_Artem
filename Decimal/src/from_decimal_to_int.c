#include "decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == S21_NULL) return S21_CONVERSION_ERROR;

  *dst = 0;

  int sign = get_sign(&src);
  int scale = get_scale(&src);

  s21_decimal tmp = src;
  set_sign(&tmp, 0);

  if (scale > 0) {
    s21_internal_error_code_t st = decrease_scale(&tmp, 0);
    if (st != S21_INTERNAL_OK) {
      return S21_CONVERSION_ERROR;
    }
  }

  if (tmp.bits[1] != 0 || tmp.bits[2] != 0) {
    return S21_CONVERSION_ERROR;
  }

  uint32_t value = (uint32_t)tmp.bits[0];

  if (value > (uint32_t)2147483648) {
    return S21_CONVERSION_ERROR;
  }

  *dst = (int)value;
  if (sign) {
    if (*dst == -2147483648) {
    } else if (*dst > 0) {
      *dst = -*dst;
    }
  }

  return S21_CONVERSION_OK;
}