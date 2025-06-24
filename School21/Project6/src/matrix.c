#include <stdio.h>
#include <stdlib.h>

#define NMAX 100
#define MMAX 100

int num_select();
void print_matrix(int **matrix, const int *flat_matrix, int n, int m, int is_static);
void process_static(int n, int m) {
    if (n > NMAX || m > MMAX) {
        printf("n/a");
        return;
    }
    int matrix[NMAX][MMAX];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int val = num_select();
            if (val == -1) {
                printf("n/a");
                return;
            }
            matrix[i][j] = val;
        }
    }
    print_matrix(NULL, (int *)matrix, n, m, 1);
}
int **create_matrix_style1(int n, int m) {
    int **matrix = malloc(n * sizeof(int *) + n * m * sizeof(int));
    int *data = (int *)(matrix + n);
    for (int i = 0; i < n; i++) {
        matrix[i] = data + i * m;
    }
    return matrix;
}
void free_matrix_style1(int **matrix) { free(matrix); }
int **create_matrix_style2(int n, int m) {
    int **matrix = malloc(n * sizeof(int *));
    int *data = malloc(n * m * sizeof(int));
    for (int i = 0; i < n; i++) {
        matrix[i] = data + i * m;
    }
    return matrix;
}
void free_matrix_style2(int **matrix) {
    free(matrix[0]);
    free(matrix);
}
int **create_matrix_style3(int n, int m) {
    int **matrix = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(m * sizeof(int));
    }
    return matrix;
}
void free_matrix_style3(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
void process_dynamic(int **matrix, int n, int m, int style) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int val = num_select();
            if (val == -1) {
                printf("n/a");
                return;
            }
            matrix[i][j] = val;
        }
    }
    print_matrix(matrix, NULL, n, m, 0);
    switch (style) {
        case 1:
            free_matrix_style1(matrix);
            break;
        case 2:
            free_matrix_style2(matrix);
            break;
        case 3:
            free_matrix_style3(matrix, n);
            break;
    }
}
int num_select() {
    int num;
    if (scanf("%d", &num) != 1) {
        return -1;
    }
    return num;
}
void print_matrix(int **matrix, const int *flat_matrix, int n, int m, int is_static) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (is_static) {
                printf("%d", flat_matrix[i * m + j]);
            } else {
                printf("%d", matrix[i][j]);
            }
            if (j < m - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
}
void menu() {
    int choice = num_select();
    if (choice < 0 || choice > 3) {
        printf("n/a");
        return;
    }
    int n = num_select();
    int m = num_select();
    if (n <= 0 || m <= 0) {
        printf("n/a");
        return;
    }
    switch (choice) {
        case 0:
            process_static(n, m);
            break;
        case 1: {
            int **matrix = create_matrix_style1(n, m);
            if (!matrix) {
                printf("n/a");
                return;
            }
            process_dynamic(matrix, n, m, 1);
            break;
        }
        case 2: {
            int **matrix = create_matrix_style2(n, m);
            if (!matrix) {
                printf("n/a");
                return;
            }
            process_dynamic(matrix, n, m, 2);
            break;
        }
        case 3: {
            int **matrix = create_matrix_style3(n, m);
            if (!matrix) {
                printf("n/a");
                return;
            }
            process_dynamic(matrix, n, m, 3);
            break;
        }
    }
}
int main() {
    menu();
    return 0;
}