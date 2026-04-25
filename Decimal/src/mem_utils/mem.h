#ifndef MEM_H
#define MEM_H

/**
 * @file s21_mem.h
 * @brief Func for memmory work
 *
 * This header provides:
 * - ::s21_memchr - For seek ch
 * - ::s21_memcmp - Compare bytes
 * - ::s21_memcpy - Copy bytes from src to dest
 * - ::s21_memset - Set value in each byte to the dest
 */

#include "../types/types.h"

/**
 * @brief
 * Compares the first n bytes of val_left and val_right.
 * @param val_left This is pointer to the all data types. Void.
 * @param val_right This is pointer to the all data types. Void.
 * @param n This is s21_size_t count of bytes.
 * @return The int code
 * @retval Negative number if first diff byte in val_left less than in val_right
 * @retval Zero if all count of comparing bytes are equal
 * @retval Positive number if if first diff byte in val_left greater than in
 * val_right
 */
int s21_memcmp(const void *val_left, const void *val_right, s21_size_t n);

/**
 * @brief
 * Copies n characters from src to dest.
 * @param dest This is pointer to the all data types. Void.
 * @param src This is pointer to the all data types. Void.
 * @param n This is s21_size_t count of bytes.
 * @return Pointer to start of dest.
 * @note
 * Of course after copy size and value dest will be modified
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

#endif