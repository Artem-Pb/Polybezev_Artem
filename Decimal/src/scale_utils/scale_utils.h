#ifndef SCALE_UTILS
#define SCALE_UTILS

#include "../decimal.h"

/**
 * @brief Gets the scale (exponent) of an s21_decimal.
 *
 * The scale is stored in bits 16-23 of bits[3]. It represents the number of
 * decimal places (the power of 10 by which the mantissa is divided).
 *
 * @param dec Pointer to the source s21_decimal.
 * @return int The scale value (0-28).
 */
int get_scale(const s21_decimal* dec);

/**
 * @brief Sets the scale (exponent) of an s21_decimal.
 *
 * Writes the scale value to bits 16-23 of bits[3]. Does not change the mantissa
 * or sign. The scale value is masked to fit within 8 bits.
 *
 * @param dec Pointer to the s21_decimal to modify.
 * @param scale The new scale value (0-28). Values outside this range are
 * masked/clamped.
 */
void set_scale(s21_decimal* dec, int scale);

/**
 * @brief Normalizes the scales of two s21_decimal numbers.
 *
 * Adjusts the scales of dec1 and dec2 so they are equal, typically by
 * increasing the scale of the one with the smaller scale and multiplying its
 * mantissa accordingly.
 *
 * @param dec1 Pointer to the first s21_decimal (may be modified).
 * @param dec2 Pointer to the second s21_decimal (may be modified).
 * @return s21_internal_error_code_t Status of the operation.
 * @retval S21_INTERNAL_OK Success.
 * @retval S21_INTERNAL_NULL_POINTER If dec1 or dec2 is NULL.
 * @retval S21_INTERNAL_OVERFLOW If increasing the scale causes mantissa
 * overflow.
 * @retval S21_INTERNAL_CONVERSION_ERROR If scale values are invalid.
 */
s21_internal_error_code_t normalize_scale(s21_decimal* dec1, s21_decimal* dec2);

/**
 * @brief Increases the scale of an s21_decimal to a target scale.
 *
 * Multiplies the mantissa by 10^(target_scale - current_scale).
 *
 * @param dec Pointer to the s21_decimal to modify.
 * @param target_scale The desired scale (must be >= current scale).
 * @return s21_internal_error_code_t Status of the operation.
 * @retval S21_INTERNAL_OK Success.
 * @retval S21_INTERNAL_NULL_POINTER If dec is NULL.
 * @retval S21_INTERNAL_OVERFLOW If multiplication causes mantissa overflow.
 * @retval S21_INTERNAL_CONVERSION_ERROR If target_scale is invalid.
 */
s21_internal_error_code_t increase_scale(s21_decimal* dec, int target_scale);

/**
 * @brief Decreases the scale of an s21_decimal to a target scale.
 *
 * Divides the mantissa by 10^(current_scale - target_scale).
 * Optionally applies banker's rounding if there's a remainder.
 *
 * @param dec Pointer to the s21_decimal to modify.
 * @param target_scale The desired scale (must be <= current scale).
 * @param do_bankers_round Flag to enable banker's rounding on remainder.
 * @return s21_internal_error_code_t Status of the operation.
 * @retval S21_INTERNAL_OK Success.
 * @retval S21_INTERNAL_NULL_POINTER If dec is NULL.
 * @retval S21_INTERNAL_OVERFLOW If rounding causes mantissa overflow.
 * @retval S21_INTERNAL_CONVERSION_ERROR If target_scale is invalid.
 */
s21_internal_error_code_t decrease_scale(s21_decimal* dec, int target_scale);
s21_internal_error_code_t local_divide_mantissa_by_10(s21_decimal* dec);

#endif