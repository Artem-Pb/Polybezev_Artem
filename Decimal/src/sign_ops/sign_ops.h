#ifndef S21_SIGN_OPS_H
#define S21_SIGN_OPS_H

#include "../decimal.h"

/**
 * @brief Gets the sign bit of an s21_decimal.
 *
 * The sign is determined by bit 31 of bits[3]. 0 indicates positive, 1
 * indicates negative.
 *
 * @param decimal Pointer to the s21_decimal.
 * @return int 0 for positive, 1 for negative.
 * @retval 0 The number is positive or zero.
 * @retval 1 The number is negative.
 */
int get_sign(const s21_decimal* decimal);

/**
 * @brief Sets the sign bit of an s21_decimal.
 *
 * Modifies bit 31 of bits[3]. Does not change the mantissa or scale.
 *
 * @param decimal Pointer to the s21_decimal to modify.
 * @param sign The sign to set. 0 for positive, 1 for negative.
 */
void set_sign(s21_decimal* decimal, int sign);

#endif