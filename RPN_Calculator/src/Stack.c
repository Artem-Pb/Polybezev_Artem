#include "Stack.h"

void init(Stack *s) { s->top = -1; }

int empty(const Stack *s) { return s->top == -1; }

int push(Stack *s, TokenType tok) {
    if (s->top >= STACK_SIZE - 1) {
        return 0;
    }
    s->items[++s->top] = tok;
    return 1;
}
TokenType pop(Stack *s) {
    if (empty(s)) {
        TokenType empty_token = {"", -1, 0, -1};
        return empty_token;
    }
    return s->items[s->top--];
}

TokenType peek(Stack *s) {
    if (empty(s)) {
        TokenType empty_token = {"", -1, 0, -1};
        return empty_token;
    }
    return s->items[s->top];
}