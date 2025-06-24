#include <stdio.h>
#include <stdlib.h>

#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);
void print_picture(int **picture, int n, int m);

int main() {
    int picture_data[N][M];
    int *picture[N];
    transform((int *)picture_data, picture, N, M);

    make_picture(picture, N, M);
    print_picture(picture, N, M);

    return 0;
}

void make_picture(int **picture, int n, int m) {
    int frame_w[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int frame_h[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int tree_trunk[] = {7, 7, 7, 7};
    int tree_foliage[] = {3, 3, 3, 3};
    int sun_data[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                          {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    reset_picture(picture, n, m);

    for (int i = 0; i < m; i++) {
        picture[0][i] = frame_w[i % (sizeof(frame_w) / sizeof(frame_w[0]))];
        picture[n - 1][i] = frame_w[i % (sizeof(frame_w) / sizeof(frame_w[0]))];
    }
    for (int i = 0; i < n; i++) {
        picture[i][0] = frame_h[i % (sizeof(frame_h) / sizeof(frame_h[0]))];
        picture[i][m - 1] = frame_h[i % (sizeof(frame_h) / sizeof(frame_h[0]))];
    }

    for (int i = 2; i < 6; i++) {
        for (int j = 3; j < 7; j++) {
            picture[i][j] = tree_foliage[(i + j) % (sizeof(tree_foliage) / sizeof(tree_foliage[0]))];
        }
    }
    for (int i = 6; i < 10; i++) {
        picture[i][5] = tree_trunk[(i - 6) % (sizeof(tree_trunk) / sizeof(tree_trunk[0]))];
    }

    for (int i = 1; i < 7; i++) {
        for (int j = 7; j < 12; j++) {
            if (sun_data[i - 1][j - 7] != 0) {
                picture[i][j] = sun_data[i - 1][j - 7];
            }
        }
    }
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

void transform(int *buf, int **matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        matr[i] = buf + i * m;
    }
}

void print_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            switch (picture[i][j]) {
                case 0:
                    printf(" ");
                    break;
                case 1:
                    printf(".");
                    break;
                case 3:
                    printf("*");
                    break;
                case 6:
                    printf("O");
                    break;
                case 7:
                    printf("|");
                    break;
                default:
                    printf(" ");
            }
            if (j < m - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
}