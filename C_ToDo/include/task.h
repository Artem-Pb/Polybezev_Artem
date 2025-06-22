#ifndef TASK
#define TASK

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int uniq_id;
    char title[256];
    char description[1024];
    bool is_completed;
} Task;

Task* create_task(const char* title, const char* description, bool status, int id);
void new_title(Task* task, const char* title);
void new_description(Task* task, const char* description);
void new_status(Task* task, bool is_compleate);

char* to_string(const Task* task);
bool equals(const Task* task1, const Task* task2);
int compare(const Task* task1, const Task* task2);

void free_task(Task* task);

#endif