#ifndef TYPES_H
#define TYPES_H

/**
 * @file s21_types.h
 * @brief Custom basic type definitions for the S21 project.
 *
 * This header provides:
 * - ::S21_NULL — null pointer constant
 * - ::s21_size_t — custom size_t equivalent depending on platform
 */

/**
 * \def S21_NULL
 * @brief Null pointer constant.
 */
#ifndef S21_NULL
#define S21_NULL ((void *)0)
#endif

#ifndef S21_SIZET_DEFINED
#define S21_SIZET_DEFINED

#if defined(__x86_64__) || defined(__aarch64__)
/**
 * \typedef s21_size_t
 * @brief Alias for unsigned long on LP64 platforms (Linux/macOS 64-bit).
 * @note
 * - Size: 64 bits
 * @note
 * - Max value: 2^64 - 1 (18446744073709551615)
 */
typedef unsigned long s21_size_t;

#elif defined(_M_X64) || defined(_WIN64)
/**
 * \typedef s21_size_t
 * @brief Alias for unsigned long long on Windows 64-bit (LLP64).
 *  @note
 * - Size: 64 bits
 *  @note
 * - Max value: 2^64 - 1 (18446744073709551615)
 */
typedef unsigned long long s21_size_t;

#elif defined(__i386__) || defined(_M_IX86)
/**
 * \typedef s21_size_t
 * @brief Alias for unsigned int on 32-bit platforms.
 * @note
 * - Size: 32 bits
 * @note
 * - Max value: 2^32 - 1 (4294967295)
 */
typedef unsigned int s21_size_t;

#else
typedef unsigned long long s21_size_t;
#endif
#endif

#endif
