#ifndef BIT_UTILS
#define BIT_UTILS

#include "../decimal.h"

/**
 * @brief Clears all bits of an s21_decimal, setting it to zero.
 *
 * Sets all elements of dec->bits[] to 0.
 *
 * @param dec Pointer to the s21_decimal to clear.
 */
void clear_decimal(s21_decimal* dec);

#endif