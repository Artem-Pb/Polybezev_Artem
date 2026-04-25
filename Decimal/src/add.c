#include "decimal.h"

int s21_add(s21_decimal v1, s21_decimal v2, s21_decimal *res) {
  if (!res) return 1;
  clear_decimal(res);
  normalize_scale(&v1, &v2);

  int s1 = get_sign(&v1);
  int s2 = get_sign(&v2);

  s21_big_decimal a = {{0}}, b = {{0}}, r = {{0}};
  a.bits[0] = v1.bits[0];
  a.bits[1] = v1.bits[1];
  a.bits[2] = v1.bits[2];
  b.bits[0] = v2.bits[0];
  b.bits[1] = v2.bits[1];
  b.bits[2] = v2.bits[2];

  int sign = 0;
  if (s1 == s2) {
    big_add(&a, &b, &r);
    sign = s1;
  } else {
    if (big_cmp(&a, &b) >= 0) {
      big_sub(&a, &b, &r);
      sign = s1;
    } else {
      big_sub(&b, &a, &r);
      sign = s2;
    }
  }

  int scale = get_scale(&v1);
  if (big_to_decimal(&r, scale, sign, res)) return sign ? 2 : 1;
  return 0;
}