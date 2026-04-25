#include "valgrind_test.h"

int main() {
  s21_decimal comparing_left;
  s21_decimal comparing_right;
  decimal_init(&comparing_left, 26, 0, 0, 2, 1);
  decimal_init(&comparing_right, 28, 0, 0, 1, 1);

  compare_func_test(comparing_left, comparing_right);

  convert_func_test();

  arithmetic_func_test();
  other_func_test();
  return 0;
}