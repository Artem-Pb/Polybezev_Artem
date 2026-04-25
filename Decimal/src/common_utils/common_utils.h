#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

typedef enum {
  S21_INTERNAL_OK,
  S21_INTERNAL_OVERFLOW,
  S21_INTERNAL_UNDERFLOW,
  S21_INTERNAL_DIV_BY_ZERO,
  S21_INTERNAL_CONVERSION_ERROR,
  S21_INTERNAL_NULL_POINTER,
  S21_INTERNAL_CALCULATION_ERROR
} s21_internal_error_code_t;

/**
 * @brief This define means 31 bit in bits[3]. This bit represents the sign of
 * the number (0 - positive, 1 - negative).
 */
#define SIGN_BIT 0x80000000

/**
 * @brief Maximum valid scale for the s21_decimal type.
 *
 * Defines the highest number of digits that can appear after the decimal point
 * (max: 28). Values beyond this may cause overflow or loss of precision.
 */
#define SCALE_MAX 28

/**
 * @brief This is define means bits shift.
 * @note For example
 */
#define SCALE_BITS 0x00FF0000

#define DEC_MAX_VALUE 79228162514264337593543950335

#define DEC_MIN_VALUE -79228162514264337593543950335

/**
 * @brief Maximum valid scale for s21_decimal type (0 to 28).
 * Values beyond this range may cause overflow or loss of precision.
 */
#define SCALE_MAX 28

/**
 * @brief Bit shift for scale operations (for extracting or setting scale).
 * Shift by 16 bits to isolate scale in bits[3].
 */
#define SHIFT_BIT 16

/**
 * @brief Maximum value for s21_decimal type.
 * Exceeding this value causes overflow.
 */
#define DEC_MAX_VALUE 79228162514264337593543950335

/**
 * @brief Minimum value for s21_decimal type.
 * Exceeding this value causes underflow.
 */
#define DEC_MIN_VALUE -79228162514264337593543950335

/**
 * @brief Maximum bits allocated for the mantissa of s21_decimal.
 */
#define MANTISSA_BITS 96

/**
 * @brief Maximum words used to represent the mantissa of s21_decimal.
 */
#define MANTISSA_WORDS 3

#endif
