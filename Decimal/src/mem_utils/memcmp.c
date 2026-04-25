#include "mem.h"

int s21_memcmp(const void *str_1, const void *str_2, s21_size_t n) {
  int result = 0;
  const unsigned char *a = (const unsigned char *)str_1;
  const unsigned char *b = (const unsigned char *)str_2;
  for (s21_size_t i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      result = a[i] < b[i] ? -1 : 1;
    }
  }
  return result;
}
