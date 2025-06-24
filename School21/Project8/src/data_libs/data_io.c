#include "data_io.h"

#include <stdio.h>

#include "../data_libs/data_stat.h"

int input(double *a, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &a[i]) != 1) {
            while (getchar() != '\n');
            printf("n/a");
            return 0;
        }
    }
    return 1;
}

void output(double *a, int n) {
    if (n == 0) {
        printf("n/a");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            printf("%.2f", a[i]);
        } else {
            printf(" %.2f", a[i]);
        }
    }
    printf("\n");
}