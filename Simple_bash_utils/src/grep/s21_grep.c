#include "s21_grep.h"

int main(int argc, char **argv) {
  Options options = {0};
  Patterns patterns = {0};
  patterns.count = 0;
  const char *exit =
      "usage: grep [options] pattern [file...]\n\
                    Search for pattern in each file. \n\
                    Options:\n\
                    -e PATTERN specify pattern\n\
                    -i Ignore case\n\
                    -v Ignore match\n\
                    -c Print only count matches\n\
                    -l Print only file name\n\
                    -n Print number line\n\
                    -h Suppres pref filename\n\
                    -s Suppres error mass\n\
                    -f FILE add patterns from file\n\
                    -o show only part matching line\n\
                    ";
  if (argc > 1 && read_opt(argc, argv, &options, &patterns)) {
    if (!options.flag_f && !options.is_patterns) {
      if (optind < argc) {
        add(&patterns, argv[optind++]);
      } else {
        printf("%s", exit);
        return 1;
      }
    }

    if (optind < argc) {
      enum_file(argc, argv, &options, &patterns);
    } else {
      printf("%s", exit);
    }
  }

  return 0;
}

int read_opt(int argc, char **argv, Options *options, Patterns *patterns) {
  int ch = 0;
  int res = 1;

  while ((ch = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    res = parse_opt(ch, optarg, options, patterns);

    if (!res) break;
  }

  if (options->flag_l) {
    options->flag_h = false;
    options->flag_c = false;
    options->flag_n = false;
    options->flag_o = false;
  }

  if (options->flag_c) {
    options->flag_n = false;
    options->flag_o = false;
  }

  return res;
}

int parse_opt(char option, char *optarg, Options *options, Patterns *patterns) {
  int res = 1;

  switch (option) {
    case 'e':
      options->flag_e = true;
      add(patterns, optarg);
      options->is_patterns = true;
      break;
    case 'f':
      options->flag_f = true;
      res = read_patterns(patterns, optarg);
      options->is_patterns = res;
      break;
    case 'i':
      options->flag_i = true;
      break;
    case 'n':
      options->flag_n = true;
      break;
    case 'c':
      options->flag_c = true;
      break;
    case 'h':
      options->flag_h = true;
      break;
    case 's':
      options->flag_s = true;
      break;
    case 'l':
      options->flag_l = true;
      break;
    case 'o':
      options->flag_o = true;
      break;
    case 'v':
      options->flag_v = true;
      break;
  }

  return res;
}

void enum_file(int argc, char **argv, Options *options, Patterns *patterns) {
  if (argc - optind == 1) {
    options->flag_h = true;
  }

  char buff[16384];
  int line_num = 0;
  int line_count = 0;
  int stop = 0;

  while (optind < argc) {
    FILE *file = fopen(argv[optind], "r");

    if (file != NULL) {
      while (fgets(buff, sizeof(buff), file) && !stop) {
        line_num++;
        size_t len = strlen(buff);

        if (len > 0 && buff[len - 1] == '\n') {
          buff[len - 1] = '\0';
        }

        Position match = search_match(buff, options, patterns);

        if ((match.found && !options->flag_v) ||
            (!match.found && options->flag_v)) {
          processing_match(buff, line_num, options, argv[optind], match,
                           &line_count, &stop);
        }
      }

      if (options->flag_c) {
        if (!options->flag_h) {
          printf("%s:", argv[optind]);
        }
        printf("%d\n", line_count);
      }
      fclose(file);
    } else if (!options->flag_s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
    }

    optind++;
  }
}

void print(const char *buff, int line_num, const Options *options,
           const char *filename, Position match) {
  if (options->flag_o && match.found) {
    if (!options->flag_h) {
      printf("%s:", filename);
    }

    if (options->flag_n) {
      printf("%d:", line_num);
    }

    printf("%.*s\n", match.end - match.start, buff + match.start);
  } else if (!options->flag_o) {
    if (!options->flag_h) {
      printf("%s:", filename);
    }

    if (options->flag_n) {
      printf("%d:", line_num);
    }
    printf("%s\n", buff);
  }
}

Position search_match(char *line, Options *options, Patterns *patterns) {
  Position res = {0, 0, 0};
  regex_t reg;
  int reg_flag = options->flag_i ? REG_ICASE : 0;
  regmatch_t match;

  for (int i = 0; i < patterns->count; i++) {
    if (regcomp(&reg, patterns->patterns[i], reg_flag) == 0) {
      if (regexec(&reg, line, 1, &match, 0) == 0) {
        res.start = match.rm_so;
        res.end = match.rm_eo;
        res.found = 1;
      }
    }

    regfree(&reg);

    if (res.found) break;
  }

  return res;
}

void processing_match(const char *line, int line_num, const Options *options,
                      const char *filename, Position match, int *line_count,
                      int *stop) {
  (*line_count)++;

  if (!options->flag_l && !options->flag_c) {
    print(line, line_num, options, filename, match);
  } else if (options->flag_l) {
    printf("%s\n", filename);
    *stop = 1;
  }
}

int read_patterns(Patterns *patterns, const char *patterns_file) {
  FILE *file;
  char buff[256];
  int res = 1;

  if ((file = fopen(patterns_file, "r")) == NULL) {
    printf("file %s not found\n", patterns_file);
    res = 0;
  } else {
    while (fgets(buff, sizeof(buff), file)) {
      add(patterns, buff);
    }

    fclose(file);
  }

  return res;
}

void add(Patterns *patterns, char *pattern) {
  int len = strlen(pattern);

  if (len < 256 && patterns->count < 1024) {
    if (pattern[len - 1] == '\n') {
      pattern[len - 1] = '\0';
    }

    strcpy(patterns->patterns[patterns->count], pattern);

    patterns->count++;
  }
}