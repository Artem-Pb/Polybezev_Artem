/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/

#include <math.h>
#include <stdio.h>

#define NMAX 30

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int result);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == 1) {
        printf("n/a\n");
        return 0;
    }
    output(data, n);
    if (n == 0) {
        printf("0\n");
        return 0;
    }

    int result = 0;
    double mean_val = mean(data, n);
    double stddev_val = sqrt(variance(data, n));  // Corrected: standard deviation is sqrt(variance)

    for (int i = 0; i < n; i++) {
        int current = data[i];
        if (current % 2 == 0 && current >= mean_val && current >= mean_val - 3 * stddev_val &&
            current <= mean_val + 3 * stddev_val && current != 0) {
            result = current;
            break;
        }
    }

    output_result(result);

    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || *n > NMAX || *n < 0) {
        return 1;
    }

    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) != 1) {
            return 1;  // Input error
        }
    }

    return 0;
}

int min(int *a, int n) {
    int tmp = *a;
    for (int *p = a + 1; p - a < n; p++) {
        if (tmp > *p) {
            tmp = *p;
        }
    }
    return tmp;
}

int max(int *a, int n) {
    int tmp = *a;
    for (int *p = a + 1; p - a < n; p++) {
        if (tmp < *p) {
            tmp = *p;
        }
    }
    return tmp;
}

double mean(int *a, int n) {
    double res = 0.0;
    for (int *p = a; p - a < n; p++) {
        res += *p;
    }
    return res / n;
}

double variance(int *a, int n) {
    double avg = mean(a, n);
    double sum = 0.0;
    for (int *p = a; p - a < n; p++) {
        sum += pow(*p - avg, 2);
    }
    return sum / n;
}

void output(int *a, int n) {
    if (n == 0) {
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

void output_result(int result) { printf("%d\n", result); }
