#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n);
void input(double **matrix, int n, int m);
void output(double det);

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m <= 0) {
        printf("n/a");
        return 0;
    }

    if (n != m) {
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

    input(matrix, n, m);

    double determinant = det(matrix, n);
    output(determinant);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

void input(double **matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%lf", &matrix[i][j]) != 1) {
                for (int k = 0; k <= i; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                printf("n/a");
                exit(0);
            }
        }
    }
}

double det(double **matrix, int n) {
    double det = 1.0;
    for (int i = 0; i < n; i++) {
        if (fabs(matrix[i][i]) < 1e-12) {
            int swap_row = -1;
            for (int k = i + 1; k < n; k++) {
                if (fabs(matrix[k][i]) > 1e-12) {
                    swap_row = k;
                    break;
                }
            }
            if (swap_row == -1) return 0.0;

            double *temp = matrix[i];
            matrix[i] = matrix[swap_row];
            matrix[swap_row] = temp;
            det *= -1;
        }

        for (int j = i + 1; j < n; j++) {
            double ratio = matrix[j][i] / matrix[i][i];
            for (int k = 0; k < n; k++) {
                matrix[j][k] -= ratio * matrix[i][k];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        det *= matrix[i][i];
    }
    return det;
}

void output(double det) { printf("%.6lf", det); }
