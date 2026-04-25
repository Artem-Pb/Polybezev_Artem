#include "scale_utils.h"

s21_internal_error_code_t normalize_scale(s21_decimal* dec1,
                                          s21_decimal* dec2) {
  if (!dec1 || !dec2) return S21_INTERNAL_NULL_POINTER;
  int sa = get_scale(dec1);
  int sb = get_scale(dec2);
  if (sa == sb) return S21_INTERNAL_OK;

  s21_decimal backup1 = *dec1;
  s21_decimal backup2 = *dec2;
  s21_internal_error_code_t st = S21_INTERNAL_OK;

  if (sa < sb) {
    for (int i = 0; i < sb - sa; ++i) {
      st = increase_scale(dec1, 1);
      if (st != S21_INTERNAL_OK) break;
    }
    if (st == S21_INTERNAL_OK) return S21_INTERNAL_OK;
    *dec1 = backup1;
    *dec2 = backup2;
    for (int i = 0; i < sb - sa; ++i) {
      int cur = get_scale(dec2);
      if (cur == 0) return S21_INTERNAL_OVERFLOW;
      st = decrease_scale(dec2, cur - 1);
      if (st != S21_INTERNAL_OK) return st;
    }
  } else {
    for (int i = 0; i < sa - sb; ++i) {
      st = increase_scale(dec2, 1);
      if (st != S21_INTERNAL_OK) break;
    }
    if (st == S21_INTERNAL_OK) return S21_INTERNAL_OK;
    *dec1 = backup1;
    *dec2 = backup2;
    for (int i = 0; i < sa - sb; ++i) {
      int cur = get_scale(dec1);
      if (cur == 0) return S21_INTERNAL_OVERFLOW;
      st = decrease_scale(dec1, cur - 1);
      if (st != S21_INTERNAL_OK) return st;
    }
  }
  return S21_INTERNAL_OK;
}
