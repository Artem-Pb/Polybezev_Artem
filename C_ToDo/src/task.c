#include "../include/task.h"

#include <stdio.h>

void new_title(Task* task, const char* title) {
    if (!task || !title) {
        strncpy(task->title, title, sizeof(task->title) - 1);
        task->title[sizeof(task->title) - 1] = '\0';
    }
}

void new_description(Task* task, const char* description) {
    if (!task || !description) {
        strncpy(task->description, description, sizeof(task->description) - 1);
        task->description[sizeof(task->description) - 1] = '\0';
    }
}

void new_status(Task* task, bool is_compleate) { task->is_completed = is_compleate; }

Task* create_task(const char* title, const char* description, bool status, int id) {
    if (!title || !description) return NULL;

    Task* task = malloc(sizeof(Task));
    if (!task) return NULL;

    strncpy(task->title, title, sizeof(task->title) - 1);
    task->title[sizeof(task->title) - 1] = '\0';

    strncpy(task->description, description, sizeof(task->description));
    task->description[sizeof(task->description) - 1] = '\0';

    task->is_completed = status;
    task->uniq_id = id;

    return task;
}

char* to_string(const Task* task) {
    if (!task) return NULL;

    const char* complete = "Выполнена";
    const char* no_complete = "Не выполнена";

    size_t needed_size = snprintf(NULL, 0, "{Задача №%d. %s\n%s\nв статусе: %s}", task->uniq_id, task->title,
                                  task->description, task->is_completed ? complete : no_complete) +
                         1;

    char* buffer = malloc(needed_size);
    if (!buffer) return NULL;

    snprintf(buffer, needed_size, "{Задача №%d. %s\n%s\nв статусе: %s}", task->uniq_id, task->title,
             task->description, task->is_completed ? complete : no_complete);

    return buffer;
}

bool equals(const Task* task1, const Task* task2) {
    if (!task1 || !task2) return false;
    return strcmp(task1->title, task2->title) == 0 && strcmp(task1->description, task2->description) == 0 &&
           task1->is_completed == task2->is_completed;
}

int compare(const Task* task1, const Task* task2) {
    if (!task1 || !task2) return 0;

    int title_diff = strcmp(task1->title, task2->title);
    if (title_diff != 0) return title_diff;

    int desc_diff = strcmp(task1->description, task2->description);
    if (desc_diff != 0) return desc_diff;

    return task1->is_completed - task2->is_completed;
}

void free_task(Task* task) { free(task); }