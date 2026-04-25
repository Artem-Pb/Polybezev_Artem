#include "decimal.h"

int s21_compare_worker(s21_decimal a, s21_decimal b) {
  int result = 0;

  int is_zero_a = (a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0);
  int is_zero_b = (b.bits[0] == 0 && b.bits[1] == 0 && b.bits[2] == 0);

  if (is_zero_a && is_zero_b) {
    result = 0;
  } else if (is_zero_a) {
    result = ((b.bits[3] & 0x80000000) != 0) ? +1 : -1;
  } else if (is_zero_b) {
    result = ((a.bits[3] & 0x80000000) != 0) ? -1 : +1;
  } else {
    int sign_a = (a.bits[3] & 0x80000000) != 0;
    int sign_b = (b.bits[3] & 0x80000000) != 0;

    if (!sign_a && sign_b) {
      result = +1;
    } else if (sign_a && !sign_b) {
      result = -1;
    } else {
      s21_decimal temp_a = a;
      s21_decimal temp_b = b;

      s21_internal_error_code_t status = normalize_scale(&temp_a, &temp_b);
      if (status != S21_INTERNAL_OK) {
        result = 0;
      } else {
        temp_a.bits[3] &= 0x0000FFFF;
        temp_b.bits[3] &= 0x0000FFFF;

        int cmp = s21_memcmp(&temp_a, &temp_b, sizeof(s21_decimal));

        if (cmp == 0) {
          result = 0;
        } else if (!sign_a) {
          result = (cmp > 0) ? +1 : -1;
        } else {
          result = (cmp > 0) ? -1 : +1;
        }
      }
    }
  }
  return result;
}