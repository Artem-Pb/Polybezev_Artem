#include "graph.h"

void calculate_y(double (*func)(double), char graph[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            graph[i][j] = '.';
        }
    }

    for (int col = 0; col < WIDTH; col++) {
        double x = X_MIN + col * (X_MAX - X_MIN) / (WIDTH - 1);
        double y = func(x);

        int row = (int)round((y - Y_MIN) / (Y_MAX - Y_MIN) * (HEIGHT - 1));

        if (row >= 0 && row < HEIGHT) {
            graph[row][col] = '*';
        }
    }
}

void draw_graph(const char graph[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            putchar(graph[i][j]);
        }
        putchar('\n');
    }
}