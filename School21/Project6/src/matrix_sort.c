#include <stdio.h>
#include <stdlib.h>

int** allocate_matrix(int n, int m, int style);
void free_matrix(int** matrix, int n, int style);
int input_matrix(int** matrix, int n, int m);
void sort_matrix(int** matrix, int n, int m);
void print_matrix(int** matrix, int n, int m);
int calculate_row_sum(const int* row, int m);

int main() {
    int n, m, style;
    if (scanf("%d", &style) != 1 || style < 1 || style > 3) {
        printf("n/a");
        return 0;
    }
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0) {
        printf("n/a");
        return 0;
    }
    int** matrix = allocate_matrix(n, m, style);
    if (!matrix) {
        printf("n/a");
        return 0;
    }
    if (!input_matrix(matrix, n, m)) {
        free_matrix(matrix, n, style);
        printf("n/a");
        return 0;
    }
    sort_matrix(matrix, n, m);
    print_matrix(matrix, n, m);
    free_matrix(matrix, n, style);
    return 0;
}
int** allocate_matrix(int n, int m, int style) {
    if (style == 1) {
        int** matrix = malloc(n * sizeof(int*) + n * m * sizeof(int));
        if (!matrix) return NULL;
        int* data = (int*)(matrix + n);
        for (int i = 0; i < n; i++) {
            matrix[i] = data + i * m;
        }
        return matrix;
    } else if (style == 2) {
        int** matrix = malloc(n * sizeof(int*));
        if (!matrix) return NULL;
        int* data = malloc(n * m * sizeof(int));
        if (!data) {
            free(matrix);
            return NULL;
        }
        for (int i = 0; i < n; i++) {
            matrix[i] = data + i * m;
        }
        return matrix;
    } else {
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
}

void free_matrix(int** matrix, int n, int style) {
    if (style == 1) {
        free(matrix);
    } else if (style == 2) {
        free(matrix[0]);
        free(matrix);
    } else {
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
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

void sort_matrix(int** matrix, int n, int m) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int sum1 = calculate_row_sum(matrix[j], m);
            int sum2 = calculate_row_sum(matrix[j + 1], m);
            if (sum1 > sum2) {
                int* temp = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = temp;
            }
        }
    }
}
int calculate_row_sum(const int* row, int m) {
    int sum = 0;
    for (int i = 0; i < m; i++) {
        sum += row[i];
    }
    return sum;
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