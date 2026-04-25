#include "scale_utils.h"

s21_internal_error_code_t decrease_scale(s21_decimal* dec, int target_scale) {
  if (!dec || target_scale < 0 || target_scale > SCALE_MAX) {
    return S21_INTERNAL_CONVERSION_ERROR;
  }
  int current_scale = get_scale(dec);
  if (target_scale > current_scale) {
    return S21_INTERNAL_CONVERSION_ERROR;
  }

  int diff = current_scale - target_scale;
  if (diff == 0) {
    return S21_INTERNAL_OK;
  }

  uint32_t* m = (uint32_t*)dec->bits;

  for (int i = 0; i < diff; i++) {
    unsigned long long temp = 0;
    unsigned int remainder_before_div = 0;

    for (int w = 2; w >= 0; w--) {
      temp = ((unsigned long long)remainder_before_div << 32) | m[w];
      remainder_before_div = (unsigned int)(temp % 10);
    }

    s21_internal_error_code_t div_status = local_divide_mantissa_by_10(dec);
    if (div_status != S21_INTERNAL_OK) {
      return S21_INTERNAL_CALCULATION_ERROR;
    }
  }

  set_scale(dec, target_scale);
  return S21_INTERNAL_OK;
}

s21_internal_error_code_t local_divide_mantissa_by_10(s21_decimal* dec) {
  if (!dec) return S21_INTERNAL_NULL_POINTER;

  uint32_t* m = (uint32_t*)dec->bits;
  unsigned long long remainder = 0;
  unsigned long long dividend = 0;

  for (int i = 2; i >= 0; i--) {
    dividend = ((unsigned long long)remainder << 32) | m[i];
    uint32_t quotient = (uint32_t)(dividend / 10);
    remainder = dividend % 10;
    m[i] = quotient;
  }

  return S21_INTERNAL_OK;
}