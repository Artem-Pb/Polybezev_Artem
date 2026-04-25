#include "bit_utils.h"

void clear_decimal(s21_decimal *dec) {
  if (!dec) return;
  dec->bits[0] = dec->bits[1] = dec->bits[2] = dec->bits[3] = 0;
}