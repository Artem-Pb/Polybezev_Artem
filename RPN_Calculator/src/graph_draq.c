#include "include.h"

void draw_graph() {
    char screen[HEIGHT][WIDTH];

  
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            screen[y][x] = '.';
        }
    }


    double step_x = (X_MAX - X_MIN) / WIDTH;

    for (int i = 0; i < WIDTH; i++) {
        double x = X_MIN + i * step_x;
        double y = evaluate_rpn(x);


        if (y < Y_MIN || y > Y_MAX) continue;

        int screen_y = (int)round((y - Y_MIN) / (Y_MAX - Y_MIN) * (HEIGHT - 1));
        

        screen_y = HEIGHT - 1 - screen_y;

        if (screen_y >= 0 && screen_y < HEIGHT) {
            screen[screen_y][i] = '*';
        }
    }


    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            putchar(screen[y][x]);
        }
        putchar('\n');
    }
}