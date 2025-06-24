#include "data_stat.h"

#include <math.h>
#include <stdlib.h>

double min(double *data, int n) {
    double tmp = data[0];

    for (int i = 0; i < n; i++) {
        if (tmp > data[i]) {
            tmp = data[i];
        }
    }

    return tmp;
}

double max(double *data, int n) {
    double tmp = data[0];

    for (int i = 0; i < n; i++) {
        if (tmp < data[i]) {
            tmp = data[i];
        }
    }

    return tmp;
}

double mean(double *data, int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += data[i];
    }

    return (double)res / (double)n;
}

double variance(double *data, int n) {
    double result = pow(mean(data, n), 2);
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += pow(data[i], 2);
    }
    sum /= n;

    return sum - result;
}