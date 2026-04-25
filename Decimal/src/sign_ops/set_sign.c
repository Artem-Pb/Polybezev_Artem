#include <stdint.h>

#include "sign_ops.h"

void set_sign(s21_decimal *dec, int sign) {
  if (!dec) return;
  uint32_t *bits3 = (uint32_t *)&dec->bits[3];
  if (sign)
    *bits3 |= 0x80000000u;
  else
    *bits3 &= ~0x80000000u;
}