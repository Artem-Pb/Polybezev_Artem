#ifndef SERIAL
#define SERIAL

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "task.h"

List deserialize_list(FILE* file);
bool serialize_list(FILE* file, List* list);
bool is_empty_file(const char* file_name);

#endif