#include <stdio.h>

int isGotcha(double x, double y);

int main() {
    double x, y;
    if (scanf("%lf %lf",&x, &y) != 2) {
        printf("n/a\n");
        return 1;
    }

    isGotcha(x, y);

}

int isGotcha(double x, double y) {
    if (x > 1e8 || x < -1e8 || y > 1e8 || y < -1e8) {
        printf("n/a\n");
        return 1;
    }

    double sum = x * x + y * y;
    double epsilon = 1e-6;

    if (sum - 25 > epsilon) {
        printf("MISS\n");
        return 1;
    } else if (sum - 25 < -epsilon) {
        printf("GOTCHA\n");
        return 0;
    } else {
        printf("MISS\n");
        return 1;
    }
}
