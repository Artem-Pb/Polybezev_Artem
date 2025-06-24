#include <math.h>
#include <stdio.h>

int main() {
    int count = 42;
    double start = -3.1415927;
    double end = 3.1415927;
    double step = (end - start) / (count - 1);

    int i = 0;
    while (i < count) {
        double x = start + i * step;
        double v;
        if ((pow(1, 2) + pow(x, 2) > 0)) {
            v = pow(1, 3) / (pow(1, 2) + pow(x, 2));
        }
        double l;
        if (x > 1 || x < -1) {
            l = -1.0;
        } else {
            l = sqrt(1.0 - x * x);
        }

        double h;
        if (x == 0.0) {
            h = -1.0;
        } else {
            h = 1.0 / (x * x);
        }

        printf("% .7f | % .7f | ", x, v);

        if (l < 0.0) {
            printf("-       | ");
        } else {
            printf("%.7f | ", l);
        }

        if (h < 0.0) {
            printf("-\n");
        } else {
            printf("%.7f\n", h);
        }

        i++;
    }
    return 0;
}
