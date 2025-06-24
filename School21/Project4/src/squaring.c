#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    input(data, &n);
    squaring(data, n);
    if (n == 0) {
        printf("n/a");
        return 1;
    }
    output(data, n);
    return 0;
}

int input(int *a, int *n) {
    if (scanf("%d", n) != 1) {
        printf("n/a");
        return -1;
    } else {
        for (int *p = a; p - a < *n; p++) {
            scanf("%d", p);
        }

        return 0;
    }
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
}

void squaring(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        *p = (*p) * (*p);
    }
}
