#include <stdio.h>

#define MAX_SIZE 10

void input(int *buffer, int *length);
void output(const int *buffer, int length);
int sum_numbers(const int *buffer, int length);
int find_numbers(const int *buffer, int length, int number, int *numbers);

int main() {
    int buffer[MAX_SIZE], numbers[MAX_SIZE], length;

    input(buffer, &length);

    int sum = sum_numbers(buffer, length);
    if (sum == 0) {
        printf("n/a");
        return 0;
    }

    int count = find_numbers(buffer, length, sum, numbers);
    if (count == 0) {
        printf("n/a");
        return 0;
    }

    printf("%d\n", sum);
    output(numbers, count);

    return 0;
}

void input(int *buffer, int *length) {
    if (scanf("%d", length) != 1 || *length <= 0 || *length > MAX_SIZE) {
        *length = 0;
        return;
    }

    for (int i = 0; i < *length; i++) {
        if (scanf("%d", &buffer[i]) != 1) {
            *length = 0;
            return;
        }
    }
}

void output(const int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", buffer[i]);
        if (i < length - 1) {
            printf(" ");
        }
    }
}

int sum_numbers(const int *buffer, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0 && buffer[i] != 0) {
            sum += buffer[i];
        }
    }
    return sum;
}

int find_numbers(const int *buffer, int length, int number, int *numbers) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[count] = buffer[i];
            count++;
        }
    }
    return count;
}
