#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decimal.h"

#define MAX_SCALE 28
#define DECIMAL_MAX 79228162514264337593543950335.0

static int float_to_decimal_core(float src, uint32_t bits[3], int *scale,
                                 int *sign) {
  if (isnan(src) || isinf(src)) return S21_INTERNAL_CONVERSION_ERROR;

  *sign = src < 0 ? 1 : 0;
  double val = fabs((double)src);

  if (val > 0 && val < 1e-28) {
    bits[0] = 0;
    bits[1] = 0;
    bits[2] = 0;
    *scale = 0;
    *sign = 0;
    return S21_INTERNAL_CONVERSION_ERROR;
  }

  if (val > DECIMAL_MAX) {
    return S21_INTERNAL_CONVERSION_ERROR;
  }

  if (val != 0) {
    char buffer[32];
    sprintf(buffer, "%.7g", val);
    val = strtod(buffer, NULL);
  }

  int sc = 0;
  double tmp = val;

  while (sc <= MAX_SCALE) {
    double rounded = round(tmp);
    double diff = fabs(tmp - rounded);

    if (diff < 1e-9 || (tmp > 0 && diff / tmp < 1e-9)) {
      tmp = rounded;
      break;
    }
    tmp *= 10.0;
    sc++;
  }

  if (sc > MAX_SCALE) {
    return S21_INTERNAL_CONVERSION_ERROR;
  }

  *scale = sc;

  if (tmp > DECIMAL_MAX) return S21_INTERNAL_CONVERSION_ERROR;

  unsigned long long num = (unsigned long long)tmp;

  bits[0] = (uint32_t)(num & 0xFFFFFFFFULL);
  bits[1] = (uint32_t)((num >> 32) & 0xFFFFFFFFULL);
  bits[2] = 0;

  return S21_INTERNAL_OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst) return S21_CONVERSION_ERROR;

  clear_decimal(dst);

  uint32_t core[3] = {0};
  int scale = 0;
  int sign = 0;

  int status = float_to_decimal_core(src, core, &scale, &sign);
  if (status != S21_CONVERSION_OK) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    return S21_CONVERSION_ERROR;
  }

  uint32_t bit_src;
  s21_memcpy(&bit_src, &src, sizeof(float));
  int try_sing = bit_src >> 31;

  dst->bits[0] = core[0];
  dst->bits[1] = core[1];
  dst->bits[2] = core[2];
  set_scale(dst, scale);

  if (try_sing) set_sign(dst, 1);

  return S21_CONVERSION_OK;
}