#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "../data_libs/data_stat.h"
#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"
#include "sort.h"

int main() {
    int n = 0;
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("n/a");
        return 1;
    }
    double *data = NULL;
    data = malloc(n * sizeof(double));

    printf("LOAD DATA...\n");
    if (!input(data, n)) {
        free(data);
        return 1;
    }

    printf("RAW DATA:\n\t");
    output(data, n);

    printf("\nNORMALIZED DATA:\n\t");
    normalization(data, n);
    output(data, n);

    printf("\nSORTED NORMALIZED DATA:\n\t");
    sort(data, n);
    output(data, n);

    printf("\nFINAL DECISION:\n\t");
    make_decision(data, n);
    output(data, n);

    free(data);
    return 0;
}
