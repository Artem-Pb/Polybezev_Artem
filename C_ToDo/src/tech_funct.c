#include "../include/tech_funct.h"

void clear() { printf("\033[H\033[J"); }

void flush() {
    int c;
    while ((c = getchar() != '\n' && c != EOF));
}

Data_union input(enum Data_type type) {
    Data_union result = {0};
    bool valid = false;

    while (!valid) {
        switch (type) {
            case INT: {
                printf("Введите целое число: ");
                int scan_result = scanf("%d", &result.integer);
                if (scan_result != 1) {
                    printf("Ошибка: требуется целое число!\n");
                } else {
                    if (result.integer < INT_MIN || result.integer > INT_MAX) {
                        printf("Ошибка: число вне допустимого диапазона!\n");
                    } else {
                        valid = true;
                    }
                }
                flush();
                break;
            }

            case CHAR: {
                printf("Введите символ: ");
                int res = scanf(" %c", &result.characster);

                if (res != 1) {
                    printf("Ошибка: требуется целое число!\n");
                } else {
                    valid = true;
                }

                flush();
                break;
            }

            case STRING: {
                printf("Введите строку (макс %zu символов): ", sizeof(result.string) - 1);
                char buffer[sizeof(result.string) * 2];

                if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                    printf("Ошибка чтения ввода!\n");
                    flush();
                    break;
                }

                buffer[strcspn(buffer, "\n")] = '\0';

                if (strlen(buffer) >= sizeof(result.string)) {
                    printf("Ошибка: строка слишком длинная!\n");
                    flush();
                } else {
                    strncpy(result.string, buffer, sizeof(result.string) - 1);
                    result.string[sizeof(result.string) - 1] = '\0';
                    valid = true;
                }

                break;
            }

            case BOOLEAN: {
                printf("Введите статус (1 - выполнено, 0 - не выполнено): ");
                int temp;
                int scan_result = scanf("%d", &temp);
                if (scan_result != 1) {
                    printf("Ошибка: требуется 0 или 1!\n");
                } else if (temp != 0 && temp != 1) {
                    printf("Ошибка: введите 0 или 1!\n");
                } else {
                    result.boolean = (bool)temp;
                    valid = true;
                }
                flush();
                break;
            }

            default:
                valid = true;
                break;
        }
    }

    return result;
}

int compare_id(const void* a, const void* b) {
    const Task* task1 = (const Task*)a;
    const Task* task2 = (const Task*)b;
    return (task1->uniq_id > task2->uniq_id) - (task1->uniq_id < task2->uniq_id);
}

int compare_title(const void* a, const void* b) {
    const Task* task1 = (const Task*)a;
    const Task* task2 = (const Task*)b;
    return strcmp(task1->title, task2->title);
}

int compare_status(const void* a, const void* b) {
    const Task* task1 = (const Task*)a;
    const Task* task2 = (const Task*)b;
    return (task1->is_completed > task2->is_completed) - (task1->is_completed < task2->is_completed);
}