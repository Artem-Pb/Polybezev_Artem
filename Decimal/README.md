# Decimal

A C implementation of the 128-bit fixed-point `Decimal` type — modelled after the C# `System.Decimal` specification. Provides exact decimal arithmetic without floating-point rounding errors, suitable for financial and high-precision calculations.

## Overview

The standard IEEE 754 `float`/`double` cannot represent many decimal fractions exactly. This library implements a 128-bit structure (96-bit mantissa + scale + sign) that stores values as `mantissa × 10^(-scale)`, matching the C# Decimal layout bit-for-bit.

```c
typedef struct {
    int bits[4]; // bits[3] holds sign and scale
} s21_decimal;
```

## API

### Arithmetic

```c
int s21_add(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_sub(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_mul(s21_decimal a, s21_decimal b, s21_decimal *result);
int s21_div(s21_decimal a, s21_decimal b, s21_decimal *result);
```

All operations return an error code: `0` OK, `1` overflow, `2` underflow, `3` division by zero.

### Comparison

```c
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
```

### Conversion

```c
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
```

### Math

```c
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
```

## Architecture

```
src/
├── decimal.h               # Public API and type definitions
├── add.c / sub.c / mul.c / div.c
├── is_*.c                  # Comparison functions
├── from_*.c                # Conversion functions
├── floor.c / round.c / truncate.c / negate.c
├── big_decimal_utils/      # 192-bit intermediate arithmetic
├── bit_utils/              # Bit-level operations
├── mantissa_utils/         # 96-bit mantissa add/sub/compare
├── scale_utils/            # Scale normalisation
├── sign_ops/               # Sign extraction and setting
├── mem_utils/              # Custom memcpy / memcmp
└── types/                  # Shared type definitions

test/
├── test_src/               # Unit tests for every function (~15 files)
└── test_valgrind/          # Valgrind memory-safety tests
```

## Key implementation details

- **Intermediate precision**: multiplication and division use a 192-bit `big_decimal` to avoid overflow during computation before scaling back.
- **Scale normalisation**: before binary operations, scales are aligned by multiplying the smaller-scale operand's mantissa.
- **Banker's rounding**: `s21_round` implements round-half-to-even (same as C# `Math.Round`).
- **Full test coverage**: every public function has dedicated unit tests covering normal cases, boundary values, overflow, underflow, and null-pointer inputs.

## Tech stack

C11 · Makefile · Check (unit testing) · Valgrind
