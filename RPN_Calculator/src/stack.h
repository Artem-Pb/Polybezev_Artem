#ifndef STACK_H
#define STACK_H

#include "struct.h"

#define STACK_SIZE 100

typedef struct {
    Token items[STACK_SIZE];
    int top;
} Stack;

void stack_init(Stack *s);
int stack_empty(Stack *s);
int stack_push(Stack *s, Token tok);
Token stack_pop(Stack *s);
Token stack_peek(Stack *s);

#endif
