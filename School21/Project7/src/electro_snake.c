#include <stdio.h>
#include <stdlib.h>

void sort_vertical(int **matrix, int n, int m, int **result_matrix);
void sort(int *matrix, int n);
void sort_horizontal(int **matrix, int n, int m, int **result_matrix);

void input(int **matrix, int n, int m);
void output(int **matrix, int n, int m);

int main() {
    int **matrix = NULL, **result = NULL;
    int n, m;

    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0) {
        printf("n/a");
        return 1;
    }

    matrix = (int **)malloc(n * sizeof(int *));
    result = (int **)malloc(n * sizeof(int **));

    if (matrix == NULL || result == NULL) {
        printf("n/a");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(sizeof(int *) * m);
        result[i] = (int *)malloc(sizeof(int *) * m);
        if (matrix[i] == NULL || result[i] == NULL) {
            printf("n/a");
            return 1;
        }
    }

    input(matrix, n, m);

    sort_vertical(matrix, n, m, result);
    output(result, n, m);

    printf("\n");

    sort_horizontal(matrix, n, m, result);
    output(result, n, m);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
        free(result[i]);
    }

    free(matrix);
    free(result);
    return 0;
}

void input(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("n/a");
                exit(1);
            }
        }
    }
}

void output(int **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", matrix[i][j]);
            if (j < m - 1) printf(" ");
        }
        printf("\n");
    }
}

void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    int total = n * m;
    int index = 0;
    int *temp = (int *)malloc(total * sizeof(int));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp[index++] = matrix[i][j];
        }
    }

    sort(temp, total);
    index = 0;

    for (int j = 0; j < m; j++) {
        if (j % 2 == 0) {
            for (int i = 0; i < n; i++) {
                result_matrix[i][j] = temp[index++];
            }
        } else {
            for (int i = n - 1; i >= 0; i--) {
                result_matrix[i][j] = temp[index++];
            }
        }
    }

    free(temp);
}

void sort_horizontal(int **matrix, int n, int m, int **result) {
    int total = n * m;
    int *temp = (int *)malloc(total * sizeof(int));
    int index = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp[index++] = matrix[i][j];
        }
    }

    sort(temp, total);
    index = 0;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++) {
                result[i][j] = temp[index++];
            }
        } else {
            for (int j = m - 1; j >= 0; j--) {
                result[i][j] = temp[index++];
            }
        }
    }

    free(temp);
}

void sort(int *matrix, int n) {
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (matrix[j] > matrix[j + 1]) {
                int tmp = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = tmp;
            }
        }
    }
}
