#include "decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == S21_NULL) return S21_CONVERSION_ERROR;

  clear_decimal(dst);

  if (src < 0) {
    set_sign(dst, 1);
  }

  unsigned int abs_value = (src == -2147483648) ? ((unsigned int)2147483647 + 1)
                                                : (src < 0 ? -src : src);

  dst->bits[0] = abs_value;

  return S21_CONVERSION_OK;
}