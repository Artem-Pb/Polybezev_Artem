#include <stdio.h>

int sum(int a, int b);

int main()
{
    int a, b;
    while (scanf("%d %d", &a, &b) != 2) {
        printf("n/a\n ");
        return 1; 
    }
    sum(a, b);
    return 0;
}

int sum(int a, int b){
    printf("%d %d %d ", a + b, a - b, a * b);

    if (b == 0) {
        printf("n/a\n");
    } else {
        printf("%d", a / b);
    }
    return 0;
}
