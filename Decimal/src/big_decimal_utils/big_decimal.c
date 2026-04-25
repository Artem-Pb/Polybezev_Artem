#include "big_decimal.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef SCALE_MAX
#define SCALE_MAX 28
#endif

void big_clear(s21_big_decimal *dst) {
  if (!dst) return;
  memset(dst->bits, 0, sizeof(dst->bits));
}

void big_copy(const s21_big_decimal *src, s21_big_decimal *dst) {
  if (!src || !dst) return;
  memcpy(dst->bits, src->bits, sizeof(src->bits));
}

int big_is_zero(const s21_big_decimal *v) {
  if (!v) return 1;
  for (int i = 0; i < BIG_WORDS; ++i)
    if (v->bits[i]) return 0;
  return 1;
}

int big_has_high_words(const s21_big_decimal *v) {
  if (!v) return 0;
  return (v->bits[3] != 0) || (v->bits[4] != 0) || (v->bits[5] != 0);
}

int big_cmp(const s21_big_decimal *a, const s21_big_decimal *b) {
  for (int i = BIG_WORDS - 1; i >= 0; --i) {
    uint32_t wa = a->bits[i];
    uint32_t wb = b->bits[i];
    if (wa > wb) return 1;
    if (wa < wb) return -1;
  }
  return 0;
}

int big_add(const s21_big_decimal *a, const s21_big_decimal *b,
            s21_big_decimal *res) {
  if (!a || !b || !res) return 1;
  unsigned long long carry = 0ULL;
  for (int i = 0; i < BIG_WORDS; ++i) {
    unsigned long long sum =
        (unsigned long long)a->bits[i] + (unsigned long long)b->bits[i] + carry;
    res->bits[i] = (uint32_t)(sum & 0xFFFFFFFFu);
    carry = sum >> 32;
  }
  return carry ? 1 : 0;
}

int big_sub(const s21_big_decimal *a, const s21_big_decimal *b,
            s21_big_decimal *res) {
  if (!a || !b || !res) return 1;
  long long borrow = 0;
  for (int i = 0; i < BIG_WORDS; ++i) {
    long long aa = (long long)(uint32_t)a->bits[i];
    long long bb = (long long)(uint32_t)b->bits[i];
    long long val = aa - bb - borrow;
    if (val < 0) {
      val += (1LL << 32);
      borrow = 1;
    } else {
      borrow = 0;
    }
    res->bits[i] = (uint32_t)(val & 0xFFFFFFFFu);
  }
  return borrow ? 1 : 0;
}

int big_mul(const s21_big_decimal *a, const s21_big_decimal *b,
            s21_big_decimal *res) {
  if (!a || !b || !res) return 1;
  unsigned long long tmp[12] = {0};

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      unsigned long long mul =
          (unsigned long long)a->bits[i] * (unsigned long long)b->bits[j];
      tmp[i + j] += mul;

      for (int k = i + j; k < 11 && tmp[k] > 0xFFFFFFFFULL; ++k) {
        unsigned long long carry = tmp[k] >> 32;
        tmp[k] &= 0xFFFFFFFFULL;
        tmp[k + 1] += carry;
      }
    }
  }

  for (int i = 0; i < BIG_WORDS; ++i)
    res->bits[i] = (uint32_t)(tmp[i] & 0xFFFFFFFFULL);

  for (int i = BIG_WORDS; i < 12; ++i) {
    if (tmp[i] != 0ULL) return 1;
  }
  return 0;
}

int big_mul_small(const s21_big_decimal *a, s21_big_decimal *res, uint32_t m) {
  if (!a || !res) return 1;
  unsigned long long carry = 0ULL;
  for (int i = 0; i < BIG_WORDS; ++i) {
    unsigned long long prod =
        (unsigned long long)a->bits[i] * (unsigned long long)m + carry;
    res->bits[i] = (uint32_t)(prod & 0xFFFFFFFFu);
    carry = prod >> 32;
  }
  return carry ? 1 : 0;
}

int big_add_small(s21_big_decimal *a, uint32_t add) {
  if (!a) return 1;
  unsigned long long carry = add;
  for (int i = 0; i < BIG_WORDS && carry; ++i) {
    unsigned long long sum = (unsigned long long)a->bits[i] + carry;
    a->bits[i] = (uint32_t)(sum & 0xFFFFFFFFu);
    carry = sum >> 32;
  }
  return carry ? 1 : 0;
}

int big_divmod(const s21_big_decimal *dividend, const s21_big_decimal *divisor,
               s21_big_decimal *q, s21_big_decimal *r) {
  if (!dividend || !divisor || !q || !r) return 1;
  if (big_is_zero(divisor)) return 1;

  big_clear(q);
  big_clear(r);

  s21_big_decimal cur;
  big_clear(&cur);

  for (int bit = BIG_WORDS * 32 - 1; bit >= 0; --bit) {
    unsigned long long carry = 0ULL;
    for (int i = 0; i < BIG_WORDS; ++i) {
      unsigned long long val = ((unsigned long long)cur.bits[i] << 1) | carry;
      cur.bits[i] = (uint32_t)(val & 0xFFFFFFFFULL);
      carry = (val >> 32) & 0xFFFFFFFFULL;
    }

    int w = bit / 32;
    int off = bit % 32;
    if ((dividend->bits[w] >> off) & 1u) {
      cur.bits[0] |= 1u;
    }
    if (big_cmp(&cur, divisor) >= 0) {
      s21_big_decimal tmp;
      big_sub(&cur, divisor, &tmp);
      big_copy(&tmp, &cur);

      q->bits[w] |= (1u << off);
    }
  }
  big_copy(&cur, r);
  return 0;
}

static void divide_by_10_with_remainder(s21_big_decimal *v,
                                        uint32_t *remainder) {
  unsigned long long rem = 0;
  for (int i = BIG_WORDS - 1; i >= 0; --i) {
    unsigned long long cur = (rem << 32) | (unsigned long long)v->bits[i];
    uint32_t q = (uint32_t)(cur / 10ULL);
    uint32_t r = (uint32_t)(cur % 10ULL);
    v->bits[i] = q;
    rem = r;
  }
  if (remainder) *remainder = (uint32_t)rem;
}

int big_to_decimal(const s21_big_decimal *src, int scale, int sign,
                   s21_decimal *dst) {
  if (!src || !dst) return S21_ARITHMETIC_OVERFLOW;

  s21_big_decimal v;
  big_copy(src, &v);

  while (scale > SCALE_MAX) {
    uint32_t rem = 0;
    divide_by_10_with_remainder(&v, &rem);

    if (rem > 5 || (rem == 5 && (v.bits[0] & 1u))) {
      big_add_small(&v, 1u);
    }
    scale--;
  }

  while (big_has_high_words(&v) && scale > 0) {
    uint32_t rem = 0;
    divide_by_10_with_remainder(&v, &rem);
    if (rem > 5 || (rem == 5 && (v.bits[0] & 1u))) {
      big_add_small(&v, 1u);
    }
    scale--;
  }

  if (big_has_high_words(&v)) {
    return sign ? S21_ARITHMETIC_UNDERFLOW : S21_ARITHMETIC_OVERFLOW;
  }

  s21_decimal out = {{0, 0, 0, 0}};
  out.bits[0] = v.bits[0];
  out.bits[1] = v.bits[1];
  out.bits[2] = v.bits[2];
  set_scale(&out, scale);
  set_sign(&out, sign);
  *dst = out;
  return S21_ARITHMETIC_OK;
}