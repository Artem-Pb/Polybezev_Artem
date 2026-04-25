#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define ROWS 25
#define COLS 80
#define LIVE_CELL "\033[38;5;46m\u25CF\033[0m"
#define DEAD_CELL "\033[48;5;236m \033[0m"
#define BORDER_COLOR "\033[38;5;245m"
#define HUD_COLOR "\033[38;5;250m"

void create_matrix(int arr[][COLS]);
void clear_screen();
int searchNeighbors(int arr[][COLS], int x, int y);
void render(const int matrix[][COLS], int rows, int cols, int generation, int delay);
void read_from_file(int matrix[][COLS], int rows, int cols);
int kbhit();
void check_user_input(int *game_status, int *delay, int *speed_count);
int life_or_dead(const int matrix[ROWS][COLS]);

int main() {
    int matrix[ROWS][COLS] = {0};

    int generation = 0;

    read_from_file(matrix, ROWS, COLS);
    int delay = 500;
    int speed_count = 1;
    int is_running = 1;

    system("stty -icanon -echo");

    while (is_running) {
        create_matrix(matrix);
        render(matrix, ROWS, COLS, generation, speed_count);
        if (kbhit()) {
            check_user_input(&is_running, &delay, &speed_count);
        }
        if (life_or_dead(matrix) == 1) {
            is_running = 0;
        }
        generation++;
        usleep((unsigned int)delay * 1000);
    }

    system("stty icanon echo");
    return 0;
}

int kbhit() {
    int bytes;
    ioctl(STDIN_FILENO, FIONREAD, &bytes);
    return bytes > 0;
}

void read_from_file(int matrix[][COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            while (1) {
                char c = getchar();
                if (c == '0' || c == '1') {
                    matrix[i][j] = (c == '1') ? 1 : 0;
                    break;
                }
            }
        }
        getchar();
    }
    (void)freopen("/dev/tty", "r", stdin);
}

void create_matrix(int arr[][COLS]) {
    int new_arr[ROWS][COLS] = {0};

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = searchNeighbors(arr, i, j);
            if (arr[i][j] == 1) {
                new_arr[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                new_arr[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            arr[i][j] = new_arr[i][j];
        }
    }
}

int searchNeighbors(int arr[][COLS], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int nx = (x + i + ROWS) % ROWS;
            int ny = (y + j + COLS) % COLS;
            count += arr[nx][ny];
        }
    }
    return count;
}
void render(const int matrix[][COLS], int rows, int cols, int generation, int delay) {
    clear_screen();
    printf(BORDER_COLOR "┌");
    for (int j = 0; j < cols; j++) printf("─");
    printf("┐\n");

    for (int i = 0; i < rows; i++) {
        printf(BORDER_COLOR "│");
        for (int j = 0; j < cols; j++) {
            printf(matrix[i][j] ? LIVE_CELL : DEAD_CELL);
        }
        printf(BORDER_COLOR "│\n");
    }

    printf(BORDER_COLOR "└");
    for (int j = 0; j < cols; j++) printf("─");
    printf("┘\n");

    printf(HUD_COLOR " Generation: %d | Speed: %dx | [Q] Выход [+/-]\n", generation, delay);
}

void clear_screen() { printf("\033[2J\033[H"); }

void check_user_input(int *game_status, int *delay, int *speed_count) {
    char input = getchar();
    if (input == 'q') {
        *game_status = 0;
    }
    if (input == '-') {
        *delay += 100;
        *speed_count -= 1;
        if (*delay > 1000) {
            *delay = 1000;
            *speed_count = 1;
        }
    }
    if (input == '+') {
        *delay -= 100;
        *speed_count += 1;
    }

    if (*delay < 100) {
        *delay = 100;
        *speed_count = 10;
    }
}

int life_or_dead(const int matrix[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matrix[i][j] == 1) {
                return 0;
            }
        }
    }

    return 1;
}
