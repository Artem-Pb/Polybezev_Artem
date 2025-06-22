#include "serialization.h"

List deserialize_list(FILE* file) {
    List list = {0};

    if (!file) {
        fprintf(stderr, "Error: Invalid file pointer\n");
        return list;
    }

    if (fread(&list.capacity, sizeof(size_t), 1, file) != 1 ||
        fread(&list.count, sizeof(size_t), 1, file) != 1) {
        fprintf(stderr, "Error reading list metadata\n");
        return list;
    }

    list.list = malloc(list.capacity * sizeof(Task));

    if (!list.list) {
        fprintf(stderr, "Memmory allocation failed\n");
        list.capacity = 0;
        list.count = 0;
        return list;
    }

    for (size_t i = 0; i < list.count; i++) {
        Task* current = &list.list[i];

        if (fread(&current->uniq_id, sizeof(int), 1, file) != 1 ||
            fread(current->title, sizeof(char), sizeof(current->title), file) != sizeof(current->title) ||
            fread(current->description, sizeof(char), sizeof(current->description), file) !=
                sizeof(current->description) ||
            fread(&current->is_completed, sizeof(bool), 1, file) != 1) {
            fprintf(stderr, "Error reading task data\n");
            free(list.list);

            list.list = NULL;
            list.capacity = 0;
            list.count = 0;
            return list;
        }
    }

    return list;
}

bool serialize_list(FILE* file, List* list) {
    if (!file || !list || !list->list) {
        fprintf(stderr, "Invalid arguments for serialization\n");
        return false;
    }

    if (fwrite(&list->capacity, sizeof(size_t), 1, file) != 1 ||
        fwrite(&list->count, sizeof(size_t), 1, file) != 1) {
        fprintf(stderr, "Error writing list metadata\n");
        return false;
    }

    for (size_t i = 0; i < list->count; i++) {
        const Task* current = &list->list[i];

        if (fwrite(&current->uniq_id, sizeof(int), 1, file) != 1 ||
            fwrite(current->title, sizeof(char), sizeof(current->title), file) != sizeof(current->title) ||
            fwrite(current->description, sizeof(char), sizeof(current->description), file) !=
                sizeof(current->description) ||
            fwrite(&current->is_completed, sizeof(bool), 1, file) != 1) {
            fprintf(stderr, "Error writing task data\n");
            return false;
        }
    }

    return true;
}

bool is_empty_file(const char* file_name) {
    if (!file_name) return true;

    FILE* file = fopen(file_name, "rb");
    if (!file) return true;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);

    fclose(file);
    return size == 0;
}