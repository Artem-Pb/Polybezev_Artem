#include "decimal.h"

int s21_sub(s21_decimal v1, s21_decimal v2, s21_decimal *res) {
  if (!res) return 1;
  clear_decimal(res);
  normalize_scale(&v1, &v2);
  set_sign(&v2, !get_sign(&v2));
  return s21_add(v1, v2, res);
}