#include "decimal.h"
int s21_is_greater(s21_decimal operand_1, s21_decimal operand_2) {
  return s21_compare_worker(operand_1, operand_2) == 1 ? S21_COMPARISON_TRUE
                                                       : S21_COMPARISON_FALSE;
}
