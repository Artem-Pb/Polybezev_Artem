#include "scale_utils.h"

int get_scale(const s21_decimal *dec) {
  if (!dec) return 0;
  uint32_t bits3 = (uint32_t)dec->bits[3];
  return (int)((bits3 >> 16) & 0xFFu);
}