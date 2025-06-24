#include <stdio.h>

int max(int a, int b);

int main() {
    int a, b;
    while (scanf("%d %d", &a, &b) != 2) {
        printf("n/a\n");
        return 1;
    }
    printf("%d", max(a, b));
    return 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

