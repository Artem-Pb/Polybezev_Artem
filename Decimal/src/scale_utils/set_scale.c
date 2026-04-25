#include "scale_utils.h"

void set_scale(s21_decimal *dec, int scale) {
  if (!dec) return;
  unsigned int bits3 = dec->bits[3];
  bits3 &= ~(0xFFu << 16);
  bits3 |= ((scale & 0xFFu) << 16);
  dec->bits[3] = (int)bits3;
}