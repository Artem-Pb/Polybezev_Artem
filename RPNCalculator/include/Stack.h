#ifndef STACK_H
#define STACK_H

#include "struct.h"

#define STACK_SIZE 100

typedef struct {
    TokenType items[STACK_SIZE];
    int top;
} Stack;

void init(Stack *s);
int empty(const Stack *s);
int push(Stack *s, TokenType tok);
TokenType pop(Stack *s);
TokenType peek(Stack *s);

#endif