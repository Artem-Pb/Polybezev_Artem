#include <stdio.h>

void mergeSort(int *a, int n, int left, int right, int *temp);
void merge(int *a, int left, int right, int mid, int *temp);
void swap(int *a, int *b);
int partition(int *b, int low, int high);
void quickSort(int *a, int low, int high);
int input(int *a, int n);
void output(const int *a, int n);

int main() {
    const int n = 10;
    int a[n]; 
    int temp[n];

    if (input(a, n) == 1) {
        printf("n/a");
        return 1;
    } else {
        int b[n];
        for (int i = 0; i < n; i++) {
            b[i] = a[i];
        }

        quickSort(b, 0, n - 1);
        output(b, n);
        printf("\n");
    }

    mergeSort(a, n, 0, n - 1, temp);
    output(a, n);
    return 0;
}

int input(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            return 1;
        }
    }
    return 0;
}


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void mergeSort(int *a, int n, int left, int right, int *temp) {
    if (left < 0 || right >= n) {
        printf("n/a");
        return;
    }

    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(a, n, left, mid, temp);
        mergeSort(a, n, mid + 1, right, temp);

        merge(a, left, right, mid, temp);
    }
}

int partition(int *b, int low, int high) {
    int pivot = b[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (b[j] <= pivot) {
            i++;
            swap(&b[i], &b[j]);
        }
    }

    swap(&b[i + 1], &b[high]);
    return i + 1;
}

void quickSort(int *b, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(b, low, high);

        quickSort(b, low, pivotIndex - 1);
        quickSort(b, pivotIndex + 1, high);
    }
}

void merge(int *a, int left, int right, int mid, int *temp) {
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = a[i++];
    }

    while (j <= right) {
        temp[k++] = a[j++];
    }

    for (i = left; i <= right; i++) {
        a[i] = temp[i - left];
    }
}

void output(const int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            printf("%d", a[i]);
        } else {
            printf(" %d", a[i]);
        }
    }
}
