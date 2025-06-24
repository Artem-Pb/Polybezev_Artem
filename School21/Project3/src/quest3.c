#include <stdio.h>

int fibonacci(int num);

int main() {
    int num;
    if (scanf("%d", &num) == 1) {
        int result = fibonacci(num);
        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("n/a\n");
        }
        return 0;
    } else {
        printf("n/a\n");
    }
}

int fibonacci(int num) {
    if (num <= 0) {
        return -1;
    } else if (num == 1 || num == 2) {
        return 1;
    } else {
        return fibonacci(num - 1) + fibonacci(num - 2);
    }
}
