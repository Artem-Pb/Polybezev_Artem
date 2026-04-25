#include "mantissa_utils.h"

int compare_mantissa(const s21_decimal *dec1, const s21_decimal *dec2) {
  if (!dec1 || !dec2) return 0;
  unsigned int wa0 = dec1->bits[0];
  unsigned int wa1 = dec1->bits[1];
  unsigned int wa2 = dec1->bits[2];
  unsigned int wb0 = dec2->bits[0];
  unsigned int wb1 = dec2->bits[1];
  unsigned int wb2 = dec2->bits[2];
  if (wa2 != wb2) return (wa2 > wb2) ? 1 : -1;
  if (wa1 != wb1) return (wa1 > wb1) ? 1 : -1;
  if (wa0 != wb0) return (wa0 > wb0) ? 1 : -1;
  return 0;
}