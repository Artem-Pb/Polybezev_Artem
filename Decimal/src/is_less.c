#include "decimal.h"

int s21_is_less(s21_decimal operand_1, s21_decimal operand_2) {
  return s21_compare_worker(operand_1, operand_2) < 0 ? S21_COMPARISON_TRUE
                                                      : S21_COMPARISON_FALSE;
}
