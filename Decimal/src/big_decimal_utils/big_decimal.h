#ifndef BIG_DECIMAL_H
#define BIG_DECIMAL_H

#include <stdint.h>

#include "../decimal.h"

#define BIG_WORDS 6

typedef struct {
  uint32_t bits[BIG_WORDS];
} s21_big_decimal;

void big_clear(s21_big_decimal *dst);
void big_copy(const s21_big_decimal *src, s21_big_decimal *dst);
int big_is_zero(const s21_big_decimal *v);
int big_cmp(const s21_big_decimal *a, const s21_big_decimal *b);
int big_has_high_words(const s21_big_decimal *v);

int big_add(const s21_big_decimal *a, const s21_big_decimal *b,
            s21_big_decimal *res);
int big_sub(const s21_big_decimal *a, const s21_big_decimal *b,
            s21_big_decimal *res);
int big_mul(const s21_big_decimal *a, const s21_big_decimal *b,
            s21_big_decimal *res);
int big_mul_small(const s21_big_decimal *a, s21_big_decimal *res, uint32_t m);
int big_add_small(s21_big_decimal *a, uint32_t add);

int big_divmod(const s21_big_decimal *dividend, const s21_big_decimal *divisor,
               s21_big_decimal *quotient, s21_big_decimal *remainder);

int big_to_decimal(const s21_big_decimal *src, int scale, int sign,
                   s21_decimal *dst);

#endif