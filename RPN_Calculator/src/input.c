#include "include.h"

int is_function(const char* str) {
    const char *funcs[] = {"sin", "cos", "tan", "log", "exp", "sqrt"};
    for (int i = 0; i < 6; i++) {
        if (strcmp(str, funcs[i]) == 0) return 1;
    }
    return 0;
}

int parse_expression(const char* expr, TokenType* tokens) {
    int len = strlen(expr);
    int i = 0, token_count = 0;
    int expect_unary = 1;

    while (i < len) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        TokenType token = {"", TYPE_NUMBER, 0, 0};

        if (isdigit(expr[i]) || expr[i] == '.') {
            int j = 0;
            while (i < len && (isdigit(expr[i]) || expr[i] == '.')) {
                if (j < MAX_TOKEN_LEN - 1) {
                    token.value[j++] = expr[i++];
                } else {
                    i++;
                }
            }
            token.value[j] = '\0';
            token.type = TYPE_NUMBER;
            token.priority = 0;
            token.is_unary = 0;
            expect_unary = 0;
        }
        else if (isalpha(expr[i])) {
            int j = 0;
            while (i < len && isalpha(expr[i])) {
                if (j < MAX_TOKEN_LEN - 1) {
                    token.value[j++] = expr[i++];
                } else {
                    i++;
                }
            }
            token.value[j] = '\0';

            if (is_function(token.value)) {
                token.type = TYPE_FUNCTION;
                token.priority = 5;
                token.is_unary = 0;
            } else if (strcmp(token.value, "x") == 0) {
                token.type = TYPE_VARIBLE;
                token.priority = 0;
                token.is_unary = 0;
            } else {
                token.type = TYPE_VARIBLE;
                token.priority = 0;
                token.is_unary = 0;
            }
            expect_unary = 0;
        }
        else {
            if (expr[i] == '-' && expect_unary) {
                strcpy(token.value, "u-");
                token.type = TYPE_OPERATOR;
                token.priority = 4; 
                token.is_unary = 1;
                i++;
            } else {
                token.value[0] = expr[i++];
                token.value[1] = '\0';
                token.type = TYPE_OPERATOR;
                token.priority = get_priority_to_tok(&token);
                token.is_unary = 0;
            }
            expect_unary = 1;
        }

        if (token_count < MAX_LEXEMS) {
            tokens[token_count++] = token;
        } else {
            
            fprintf(stderr, "Ошибка: слишком много токенов\n");
            break;
        }
    }

    return token_count;
}
