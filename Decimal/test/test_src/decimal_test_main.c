#define _POSIX_C_SOURCE 200809L

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__APPLE__)
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#elif defined(__linux__)
#include <time.h>
#define SLEEP_MS(ms)                                              \
  do {                                                            \
    struct timespec ts = {(ms) / 1000, ((ms) % 1000) * 1000000L}; \
    nanosleep(&ts, NULL);                                         \
  } while (0)
#else
#error "Unsupported platform"
#endif

Suite *s21_add_suite(void);
Suite *s21_sub_suite(void);
Suite *s21_mul_suite(void);
Suite *s21_div_suite(void);

Suite *s21_floor_suite(void);
Suite *s21_round_suite(void);
Suite *s21_truncate_suite(void);
Suite *s21_negate_suite(void);

Suite *s21_is_less_suite(void);
Suite *s21_is_greater_suite(void);
Suite *s21_is_equal_suite(void);
Suite *s21_is_not_equal_suite(void);
Suite *s21_is_less_or_equal_suite(void);
Suite *s21_is_greater_or_equal_suite(void);

Suite *s21_from_int_to_decimal_suite(void);
Suite *s21_from_float_to_decimal_suite(void);
Suite *s21_from_decimal_to_int_suite(void);
Suite *s21_from_decimal_to_float_suite(void);

Suite *s21_sub_mantissa_unit_suite(void);
Suite *normalize_scale_suite(void);
Suite *s21_mul_comprehensive_suite(void);

static Suite *make_master_suite(void) { return suite_create("Master Suite"); }

void progress_callback(int test_num, int total_tests) {
  static int current_progress = 0;
  int progress = (test_num * 100) / total_tests;

  if (progress > current_progress) {
    current_progress = progress;
    int bars = progress / 2;

    printf("\r[");
    for (int i = 0; i < 50; i++) {
      if (i < bars)
        printf("\e[42m=\e[0m");
      else
        printf("-");
    }
    printf("] %d%%", progress);
    fflush(stdout);
  }
}

int run_all_tests(void) {
  int number_failed;

  SRunner *sr = srunner_create(make_master_suite());

  Suite *suites[] = {s21_add_suite(),
                     s21_sub_suite(),
                     s21_mul_suite(),
                     s21_div_suite(),

                     s21_floor_suite(),
                     s21_round_suite(),
                     s21_truncate_suite(),
                     s21_negate_suite(),

                     s21_is_equal_suite(),
                     s21_is_less_suite(),
                     s21_is_greater_or_equal_suite(),
                     s21_is_greater_suite(),
                     s21_is_less_or_equal_suite(),
                     s21_is_not_equal_suite(),

                     s21_from_int_to_decimal_suite(),
                     s21_from_float_to_decimal_suite(),
                     s21_from_decimal_to_int_suite(),
                     s21_from_decimal_to_float_suite(),
                     s21_sub_mantissa_unit_suite(),
                     normalize_scale_suite(),
                     s21_mul_comprehensive_suite(),
                     NULL};

  int total_tests = 200;

  printf("\e[?25l");
  printf(
      "Running tests: [--------------------------------------------------] "
      "0%%");
  fflush(stdout);

  for (int i = 0; suites[i] != NULL; i++) {
    srunner_add_suite(sr, suites[i]);
  }

  srunner_run_all(sr, CK_SILENT);

  for (int i = 1; i <= total_tests; i++) {
    progress_callback(i, total_tests);
    SLEEP_MS(15);
  }

  number_failed = srunner_ntests_failed(sr);

  printf("\r[");
  for (int i = 0; i < 50; i++) printf("\e[42m=\e[0m");
  printf("] 100%%\n");

  if (number_failed == 0) {
    printf(" \e[42;30m PASS \e[0m \e[32mAll tests passed!\e[0m\n");
  } else {
    printf(" \e[41;30m FAIL \e[0m \e[31m%d tests failed:\e[0m\n\n",
           number_failed);
    printf("\e[1;31m=== Failed test details ===\e[0m\n");
    srunner_print(sr, CK_VERBOSE);
  }

  printf("\e[?25h");
  srunner_free(sr);

  return (number_failed == 0) ? 0 : -1;
}

int main(void) {
  printf("\e[1;34m=== S21 Decimal Tests ===\e[0m\n\n");
  int result = run_all_tests();
  printf("\n\e[1;34mTest execution completed\e[0m\n");
  return result;
}
