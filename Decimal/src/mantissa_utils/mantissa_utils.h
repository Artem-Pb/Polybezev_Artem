#ifndef MANTISSA_UTILS
#define MANTISSA_UTILS

#include "../decimal.h"

/**
 * @brief Adds the 96-bit mantissas of two s21_decimal numbers.
 *
 * Performs addition on bits[0..2] of dec1 and dec2. Overflow is detected.
 *
 * @param dec1 Pointer to the first operand.
 * @param dec2 Pointer to the second operand.
 * @param result Pointer to store the resulting mantissa.
 * @return s21_internal_error_code_t Status of the operation.
 * @retval S21_INTERNAL_OK Success.
 * @retval S21_INTERNAL_NULL_POINTER If any pointer is NULL.
 * @retval S21_INTERNAL_OVERFLOW If the result exceeds 96 bits.
 */
s21_internal_error_code_t add_mantissa(s21_decimal *dec1, s21_decimal *dec2,
                                       s21_decimal *result);

/**
 * @brief Subtracts the 96-bit mantissa of dec2 from dec1.
 *
 * Performs subtraction on bits[0..2]. Assumes dec1 >= dec2 to avoid underflow
 * in unsigned arithmetic context. Underflow is detected.
 *
 * @param dec1 Pointer to the minuend.
 * @param dec2 Pointer to the subtrahend.
 * @param result Pointer to store the resulting mantissa.
 * @return s21_internal_error_code_t Status of the operation.
 * @retval S21_INTERNAL_OK Success.
 * @retval S21_INTERNAL_NULL_POINTER If any pointer is NULL.
 * @retval S21_INTERNAL_OVERFLOW If dec1 < dec2 (unsigned underflow).
 */
s21_internal_error_code_t sub_mantissa(const s21_decimal *dec1,
                                       const s21_decimal *dec2,
                                       s21_decimal *result);

/**
 * @brief Compares the 96-bit mantissas of two s21_decimal numbers.
 *
 * Compares bits[0..2] of dec1 and dec2.
 *
 * @param dec1 Pointer to the first operand.
 * @param dec2 Pointer to the second operand.
 * @return int Comparison result.
 * @retval -1 If mantissa of dec1 is less than mantissa of dec2.
 * @retval 0 If mantissas are equal.
 * @retval 1 If mantissa of dec1 is greater than mantissa of dec2.
 */
int compare_mantissa(const s21_decimal *dec1, const s21_decimal *dec2);

/**
 * @brief Checks if the 96-bit mantissa of an s21_decimal is zero.
 *
 * Checks if bits[0], bits[1], and bits[2] are all zero.
 *
 * @param dec Pointer to the s21_decimal.
 * @return int Zero check result.
 * @retval 1 If the mantissa is zero.
 * @retval 0 If the mantissa is not zero.
 */
int is_zero(const s21_decimal *dec);

#endif