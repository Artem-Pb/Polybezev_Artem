#include <stdio.h>

int print_field(int ball_x, int ball_y, int l_racket_x, int l_racket_y, int r_racket_x, int r_racket_y,
                int game_is_playing, int player_score_one, int player_score_two);
int player_one_move_racket(int l_racket_y, char ch);
int player_two_move_racket(int r_racket_y, char ch);
int end_game(int player_score_one, int player_score_two, int game_is_playing);

int main() {
    int game_is_playing = 1;
    int ball_x = 6;
    int ball_y = 13;
    int l_racket_x = 5;
    int l_racket_y = 12;
    int r_racket_x = 75;
    int r_racket_y = 12;
    int ball_vector_x = 1;
    int ball_vector_y = 1;
    int player_score_one = 0;
    int player_score_two = 0;

    while (game_is_playing) {
        if (game_is_playing == 0) {
            return 0;
        }
        game_is_playing = print_field(ball_x, ball_y, l_racket_x, l_racket_y, r_racket_x, r_racket_y,
                                      game_is_playing, player_score_one, player_score_two);

        char ch = getchar();
        if (ch != '\n') {
            getchar();
        }
        if ((ch == ' ' || ch == 'a' || ch == 'z')) {
            l_racket_y = (player_one_move_racket(l_racket_y, ch));
        }
        if ((ch == 'k' || ch == 'm')) {
            r_racket_y = (player_two_move_racket(r_racket_y, ch));
        }

        if ((ch == ' ' || ch == 'a' || ch == 'z') || (ch == 'k' || ch == 'm')) {
            ball_x += ball_vector_x;
            ball_y += ball_vector_y;

            if (ball_x == 6 && ball_y >= l_racket_y && ball_y < l_racket_y + 3) {
                ball_vector_x = -ball_vector_x;
            } else if (ball_x == 74 && ball_y >= r_racket_y && ball_y < r_racket_y + 3) {
                ball_vector_x = -ball_vector_x;
            }

            if (ball_y <= 1 || ball_y >= 23) {
                ball_vector_y = -ball_vector_y;
            }

            if (ball_x == 0) {
                player_score_two++;
                ball_x = 73;
                ball_y = 13;
            } else if (ball_x == 79) {
                player_score_one++;
                ball_x = 6;
                ball_y = 13;
            }
        }
    }
    return 0;
}

int print_field(int ball_x, int ball_y, int l_racket_x, int l_racket_y, int r_racket_x, int r_racket_y,
                int game_is_playing, int player_score_one, int player_score_two) {
    int width = 80;
    int height = 25;
    char border = '#';
    char vert = '|';
    char space = ' ';
    char ball = 'o';

    printf("\033c");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1) {
                printf("%c", border);
            } else if (j == 0 || j == width - 1) {
                printf("%c", border);
            } else if (j == ball_x && i == ball_y) {
                printf("%c", ball);
            } else if (j == 39) {
                printf("%c", vert);
            } else if ((j == l_racket_x) &&
                       ((i == l_racket_y) || (i == l_racket_y + 1) || (i == l_racket_y + 2))) {
                printf("%c", vert);
            } else if ((j == r_racket_x) &&
                       ((i == r_racket_y) || (i == r_racket_y + 1) || (i == r_racket_y + 2))) {
                printf("%c", vert);
            } else {
                printf("%c", space);
            }
        }
        printf("\n");
    }

    printf("1 player: %d\n2 player: %d\n", player_score_one, player_score_two);

    if (player_score_one == 21 || player_score_two == 21) {
        printf("%s",
               (player_score_one > player_score_two ? "First player wins!\n" : "Second player wins!\n"));
        return game_is_playing = 0;
    } else {
        return game_is_playing = 1;
    }
}

int player_one_move_racket(int l_racket_y, char ch) {
    if (ch == 'a') {
        if (l_racket_y >= 2) return l_racket_y - 1;
    } else if (ch == 'z') {
        if (l_racket_y <= 20) return l_racket_y + 1;
    }
    return l_racket_y;
}

int player_two_move_racket(int r_racket_y, char ch) {
    if (ch == 'k') {
        if (r_racket_y >= 2) return r_racket_y - 1;
    } else if (ch == 'm') {
        if (r_racket_y <= 20) return r_racket_y + 1;
    }
    return r_racket_y;
}
