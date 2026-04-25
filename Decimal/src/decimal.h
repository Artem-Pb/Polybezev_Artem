#ifndef DECIMAL_H
#define DECIMAL_H

#include <stdint.h>

typedef struct {
  int bits[4];
} s21_decimal;

#include "big_decimal_utils/big_decimal.h"
#include "bit_utils/bit_utils.h"
#include "common_utils/common_utils.h"
#include "mantissa_utils/mantissa_utils.h"
#include "mem_utils/mem.h"
#include "types/types.h"
#include "scale_utils/scale_utils.h"
#include "sign_ops/sign_ops.h"

typedef enum {
  S21_ARITHMETIC_OK = 0,
  S21_ARITHMETIC_OVERFLOW = 1,
  S21_ARITHMETIC_UNDERFLOW = 2,
  S21_ARITHMETIC_DIV_BY_ZERO = 3
} s21_arithmetic_result_t;

typedef enum {
  S21_COMPARISON_FALSE = 0,
  S21_COMPARISON_TRUE = 1
} s21_comparison_result_t;

typedef enum {
  S21_CONVERSION_OK = 0,
  S21_CONVERSION_ERROR = 1
} s21_conversion_result_t;

typedef enum { S21_OTHER_OK = 0, S21_OTHER_ERROR = 1 } s21_other_result_t;

/**
 * @brief Addition two s21_decimal numbers\n
 * @brief operator can be only '+'
 * @param value_1 First operand.
 * @param value_2 Second operand.
 * @param result pointer to s21_decimal result variable
 * @return The error code
 * @retval 0 if addition if OK
 * @retval 1 if the number is too large or equal to infinity.
 * @retval 2 if the number is too small or equal to negative infinity.
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * @brief Subtraction two s21_decimal numbers\n
 * @brief operator can be only '-'
 * @param value_1 First operand.
 * @param value_2 Second operand.
 * @param result pointer to s21_decimal result variable
 * @return The error code
 * @retval 0 if subtraction if OK
 * @retval 1 if the number is too large or equal to infinity.
 * @retval 2 if the number is too small or equal to negative infinity.
 */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * @brief Multiplication two s21_decimal numbers\n
 * @brief operator can be only '-'
 * @param value_1 First operand.
 * @param value_2 Second operand.
 * @param result pointer to s21_decimal result variable
 * @return The error code
 * @retval 0 if multiplication if OK
 * @retval 1 if the number is too large or equal to infinity.
 * @retval 2 if the number is too small or equal to negative infinity.
 */
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * @brief Division two s21_decimal numbers\n
 * @brief operator can be only '-'
 * @param value_1 First operand.
 * @param value_2 Second operand.
 * @param result pointer to s21_decimal result variable
 * @return The error code
 * @retval 0 if division if OK
 * @retval 1 if the number is too large or equal to infinity.
 * @retval 2 if the number is too small or equal to negative infinity.
 * @retval 3 if division by 0
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/**
 * @brief Compare two s21_decimal numbers.
 * @param operand_1 First operand.
 * @param operand_2 Second operand.
 * @retval 1 if operand_1 < operand_2
 * @retval 0 otherwise.
 */
int s21_is_less(s21_decimal operand_1, s21_decimal operand_2);

/**
 * @brief Compare two s21_decimal numbers.
 * @param operand_1 First operand.
 * @param operand_2 Second operand.
 * @retval 1 If operand_1 is less than or equal to operand_2.
 * @retval 0 Otherwise.
 *
 */
int s21_is_less_or_equal(s21_decimal operand_1, s21_decimal operand_2);

/**
 * @brief Compare two s21_decimal numbers.
 * @param operand_1 First operand.
 * @param operand_2 Second operand.
 * @retval 1 If operand_1 is greater than  operand_2.
 * @retval 0 Otherwise.
 *
 */
int s21_is_greater(s21_decimal operand_1, s21_decimal operand_2);

/**
 * @brief Compare two s21_decimal numbers.
 * @param operand_1 First operand.
 * @param operand_2 Second operand.
 * @retval 1 If operand_1 is greater than or equal to operand_2.
 * @retval 0 Otherwise.
 *
 */
int s21_is_greater_or_equal(s21_decimal operand_1, s21_decimal operand_2);

/**
 * @brief Compare two s21_decimal numbers.
 * @param operand_1 First operand.
 * @param operand_2 Second operand.
 * @retval 1 If operand_1 is greater equal to operand_2.
 * @retval 0 Otherwise.
 *
 */
int s21_is_equal(s21_decimal operand_1, s21_decimal operand_2);

/**
 * @brief Compare two s21_decimal numbers.
 * @param operand_1 First operand.
 * @param operand_2 Second operand.
 * @retval 1 If operand_1 is greater is not equal to operand_2.
 * @retval 0 Otherwise.
 *
 */
int s21_is_not_equal(s21_decimal operand_1, s21_decimal operand_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);

/**
 * @brief This funс convert float value to s21_decimal
 * @param src float source, for example 21
 * @param dst is destanation/ This is pointer
 * @retval 0 - false
 * @retval 1 - true
 *
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst);

/**
 * @brief This funс convert s21_decimal value to int
 * @param src s21_decimal source, for example 21.21
 * @param dst is int destanation/ This is pointer
 * @retval 0 - false
 * @retval 1 - true
 *
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst);

/**
 * @brief This funс convert s21_decimal value to float
 * @param src s21_decimal source, for example 21.21
 * @param dst is float destanation/ This is pointer
 * @retval 0 - false
 * @retval 1 - true
 *
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/**
 * @brief This rounds a specified Decimal number to the closest integer toward
 * negative infinity.
 * @param value s21_decimal value, for example 21.21
 * @param result is s21_decimal destanation. This is pointer
 * @return The error code
 * @retval 0 - OK
 * @retval 1 - calculation error
 *
 */
int s21_floor(s21_decimal value, s21_decimal *result);

/**
 * @brief This rounds a decimal value to the nearest integer.
 * @param value s21_decimal value, for example 21.21
 * @param result is s21_decimal destanation. This is pointer
 * @return The error code
 * @retval 0 - OK
 * @retval 1 - calculation error
 *
 */
int s21_round(s21_decimal value, s21_decimal *result);

/**
 * @brief This returns the integral digits of the specified Decimal; any
 * fractional digits are discarded, including trailing zeroes..
 * @param value s21_decimal value, for example 21.21
 * @param result is s21_decimal destanation. This is pointer
 * @return The error code
 * @retval 0 - OK
 * @retval 1 - calculation error
 *
 */
int s21_truncate(s21_decimal value, s21_decimal *result);

/**
 * @brief This returns the result of multiplying the specified Decimal value by
 * negative one.
 * @param value s21_decimal value, for example 21.21
 * @param result is s21_decimal destanation. This is pointer
 * @return The error code
 * @retval 0 - OK
 * @retval 1 - calculation error
 *
 */
int s21_negate(s21_decimal value, s21_decimal *result);

/**
 * @brief This function compares two s21_decimal numbers.
 *
 * It takes two s21_decimal arguments and returns an integer indicating the
 * relationship between them: 0 if they are equal, -1 if the first number is
 * less than the second one, or 1 if the first number is greater than the second
 * one.
 *
 * @param a The first s21_decimal to compare.
 * @param b The second s21_decimal to compare.
 * @return An integer indicating the relationship between 'a' and 'b':
 *         - 0 if they are equal
 *         - -1 if 'a' is less than 'b'
 *         - 1 if 'a' is greater than 'b'
 */
int s21_compare_worker(s21_decimal a, s21_decimal b);

#endif