#include "mantissa_utils.h"

int is_zero(const s21_decimal *dec) {
  if (!dec) return 1;
  return (dec->bits[0] == 0u && dec->bits[1] == 0u && dec->bits[2] == 0u);
}