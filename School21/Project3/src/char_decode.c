#include <stdio.h>

int mod_0(void);  // кодирование (символ ->число)
int mod_1(void);  // декодирование (число -> число)

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("n/a\n");
        return 1;
    }
    if ((argv[1][0] != '0' && argv[1][0] != '1') || (argv[1][1] != '\0')) {
        printf("n/a\n");
        return 1;
    }

    if (argv[1][0] == '0') {
        return mod_0();

    } else if (argv[1][0] == '1') {
        return mod_1();

    } else {
        printf("n/a\n");
        return 1;
    }
}
int mod_1() {
    int x;
    char second;
    int flag = 0;
    while (1) {
        int res = scanf("%x%c", &x, &second);
        if (res == EOF) {
            break;
        }
        if (res != 2) {
            printf("n/a\n");
            return 1;
        }
        if (second == ' ' || second == '\n') {
            if (x >= 0 && x <= 126) {
                if (flag == 0) {
                    printf("%c", (char)x);
                    flag = 1;
                } else {
                    printf(" %c", (char)x);
                } 
            } else {
                printf("1n  n/a\n");
                return 1;
            }
        } else {
            printf("2n n/a\n");
            return 1;
        }

        if (second == '\n') {
            break;
        }
    }
    return 0;
}
int mod_0(void) {
    char c;
    char d;
    while (scanf("%c%c", &c, &d) == 2) {
        if (d == ' ') {
            printf("%X ", c);
        } else if (d == '\n') {
            printf("%X", c);
            return 0;
        } else {
            printf("n/a\n");
            return 1;
        }
    }
    return 0;
}
