#include "parser.h"

#include <stdio.h>
#include <string.h>

#include "type.h"

int is_function(const char *str) {
    const char *funcs[] = {"sin", "cos", "tan", "log", "exp", "sqrt"};
    for (int i = 0; i < 6; i++) {
        if (strcmp(str, funcs[i]) == 0) return 1;
    }
    return 0;
}

int parse_expression(const char *src, TokenType *tokens) {
    int len = strlen(src);
    int i = 0, token_count = 0;
    int expect_unary = 1;

    while (i < len) {
        if (isspace(src[i])) {
            i++;
            continue;
        }

        TokenType token = {"", TYPE_NUMBER, 0, 0};

        if (isdigit(src[i]) || src[i] == '.') {
            int j = 0;
            while (i < len && (isdigit(src[i]) || src[i] == '.')) {
                if (j < MAX_TOKEN_LEN - 1)
                    token.value[j++] = src[i++];
                else
                    i++;
            }
            token.value[j] = '\0';
            token.type = TYPE_NUMBER;
            token.priority = 0;
            token.is_unary = 0;
            expect_unary = 0;
        } else if (isalpha(src[i])) {
            int j = 0;
            while (i < len && isalpha(src[i])) {
                if (j < MAX_TOKEN_LEN - 1)
                    token.value[j++] = src[i++];
                else
                    i++;
            }
            token.value[j] = '\0';

            if (is_function(token.value)) {
                token.type = TYPE_FUNCTION;
                token.priority = 5;
                token.is_unary = 0;
            } else if (strcmp(token.value, "x") == 0) {
                token.type = TYPE_VARIABLE;
                token.priority = 0;
                token.is_unary = 0;
            } else {
                token.type = TYPE_VARIABLE;
                token.priority = 0;
                token.is_unary = 0;
            }
            expect_unary = 0;
        } else {
            if (src[i] == '(') {
                token.value[0] = '(';
                token.value[1] = '\0';
                token.type = TYPE_LPAREN;
                token.priority = 0;
                token.is_unary = 0;
                i++;
                expect_unary = 1;
            } else if (src[i] == ')') {
                token.value[0] = ')';
                token.value[1] = '\0';
                token.type = TYPE_RPAREN;
                token.priority = 0;
                token.is_unary = 0;
                i++;
                expect_unary = 0;
            } else if (src[i] == '-' && expect_unary) {
                strcpy(token.value, "u-");
                token.type = TYPE_OPERATOR;
                token.priority = 4;
                token.is_unary = 1;
                i++;
                expect_unary = 1;
            } else {
                token.value[0] = src[i++];
                token.value[1] = '\0';
                token.type = TYPE_OPERATOR;
                token.priority = 0;
                token.is_unary = 0;
                expect_unary = 1;
            }
        }

        if (token_count < MAX_LEXEMS) {
            tokens[token_count++] = token;
        } else {
            printf("Ошибка: слишком много токенов\n");
            break;
        }
    }

    return token_count;
}
