#include <stdio.h>

void sort(int *a, int n);
int input(int *a, int n);
void output(int *a, int n);

int main() {
    const int size = 10;
    int a[size];
    input(a, size);
    sort(a, size);
    output(a, size);
    return 0;
}

int input(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        if (scanf("%d", p) != 1) {
            printf("n/a");
            return -1;
        }
    }

    return 0;
}

void sort(int *a, int n) {
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        if (p == a) {
            printf("%d", *p);
        } else {
            printf(" %d", *p);
        }
    }
}
