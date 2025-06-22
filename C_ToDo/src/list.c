#include "../include/list.h"

#include <stdio.h>

List* init_list(size_t initial_capcity) {
    List* list = malloc(sizeof(List));
    if (!list) return NULL;

    list->list = malloc(initial_capcity * sizeof(Task));
    if (!list->list) {
        free(list);
        return NULL;
    }

    list->count = 0;
    list->capacity = initial_capcity;

    return list;
}

bool increase_capcity(List* list) {
    size_t new_capcity = list->capacity * 2;
    Task* new_list = realloc(list->list, new_capcity * sizeof(Task));

    if (!new_list) return false;  // место для записи в log

    list->list = new_list;
    list->capacity = new_capcity;

    return true;
}

bool add_to_list(List* list, const Task* new_task) {
    if (list->count == list->capacity) {
        if (!increase_capcity(list)) {
            return false;
        }
    }

    memcpy(&list->list[list->count++], new_task, sizeof(Task));
    return true;
}

bool is_empty_list(const List* list) { return list == NULL || list->count == 0; }

bool search_uniq_task(List* list, const Task* task) {
    if (is_empty_list(list)) return true;

    for (size_t i = 0; i < list->count; i++) {
        if (equals(&list->list[i], task)) {
            return false;
        }
    }
    return true;
}

void free_list(List* list) {
    if (list) {
        free(list->list);
        free(list);
    }
}