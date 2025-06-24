#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int sle(double **matrix, int n, int m, double *roots);
void input(double **matrix, const int *n, const int *m);
void output_roots(const double *roots, int n);

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

    input(matrix, &n, &m);

    if (m != n + 1) {
        printf("n/a");
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 0;
    }

    double *roots = (double *)malloc(n * sizeof(double));
    if (roots == NULL) {
        printf("n/a");
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 0;
    }

    if (sle(matrix, n, m, roots) != 0) {
        printf("n/a");
    } else {
        output_roots(roots, n);
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(roots);

    return 0;
}

void input(double **matrix, const int *n, const int *m) {
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
}

int sle(double **matrix, int n, int m, double *roots) {
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
                return -1;
            }

            double *temp = matrix[i];
            matrix[i] = matrix[swap_row];
            matrix[swap_row] = temp;
        }

        for (int k = i + 1; k < n; k++) {
            double factor = matrix[k][i] / matrix[i][i];
            for (int j = i; j < m; j++) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        roots[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++) {
            roots[i] -= matrix[i][j] * roots[j];
        }
        roots[i] /= matrix[i][i];
    }

    return 0;
}

void output_roots(const double *roots, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.6lf", roots[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
}