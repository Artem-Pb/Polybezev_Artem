#ifndef GREP
#define GREP

#define _POSIX_C_SOURCE 200809L
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int start;
  int end;
  int found;
} Position;

typedef struct {
  char patterns[1024][256];
  int count;
} Patterns;

typedef struct {
  bool flag_e;
  bool flag_i;
  bool flag_v;
  bool flag_c;
  bool flag_l;
  bool flag_n;
  bool flag_h;
  bool flag_s;
  bool flag_f;
  bool flag_o;

  bool is_patterns;
  bool is_more_files;
} Options;

int read_opt(int argc, char **argv, Options *options, Patterns *patterns);
int parse_opt(char option, char *optarg, Options *options, Patterns *patterns);

void enum_file(int argc, char **argv, Options *options, Patterns *patterns);
void print(const char *buff, int line_num, const Options *options,
           const char *filename, Position match);

Position search_match(char *line, Options *options, Patterns *patterns);
void processing_match(const char *line, int line_num, const Options *options,
                      const char *filename, Position match, int *line_count,
                      int *stop);

int read_patterns(Patterns *patterns, const char *patterns_file);
void add(Patterns *patterns, char *pattern);

#endif