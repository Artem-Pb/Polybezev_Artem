#include "include.h"

int to_rpn(Token tokens[], int token_count, Token output[]) {
    Stack stack;
    init(&stack);
    int out_pos = 0;

    for (int i = 0; i < token_count; i++) {
        Token tok = tokens[i];

        if (tok.type == TYPE_NUMBER) {
            output[out_pos++] = tok;
        } else if (tok.type == TYPE_FUNCTION) {
            push(&stack, tok);
        } else if (tok.type == TYPE_OPERATOR) {
            while (!empty(&stack)) {
                Token top = peek(&stack);
                if ((top.type == TYPE_OPERATOR || top.type == TYPE_FUNCTION) && 
                ((get_priority_to_tok(&top) > get_priority_to_tok(&tok)) || 
                (get_priority_to_tok(&top) == get_priority_to_tok(&tok) && 
                is_left_associative(&tok)))) {
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
                Token top = pop(&stack);
                if (top.type == TYPE_LPAREN) {
                    found_lparen = 1;
                    break;
                } else {
                    output[out_pos++] = top;
                }
            }
            if (!found_lparen) {
                printf("Перепиши условие, скобки не сходятся!");
                return -1;
            }
            if (!empty(&stack)) {
                Token top = peek(&stack);
                if (top.type == TYPE_FUNCTION) {
                    output[out_pos++] = pop(&stack);
                }
            }
        }
    }

    while (!empty(&stack)) {
        Token top = pop(&stack);
        if (top.type == TYPE_LPAREN || top.type == TYPE_RPAREN) {
            printf("Перепиши условие, скобки не сходятся!");
            return -1;
        }
        output[out_pos++] = top;
    }
    return out_pos;
}