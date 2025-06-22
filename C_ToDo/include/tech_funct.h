#ifndef TECH
#define TECH

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"

typedef union {
    int integer;
    char characster;
    char string[256];
    bool boolean;
} Data_union;

enum Data_type { INT, CHAR, STRING, BOOLEAN };

Data_union input(enum Data_type type);
void clear();
void flush();

int compare_id(const void *a, const void *b);
int compare_title(const void *a, const void *b);
int compare_status(const void *a, const void *b);

#endif