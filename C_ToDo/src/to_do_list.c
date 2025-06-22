#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "serialization.h"
#include "task.h"
#include "tech_funct.h"

#define DATA_FILE "todolist_data.dat"

void display_menu() {
    clear();
    printf("\n=== ToDo List Manager ===\n");
    printf("1. Добавить задачу\n");
    printf("2. Просмотреть все задачи\n");
    printf("3. Найти задачу по ID\n");
    printf("4. Удалить задачу\n");
    printf("5. Изменить статус задачи\n");
    printf("6. Сортировать задачи\n");
    printf("7. Сохранить и выйти\n");
    printf("Выберите действие: ");
}

void print_task(const Task* task) {
    char* task_str = to_string(task);
    if (task_str) {
        printf("%s\n", task_str);
        free(task_str);
    }
}

void add_task_interactive(List* list) {
    clear();
    printf("\n=== Добавление новой задачи ===\n");

    printf("Введите заголовок: ");
    Data_union title = input(STRING);

    printf("Введите описание: ");
    Data_union desc = input(STRING);

    printf("Статус (1 - выполнено, 0 - не выполнено): ");
    Data_union status = input(BOOLEAN);

    static int last_id = 0;
    int new_id = ++last_id;

    Task* task = create_task(title.string, desc.string, status.boolean, new_id);
    if (!task) {
        printf("Ошибка создания задачи!\n");
        return;
    }

    if (!add_to_list(list, task)) {
        printf("Ошибка добавления задачи!\n");
        free_task(task);
        return;
    }

    printf("\nЗадача успешно добавлена (ID: %d)\n", new_id);
}

void view_all_tasks(const List* list) {
    clear();
    printf("\n=== Все задачи ===\n");

    if (is_empty_list(list)) {
        printf("Список задач пуст.\n");
        return;
    }

    for (size_t i = 0; i < list->count; i++) {
        print_task(&list->list[i]);
        printf("-----------------\n");
    }
}

Task* find_task_by_id(const List* list, int id) {
    if (is_empty_list(list)) return NULL;

    for (size_t i = 0; i < list->count; i++) {
        if (list->list[i].uniq_id == id) {
            return &list->list[i];
        }
    }
    return NULL;
}

void delete_task_by_id(List* list) {
    clear();
    printf("\n=== Удаление задачи ===\n");

    if (is_empty_list(list)) {
        printf("Список задач пуст.\n");
        return;
    }

    printf("Введите ID задачи для удаления: ");
    Data_union id = input(INT);

    Task* found = NULL;
    size_t index = 0;
    for (; index < list->count; index++) {
        if (list->list[index].uniq_id == id.integer) {
            found = &list->list[index];
            break;
        }
    }

    if (!found) {
        printf("Задача с ID %d не найдена.\n", id.integer);
        return;
    }

    // Сдвигаем оставшиеся элементы
    for (size_t i = index; i < list->count - 1; i++) {
        list->list[i] = list->list[i + 1];
    }

    list->count--;
    printf("Задача с ID %d успешно удалена.\n", id.integer);
}

void toggle_task_status(List* list) {
    clear();
    printf("\n=== Изменение статуса задачи ===\n");

    if (is_empty_list(list)) {
        printf("Список задач пуст.\n");
        return;
    }

    printf("Введите ID задачи: ");
    Data_union id = input(INT);

    Task* task = find_task_by_id(list, id.integer);
    if (!task) {
        printf("Задача с ID %d не найдена.\n", id.integer);
        return;
    }

    task->is_completed = !task->is_completed;
    printf("Статус задачи ID %d изменен на: %s\n", id.integer,
           task->is_completed ? "Выполнена" : "Не выполнена");
}

void sort_tasks_menu(List* list) {
    clear();
    printf("\n=== Сортировка задач ===\n");
    printf("1. По ID\n");
    printf("2. По названию\n");
    printf("3. По статусу\n");
    printf("Выберите критерий сортировки: ");

    Data_union choice = input(INT);

    switch (choice.integer) {
        case 1:
            qsort(list->list, list->count, sizeof(Task), compare_id);
            printf("Задачи отсортированы по ID.\n");
            break;
        case 2:
            qsort(list->list, list->count, sizeof(Task), compare_title);
            printf("Задачи отсортированы по названию.\n");
            break;
        case 3:
            qsort(list->list, list->count, sizeof(Task), compare_status);
            printf("Задачи отсортированы по статусу.\n");
            break;
        default:
            printf("Неверный выбор.\n");
            break;
    }
}

void save_and_exit(List* list) {
    FILE* file = fopen(DATA_FILE, "wb");
    if (!file) {
        printf("Ошибка открытия файла для записи!\n");
        return;
    }

    if (!serialize_list(file, list)) {
        printf("Ошибка сохранения данных!\n");
    } else {
        printf("Данные успешно сохранены в %s\n", DATA_FILE);
    }

    fclose(file);
}

int main() {
    List* list = NULL;
    FILE* file = fopen(DATA_FILE, "rb");

    if (file) {
        List loaded = deserialize_list(file);
        list = malloc(sizeof(List));
        if (list) {
            *list = loaded;
        }
        fclose(file);
    }

    if (!list) {
        list = init_list(10);
        if (!list) {
            fprintf(stderr, "Ошибка инициализации списка!\n");
            return EXIT_FAILURE;
        }
    }

    // Главный цикл
    int choice = 0;
    while (choice != 7) {
        display_menu();
        Data_union input_choice = input(INT);
        choice = input_choice.integer;

        switch (choice) {
            case 1:
                add_task_interactive(list);
                break;
            case 2:
                view_all_tasks(list);
                break;
            case 3: {
                printf("Введите ID задачи: ");
                Data_union id = input(INT);
                Task* task = find_task_by_id(list, id.integer);
                if (task) {
                    print_task(task);
                } else {
                    printf("Задача с ID %d не найдена.\n", id.integer);
                }
                break;
            }
            case 4:
                delete_task_by_id(list);
                break;
            case 5:
                toggle_task_status(list);
                break;
            case 6:
                sort_tasks_menu(list);
                break;
            case 7:
                save_and_exit(list);
                break;
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
                break;
        }

        if (choice != 7) {
            printf("\nНажмите Enter для продолжения...");
            flush();
            getchar();
        }
    }

    if (list) {
        free(list->list);
        free(list);
    }

    return EXIT_SUCCESS;
}