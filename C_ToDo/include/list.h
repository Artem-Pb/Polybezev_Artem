#ifndef LIST
#define LIST

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"

typedef struct {
    Task* list;
    size_t count;
    size_t capacity;
} List;

List* init_list(size_t initial_capcity);
bool is_empty_list(const List* list);
bool search_uniq_task(List* list, const Task* task);
bool add_to_list(List* list, const Task* new_task);
bool increase_capcity(List* list);
void free_list(List* list);

#endif