#include <math.h>
#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    input(data, &n);
    output(data, n);
    if (n == 0) {
        return 1;
    }
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1) {
        return 1;
    } else {
        for (int *p = a; p - a < *n; p++) {
            scanf("%d", p);
        }
    }

    return 0;
}

int min(int *a, int n) {
    int tmp = *a;

    for (int *p = a; p - a < n; p++) {
        if (tmp > *p) {
            tmp = *p;
        }
    }

    return tmp;
}

int max(int *a, int n) {
    int tmp = *a;

    for (int *p = a; p - a < n; p++) {
        if (tmp < *(p)) {
            tmp = *(p);
        }
    }

    return tmp;
}

double mean(int *a, int n) {
    int res = 0;
    for (int *p = a; p - a < n; p++) {
        res += *p;
    }

    return (double)res / (double)n;
}

double variance(int *a, int n) {
    double result = pow(mean(a, n), 2);
    double sum = 0.0;
    for (int *p = a; p - a < n; p++) {
        sum += pow(*p, 2);
    }
    sum /= n;

    return sum - result;
}

void output(int *a, int n) {
    if (n == 0) {
        printf("n/a");
        return;
    }
    for (int *p = a; p - a < n; p++) {
        if (p == a) {
            printf("%d", *p);
        } else {
            printf(" %d", *p);
        }
    }

    printf("\n");
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d", max_v, min_v);

    printf(" %.6lf", mean_v);

    printf(" %.6lf", variance_v);
}
