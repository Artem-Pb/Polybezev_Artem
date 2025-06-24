#include <stdio.h>

int isPrime(long n) {
    if (n < 2) return 0;
    if (n == 2) return 1;

    long temp;
    for (long i = 2; i * i <= n; i++) {
        temp = n;
        while (temp >= i) temp -= i;
        if (temp == 0) return 0;
    }
    return 1;
}

long PND(long n) {
    if (n < 0) n = -n;
    long maxPrime = -1;
    for (long i = 2; i <= n; i++) {
        long temp = n;
        while (temp >= i) temp -= i;
        if (temp == 0 && isPrime(i)) {
            maxPrime = i;
        }
    }
    return maxPrime;
}

int main() {
    long n;
    if (scanf("%ld", &n) != 1) {
        printf("n/a\n");
        return 1;
    }
    printf("%ld\n", PND(n));
    return 0;
}
