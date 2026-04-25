#include "decimal.h"

int s21_mul(s21_decimal v1, s21_decimal v2, s21_decimal *res) {
  if (!res) return 1;
  clear_decimal(res);
  int sign = get_sign(&v1) ^ get_sign(&v2);
  int scale = get_scale(&v1) + get_scale(&v2);
  if ((v1.bits[0] == 0 && v1.bits[1] == 0 && v1.bits[2] == 0) ||
      (v2.bits[0] == 0 && v2.bits[1] == 0 && v2.bits[2] == 0)) {
    set_sign(res, sign);
    return 0;
  }

  s21_big_decimal a = {{0}}, b = {{0}}, r = {{0}};
  a.bits[0] = v1.bits[0];
  a.bits[1] = v1.bits[1];
  a.bits[2] = v1.bits[2];
  b.bits[0] = v2.bits[0];
  b.bits[1] = v2.bits[1];
  b.bits[2] = v2.bits[2];

  big_mul(&a, &b, &r);

  while (scale > 28) {
    unsigned long long rem = 0;
    for (int i = BIG_WORDS - 1; i >= 0; i--) {
      unsigned long long cur = (rem << 32) | r.bits[i];
      r.bits[i] = (uint32_t)(cur / 10ULL);
      rem = cur % 10ULL;
    }
    if (rem > 5 || (rem == 5 && (r.bits[0] & 1))) {
      big_add_small(&r, 1);
    }
    scale--;
  }

  if (big_to_decimal(&r, scale, sign, res)) return sign ? 2 : 1;
  return 0;
}