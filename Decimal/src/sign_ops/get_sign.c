#include "sign_ops.h"

int get_sign(const s21_decimal *dec) {
  if (!dec) return 0;
  return ((uint32_t)dec->bits[3] & 0x80000000u) != 0;
}