#include "scale_utils.h"

s21_internal_error_code_t increase_scale(s21_decimal *dec, int target_scale) {
  if (!dec) return S21_INTERNAL_NULL_POINTER;

  int current_scale = get_scale(dec);

  if (current_scale + target_scale > SCALE_MAX) {
    return S21_INTERNAL_OVERFLOW;
  }

  for (int t = 0; t < target_scale; ++t) {
    uint32_t *m = (uint32_t *)dec->bits;
    unsigned long long carry = 0;

    for (int i = 0; i < 3; i++) {
      unsigned long long product = ((unsigned long long)m[i]) * 10ULL + carry;
      m[i] = (uint32_t)(product & 0xFFFFFFFFU);
      carry = product >> 32;
    }

    if (carry != 0) {
      return S21_INTERNAL_OVERFLOW;
    }

    set_scale(dec, get_scale(dec) + 1);
  }

  return S21_INTERNAL_OK;
}