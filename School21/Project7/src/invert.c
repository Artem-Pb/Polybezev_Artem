#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int invert(double **matrix, int n);
int input(double **matrix, const int *n, const int *m);
void output(double **matrix, int n, int m);

int main() {
    int n, m;

    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0) {
        printf("n/a");
        return 0;
    }

    double **matrix = (double **)malloc(n * sizeof(double *));
    if (matrix == NULL) {
        printf("n/a");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(m * sizeof(double));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            printf("n/a");
            return 0;
        }
    }

    if (input(matrix, &n, &m) != 0) {
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
        printf("n/a");
        return 0;
    }

    if (n != m) {
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
        printf("n/a");
        return 0;
    }

    if (invert(matrix, n) != 0) {
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
        printf("n/a");
        return 0;
    }

    output(matrix, n, n);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

int input(double **matrix, const int *n, const int *m) {
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            if (scanf("%lf", &matrix[i][j]) != 1) {
                return -1;
            }
        }
    }
    return 0;
}

int invert(double **matrix, int n) {
    double **inverse = (double **)malloc(n * sizeof(double *));
    if (inverse == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        inverse[i] = (double *)calloc(n, sizeof(double));
        if (inverse[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(inverse[j]);
            }
            free(inverse);
            return -1;
        }
        inverse[i][i] = 1.0;
    }

    for (int i = 0; i < n; i++) {
        if (fabs(matrix[i][i]) < 1e-12) {
            int swap_row = -1;
            for (int k = i + 1; k < n; k++) {
                if (fabs(matrix[k][i]) > 1e-12) {
                    swap_row = k;
                    break;
                }
            }

            if (swap_row == -1) {
                for (int j = 0; j < n; j++) {
                    free(inverse[j]);
                }
                free(inverse);
                return -1;
            }

            double *temp = matrix[i];
            matrix[i] = matrix[swap_row];
            matrix[swap_row] = temp;

            temp = inverse[i];
            inverse[i] = inverse[swap_row];
            inverse[swap_row] = temp;
        }

        double pivot = matrix[i][i];
        for (int j = 0; j < n; j++) {
            matrix[i][j] /= pivot;
            inverse[i][j] /= pivot;
        }

        for (int k = 0; k < n; k++) {
            if (k != i && fabs(matrix[k][i]) > 1e-12) {
                double factor = matrix[k][i];
                for (int j = 0; j < n; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                    inverse[k][j] -= factor * inverse[i][j];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = inverse[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        free(inverse[i]);
    }
    free(inverse);

    return 0;
}

void output(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%.6lf", matrix[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        if (i < n - 1) {
            printf("\n");
        }
    }
}