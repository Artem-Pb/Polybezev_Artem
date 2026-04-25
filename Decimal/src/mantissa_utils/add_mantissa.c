#include "mantissa_utils.h"

s21_internal_error_code_t add_mantissa(s21_decimal* dec1, s21_decimal* dec2,
                                       s21_decimal* result) {
  if (dec1 == S21_NULL || dec2 == S21_NULL || result == S21_NULL)
    return S21_INTERNAL_NULL_POINTER;

  clear_decimal(result);

  unsigned long long carry = 0ULL;
  for (int i = 0; i < 3; ++i) {
    unsigned long long a = dec1->bits[i];
    unsigned long long b = dec2->bits[i];
    unsigned long long sum = a + b + carry;
    result->bits[i] = sum & 0xFFFFFFFFu;
    carry = sum >> 32;
  }

  if (carry) {
    clear_decimal(result);
    return S21_INTERNAL_OVERFLOW;
  }

  return S21_INTERNAL_OK;
}