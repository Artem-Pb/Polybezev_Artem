#include "mem.h"

void *s21_memcpy(void *dest_str, const void *src_str, s21_size_t n) {
  unsigned char *d_str = dest_str;
  const unsigned char *src = src_str;
  for (s21_size_t i = 0; i < n; i++) {
    d_str[i] = src[i];
  }
  return dest_str;
}