#include <stdio.h>

#define LEN 100

void input(int *buffer, int *length);
void output(const int *buffer, int length);
void sum(const int *buff1, int len1, const int *buff2, int len2, int *result, int *result_length);
void sub(const int *buff1, int len1, const int *buff2, int len2, int *result, int *result_length);

int main() {
    int num1[LEN], num2[LEN], sum_result[LEN], sub_result[LEN];
    int len1, len2, sum_len, sub_len;

    input(num1, &len1);
    input(num2, &len2);

    sum(num1, len1, num2, len2, sum_result, &sum_len);
    output(sum_result, sum_len);

    sub(num1, len1, num2, len2, sub_result, &sub_len);
    if (sub_len == -1) {
        printf("n/a\n");
    } else {
        output(sub_result, sub_len);
    }

    return 0;
}

void input(int *buffer, int *length) {
    scanf("%d", length);
    for (int i = 0; i < *length; i++) {
        scanf("%d", &buffer[i]);
    }
}

void output(const int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            printf("%d", buffer[i]);
        } else {
            printf(" %d", buffer[i]);
        }
    }
    printf("\n");
}

void sum(const int *buff1, int len1, const int *buff2, int len2, int *result, int *result_length) {
    int max_len = len1 > len2 ? len1 : len2;
    int carry = 0;
    int i = len1 - 1, j = len2 - 1, k = max_len;

    while (i >= 0 || j >= 0 || carry) {
        int total = carry;
        if (i >= 0) total += buff1[i--];
        if (j >= 0) total += buff2[j--];

        result[--k] = total % 10;
        carry = total / 10;
    }

    *result_length = max_len + (k == 0 ? 1 : 0);
}

void sub(const int *buff1, int len1, const int *buff2, int len2, int *result, int *result_length) {
    if (len1 < len2 || (len1 == len2 && buff1[len1 - 1] < buff2[len2 - 1])) {
        *result_length = -1;
        return;
    }

    int borrow = 0;
    int i = len1 - 1, j = len2 - 1, k = len1 - 1;

    while (j >= 0) {
        int diff = buff1[i] - borrow;
        if (diff < buff2[j]) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[k--] = diff - buff2[j--];
    }

    while (k >= 0) {
        int diff = buff1[k] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[k--] = diff;
    }

    // Удаление ведущих нулей
    while (*result_length > 1 && result[*result_length - 1] == 0) {
        (*result_length)--;
    }
}
