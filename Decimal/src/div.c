
#include <stdint.h>
#include <string.h>

#include "big_decimal_utils/big_decimal.h"
#include "decimal.h"

#define DIV_OK 0
#define DIV_OVF 1
#define DIV_UNDER 2
#define DIV_BY_ZERO 3

#ifndef SCALE_MAX
#define SCALE_MAX 28
#endif

static void decimal_to_big(const s21_decimal *d, s21_big_decimal *out) {
  big_clear(out);
  out->bits[0] = d->bits[0];
  out->bits[1] = d->bits[1];
  out->bits[2] = d->bits[2];
}

static void big_to_decimal_mantissa(const s21_big_decimal *big,
                                    s21_decimal *d) {
  d->bits[0] = big->bits[0];
  d->bits[1] = big->bits[1];
  d->bits[2] = big->bits[2];
}

static int decimal_mul10_inplace(s21_decimal *d) {
  int scale = get_scale(d);
  if (scale >= SCALE_MAX) return 1;

  s21_big_decimal src, res;
  decimal_to_big(d, &src);
  big_clear(&res);

  if (big_mul_small(&src, &res, 10u) != 0) {
    return 1;
  }

  if (res.bits[3] || res.bits[4] || res.bits[5]) return 1;

  big_to_decimal_mantissa(&res, d);
  set_scale(d, scale + 1);
  return 0;
}

static int decimal_div10_bank_inplace(s21_decimal *d) {
  int scale = get_scale(d);
  if (scale <= 0) return 1;

  s21_big_decimal v;
  decimal_to_big(d, &v);

  unsigned long long rem = 0;
  for (int i = 5; i >= 0; --i) {
    unsigned long long cur = (rem << 32) | (unsigned long long)v.bits[i];
    uint32_t q = (uint32_t)(cur / 10ULL);
    uint32_t r = (uint32_t)(cur % 10ULL);
    v.bits[i] = q;
    rem = r;
  }

  if (rem > 5 || (rem == 5 && (v.bits[0] & 1u))) {
    big_add_small(&v, 1u);
  }

  s21_decimal out = {{0, 0, 0, 0}};
  out.bits[0] = v.bits[0];
  out.bits[1] = v.bits[1];
  out.bits[2] = v.bits[2];
  set_scale(&out, scale - 1);
  set_sign(&out, get_sign(d));
  *d = out;
  return 0;
}

static int decimal_is_zero_mantissa(const s21_decimal *d) {
  return (d->bits[0] == 0 && d->bits[1] == 0 && d->bits[2] == 0);
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return DIV_OVF;
  clear_decimal(result);

  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    return DIV_BY_ZERO;
  }

  int sign1 = get_sign(&value_1);
  int sign2 = get_sign(&value_2);
  int result_sign = sign1 ^ sign2;

  s21_decimal A = value_1;
  s21_decimal B = value_2;
  set_sign(&A, 0);
  set_sign(&B, 0);

  if (decimal_is_zero_mantissa(&A)) {
    clear_decimal(result);
    return DIV_OK;
  }

  int scA = get_scale(&A);
  int scB = get_scale(&B);

  int guard = 0;
  while (scA != scB && guard < 100) {
    guard++;
    if (scA < scB) {
      if (scA < SCALE_MAX) {
        if (decimal_mul10_inplace(&A) == 0) {
          scA++;
          continue;
        } else {
          if (scB > 0) {
            decimal_div10_bank_inplace(&B);
            scB--;
            continue;
          } else {
            break;
          }
        }
      } else {
        if (scB > 0) {
          decimal_div10_bank_inplace(&B);
          scB--;
          continue;
        } else
          break;
      }
    } else {
      if (scB < SCALE_MAX) {
        if (decimal_mul10_inplace(&B) == 0) {
          scB++;
          continue;
        } else {
          if (scA > 0) {
            decimal_div10_bank_inplace(&A);
            scA--;
            continue;
          } else
            break;
        }
      } else {
        if (scA > 0) {
          decimal_div10_bank_inplace(&A);
          scA--;
          continue;
        } else
          break;
      }
    }
  }

  s21_big_decimal bigA, bigB;
  big_clear(&bigA);
  big_clear(&bigB);
  decimal_to_big(&A, &bigA);
  decimal_to_big(&B, &bigB);

  s21_big_decimal q_big, r_big;
  big_clear(&q_big);
  big_clear(&r_big);

  int divmod_ret = big_divmod(&bigA, &bigB, &q_big, &r_big);
  if (divmod_ret != 0) {
    return result_sign ? DIV_UNDER : DIV_OVF;
  }

  s21_big_decimal q_work;
  big_copy(&q_big, &q_work);

  s21_big_decimal r_work;
  big_copy(&r_big, &r_work);

  int max_generate = SCALE_MAX + 1;
  int actual_generated = 0;

  s21_big_decimal tmp_mul, tmp_digit, tmp_rem;
  for (int i = 0; i < max_generate; ++i) {
    if (big_is_zero(&r_work)) break;

    big_mul_small(&r_work, &tmp_mul, 10u);

    big_divmod(&tmp_mul, &bigB, &tmp_digit, &tmp_rem);

    big_mul_small(&q_work, &tmp_mul, 10u);
    big_copy(&tmp_mul, &q_work);
    big_add_small(&q_work, tmp_digit.bits[0]);

    big_copy(&tmp_rem, &r_work);

    actual_generated++;
  }

  if (actual_generated == 0) {
    int pack = big_to_decimal(&q_work, 0, result_sign, result);
    return pack;
  }

  int result_scale = actual_generated;
  int pack_code = big_to_decimal(&q_work, result_scale, result_sign, result);
  return pack_code;
}