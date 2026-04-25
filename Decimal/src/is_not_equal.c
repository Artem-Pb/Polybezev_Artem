#include "decimal.h"

int s21_is_not_equal(s21_decimal operand_1, s21_decimal operand_2) {
  int result = s21_compare_worker(operand_1, operand_2);
  if (result < 0) {
    result = S21_COMPARISON_TRUE;
  } else if (result > 0) {
    result = S21_COMPARISON_TRUE;
  } else {
    result = S21_COMPARISON_FALSE;
  }
  return result;
}