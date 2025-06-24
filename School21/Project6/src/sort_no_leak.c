#include <stdio.h>
#include <stdlib.h>

void sort(int *a, int length);
int input(int **a, int *length);
void output(const int *a, int length);

int main() {
    int length;
    int *a = NULL;

    if (input(&a, &length) != 0) {
        return 1;
    }

    sort(a, length);
    output(a, length);
    free(a);
    return 0;
}

void sort(int *a, int length) {
    for (int i = length - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

void output(const int *a, int length) {
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            printf("%d", a[i]);
        } else {
            printf(" %d", a[i]);
        }
    }
}

int input(int **a, int *length) {
    if (scanf("%d", length) != 1) {
        return 1;
    }

    *a = malloc(*length * sizeof(int));
    if (!*a) {
        return 2;
    }

    for (int i = 0; i < *length; i++) {
        if (scanf("%d", &((*a)[i])) != 1) {
            printf("n/a");
            return -1;
        }
    }

    return 0;
}