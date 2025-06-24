#include <stdio.h>
#include <stdlib.h>

int** allocate_matrix(int n, int m);
void free_matrix(int** matrix, int n);
int input_matrix(int** matrix, int n, int m);
void print_matrix(int** matrix, int n, int m);
int** add_matrices(int** a, int** b, int n, int m);
int** multiply_matrices(int** a, int** b, int n, int m, int p);
int** transpose_matrix(int** matrix, int n, int m);

int main() {
    int operation, n1, m1, n2, m2;
    int **matrix1 = NULL, **matrix2 = NULL, **result = NULL;
    if (scanf("%d", &operation) != 1 || operation < 1 || operation > 3) {
        printf("n/a");
        return 0;
    }
    if (operation == 3) {
        if (scanf("%d %d", &n1, &m1) != 2 || n1 <= 0 || m1 <= 0) {
            printf("n/a");
            return 0;
        }
    } else {
        if (scanf("%d %d", &n1, &m1) != 2 || n1 <= 0 || m1 <= 0) {
            printf("n/a");
            return 0;
        }
        if (operation == 2) {
            if (scanf("%d %d", &n2, &m2) != 2 || n2 <= 0 || m2 <= 0 || m1 != n2) {
                printf("n/a");
                return 0;
            }
        } else {
            if (scanf("%d %d", &n2, &m2) != 2 || n2 <= 0 || m2 <= 0 || n1 != n2 || m1 != m2) {
                printf("n/a");
                return 0;
            }
        }
    }
    matrix1 = allocate_matrix(n1, m1);
    if (!matrix1 || !input_matrix(matrix1, n1, m1)) {
        if (matrix1) free_matrix(matrix1, n1);
        printf("n/a");
        return 0;
    }
    if (operation != 3) {
        matrix2 = allocate_matrix(n2, m2);
        if (!matrix2 || !input_matrix(matrix2, n2, m2)) {
            free_matrix(matrix1, n1);
            if (matrix2) free_matrix(matrix2, n2);
            printf("n/a");
            return 0;
        }
    }
    switch (operation) {
        case 1:
            result = add_matrices(matrix1, matrix2, n1, m1);
            break;
        case 2:
            result = multiply_matrices(matrix1, matrix2, n1, m1, m2);
            break;
        case 3:
            result = transpose_matrix(matrix1, n1, m1);
            break;
    }
    if (!result) {
        printf("n/a");
    } else {
        int res_rows = (operation == 3) ? m1 : n1;
        int res_cols = (operation == 3) ? n1 : (operation == 2) ? m2 : m1;
        print_matrix(result, res_rows, res_cols);
        free_matrix(result, res_rows);
    }
    free_matrix(matrix1, n1);
    if (matrix2) free_matrix(matrix2, n2);
    return 0;
}
int** allocate_matrix(int n, int m) {
    int** matrix = malloc(n * sizeof(int*));
    if (!matrix) return NULL;
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(m * sizeof(int));
        if (!matrix[i]) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}
void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int input_matrix(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                return 0;
            }
        }
    }
    return 1;
}
void print_matrix(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j < m - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
}
int** add_matrices(int** a, int** b, int n, int m) {
    int** result = allocate_matrix(n, m);
    if (!result) return NULL;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    return result;
}
int** multiply_matrices(int** a, int** b, int n, int m, int p) {
    int** result = allocate_matrix(n, p);
    if (!result) return NULL;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            result[i][j] = 0;
            for (int k = 0; k < m; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}
int** transpose_matrix(int** matrix, int n, int m) {
    int** result = allocate_matrix(m, n);
    if (!result) return NULL;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[j][i];
        }
    }
    return result;
}