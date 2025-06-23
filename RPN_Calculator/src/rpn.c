#include "rpn.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"
#include "double_stack.h"

int get_priority_to_tok(TokenType *token) {
    if (token->type == TYPE_FUNCTION) return 5;
    if (token->type != TYPE_OPERATOR) return 0;

    if (strcmp(token->value, "u-") == 0) return 4;

    char op = token->value[0];
    switch (op) {
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case '^':
            return 4;
        default:
            return 0;
    }
}

int is_left_associative(TokenType *token) {
    if (token->type != TYPE_OPERATOR) return 0;
    char op = token->value[0];
    return (op != '^');
}

int to_rpn(TokenType tokens[], int token_count, TokenType output[]) {
    Stack stack;
    init(&stack);
    int out_pos = 0;

    for (int i = 0; i < token_count; i++) {
        TokenType tok = tokens[i];

        if (tok.type == TYPE_NUMBER || tok.type == TYPE_VARIABLE) {
            output[out_pos++] = tok;
        } else if (tok.type == TYPE_FUNCTION) {
            push(&stack, tok);
        } else if (tok.type == TYPE_OPERATOR) {
            while (!empty(&stack)) {
                TokenType top = peek(&stack);
                if ((top.type == TYPE_OPERATOR || top.type == TYPE_FUNCTION) &&
                    ((get_priority_to_tok(&top) > get_priority_to_tok(&tok)) ||
                     (get_priority_to_tok(&top) == get_priority_to_tok(&tok) && is_left_associative(&tok)))) {
                    output[out_pos++] = pop(&stack);
                } else {
                    break;
                }
            }
            push(&stack, tok);
        } else if (tok.type == TYPE_LPAREN) {
            push(&stack, tok);
        } else if (tok.type == TYPE_RPAREN) {
            int found_lparen = 0;
            while (!empty(&stack)) {
                TokenType top = pop(&stack);
                if (top.type == TYPE_LPAREN) {
                    found_lparen = 1;
                    break;
                } else {
                    output[out_pos++] = top;
                }
            }
            if (!found_lparen) {
                fprintf(stderr, "Ошибка: несоответствие скобок!\n");
                return -1;
            }
            if (!empty(&stack)) {
                TokenType top = peek(&stack);
                if (top.type == TYPE_FUNCTION) {
                    output[out_pos++] = pop(&stack);
                }
            }
        }
    }

    while (!empty(&stack)) {
        TokenType top = pop(&stack);
        if (top.type == TYPE_LPAREN || top.type == TYPE_RPAREN) {
            fprintf(stderr, "Ошибка: несоответствие скобок!\n");
            return -1;
        }
        output[out_pos++] = top;
    }
    return out_pos;
}

double evaluate_rpn(TokenType rpn_tokens[], int token_count, double x) {
    DoubleStack stack;
    init_double_stack(&stack);

    for (int i = 0; i < token_count; i++) {
        TokenType token = rpn_tokens[i];

        if (token.type == TYPE_NUMBER) {
            double val = atof(token.value);
            push_double_stack(&stack, val);
        } else if (token.type == TYPE_VARIABLE && strcmp(token.value, "x") == 0) {
            push_double_stack(&stack, x);
        } else if (token.type == TYPE_OPERATOR) {
            double b = pop_double_stack(&stack);
            double a = pop_double_stack(&stack);
            double result = 0;

            switch (token.value[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
                case '^':
                    result = pow(a, b);
                    break;
                default:
                    printf("Ошибка: неизвестный оператор %s\n", token.value);
                    return 0.0;
            }
            push_double_stack(&stack, result);
        } else if (token.type == TYPE_FUNCTION) {
            double a = pop_double_stack(&stack);
            double result = 0;

            if (strcmp(token.value, "sin") == 0)
                result = sin(a);
            else if (strcmp(token.value, "cos") == 0)
                result = cos(a);
            else if (strcmp(token.value, "tan") == 0)
                result = tan(a);
            else if (strcmp(token.value, "log") == 0)
                result = log(a);
            else if (strcmp(token.value, "exp") == 0)
                result = exp(a);
            else if (strcmp(token.value, "sqrt") == 0)
                result = sqrt(a);
            else {
                printf("Ошибка: неизвестная функция %s\n", token.value);
                return 0.0;
            }
            push_double_stack(&stack, result);
        }
    }

    if (!empty_double_stack(&stack)) {
        return pop_double_stack(&stack);
    }
    return 0.0;
}
