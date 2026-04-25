#include <math.h>

#include "decimal.h"
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == S21_NULL) return S21_CONVERSION_ERROR;
  *dst = 0.0f;
  s21_decimal tmp_src = src;
  int scale = get_scale(&tmp_src);
  int sign = get_sign(&tmp_src);

  if (is_zero(&tmp_src)) {
    *dst = sign ? -0.0f : 0.0f;
    return S21_CONVERSION_OK;
  }

  double mantissa = 0.0;
  double multiplier = 1.0;

  for (int i = 0; i < 3; i++) {
    mantissa += (double)((unsigned int)tmp_src.bits[i]) * multiplier;
    multiplier *= 4294967296.0;
  }

  double scale_divisor = 1.0;
  for (int i = 0; i < scale; i++) {
    scale_divisor *= 10.0;
  }

  double result = mantissa / scale_divisor;

  if (sign) {
    result = -result;
  }

  *dst = (float)result;
  return S21_CONVERSION_OK;
}