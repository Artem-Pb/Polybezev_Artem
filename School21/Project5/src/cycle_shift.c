#include <stdio.h>

#define MAX_SIZE 10

void input(int *n, int *arr, int *shift);
void output(const int *arr, int n);
void cycle_shift(int *arr, int n, int shift);
void shift_left(int *arr, int n, int shift);
void shift_right(int *arr, int n, int shift);

int main() {
    int n, shift;
    int arr[MAX_SIZE];

    input(&n, arr, &shift);

    cycle_shift(arr, n, shift);
    output(arr, n);

    return 0;
}

void input(int *n, int *arr, int *shift) {
    if (scanf("%d", n) != 1 || *n <= 0 || *n > MAX_SIZE) {
        printf("n/a");
        return;
    }

    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("n/a");
            return;
        }
    }

    if (scanf("%d", shift) != 1) {
        printf("n/a");
        return;
    }
}

void output(const int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
}

void cycle_shift(int *arr, int n, int shift) {
    shift %= n;
    if (shift < 0) {
        shift_right(arr, n, -shift);
    } else {
        shift_left(arr, n, shift);
    }
}

void shift_left(int *arr, int n, int shift) {
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++) {
        temp[i] = arr[(i + shift) % n];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
}

void shift_right(int *arr, int n, int shift) {
    int temp[MAX_SIZE];
    for (int i = 0; i < n; i++) {
        temp[(i + shift) % n] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
}
