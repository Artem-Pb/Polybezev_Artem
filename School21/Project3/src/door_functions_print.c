#include <math.h>
#include <stdio.h>

void graphDraw(int count, int height, double maxY, double minY, double start, double end, double (*func)(double));

double ascer(double x) {
    if ((pow(1, 2) + pow(x, 2) > 0)) {
        return pow(1, 3) / (pow(1, 2) + pow(x, 2));
    } else {
        return -1.0; // Укажите значение для случая, когда функция не определена
    }
}

double bernull(double x) {
    if (x > 1 || x < -1) {
        return -1.0;
    } else {
        return sqrt(1.0 - x * x);
    }
}

double parab(double x) {
    if (x == 0.0) {
        return -1.0;
    } else {
        return 1.0 / (x * x);
    }
}

int main() {
    int count = 42; // Масштаб по оси абсцисс
    int height = 21; // Масштаб по оси ординат
    double start = -3.1415927; // Начало интервала
    double end = 3.1415927; // Конец интервала
    double step = (end - start) / (count - 1);
    double maxY = -1e9; // Максимальное значение по оси Y
    double minY = 1e9; // Минимальное значение по оси Y

    for (int i = 0; i < count; i++) {
        double x = start + i * step;

        double ascerVal = ascer(x);
        double bernullVal = bernull(x);
        double parabVal = parab(x);

        if (ascerVal > maxY) maxY = ascerVal;
        if (ascerVal < minY) minY = ascerVal;
        if (bernullVal > maxY) maxY = bernullVal;
        if (bernullVal < minY) minY = bernullVal;
        if (parabVal > maxY) maxY = parabVal;
        if (parabVal < minY) minY = parabVal;

        printf("% .7f | % .7f | ", x, ascerVal);

        if (bernullVal < 0.0) {
            printf("-      | ");
        } else {
            printf("%.7f | ", bernullVal);
        }

        if (parabVal < 0.0) {
            printf("-\n");
        } else {
            printf("%.7f\n", parabVal);
        }
    }


    graphDraw(count, height, maxY, minY, start, end, ascer);


    graphDraw(count, height, maxY, minY, start, end, bernull);


    graphDraw(count, height, maxY, minY, start, end, parab);

    return 0;
}

void graphDraw(int count, int height, double maxY, double minY, double start, double end, double (*func)(double)) {
    double step = (end - start) / (count - 1);

    for (int row = 0; row < height; row++) {
        double levelTop = maxY - (double)row * (maxY - minY) / (height - 1);
        double levelBottom = levelTop - (maxY - minY) / (height - 1);
        for (int i = 0; i < count; i++) {
            double x = start + i * step;
            double funcVal = func(x);

            if (funcVal != -1 && funcVal <= levelTop && funcVal >= levelBottom) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}
