#ifndef GRAPH_H
#define GRAPH_H

#include <math.h>
#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define X_MIN 0
#define X_MAX (4 * M_PI)
#define Y_MIN -1.0
#define Y_MAX 1.0

void calculate_y(double (*func)(double), char graph[HEIGHT][WIDTH]);
void draw_graph(const char graph[HEIGHT][WIDTH]);

#endif
