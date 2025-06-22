#define _POSIX_C_SOURCE 200809L
#ifndef S21_CAT_H
#define S21_CAT_H

#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int number_nonblank;
  int number;
  int squeeze_blank;
  int show_ends;
  int show_tabs;
  int non_printing;
  int current_line;
  int prev_line_blank;
  int prev_file_nl;
  int last_line_no_nl;
  int skip_number_for_next_line;
} Options;

void parse_args(int argc, char **argv, Options *opts);
void process_file(const char *filename, Options *opts);
void process_line(const char *line, Options *opts);
void print_nonprinting_char(unsigned char c);

#endif