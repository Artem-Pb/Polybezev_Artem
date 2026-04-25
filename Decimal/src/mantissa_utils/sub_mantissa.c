#include "mantissa_utils.h"

s21_internal_error_code_t sub_mantissa(const s21_decimal *dec1,
                                       const s21_decimal *dec2,
                                       s21_decimal *result) {
  if (!dec1 || !dec2 || !result) return S21_INTERNAL_NULL_POINTER;
  clear_decimal(result);
  unsigned long long borrow = 0ULL;
  for (int i = 0; i < 3; ++i) {
    unsigned long long av = dec1->bits[i];
    unsigned long long bv = dec2->bits[i];
    unsigned long long sub = av - bv - borrow;
    if (av < bv + borrow) {
      result->bits[i] = ((1ULL << 32) + av - bv - borrow);
      borrow = 1ULL;
    } else {
      result->bits[i] = (sub & 0xFFFFFFFFu);
      borrow = 0ULL;
    }
  }
  if (borrow) {
    clear_decimal(result);
    return S21_INTERNAL_OVERFLOW;
  }
  return S21_INTERNAL_OK;
}