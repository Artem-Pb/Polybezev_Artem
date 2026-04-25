#ifndef DOUBLE_STACK_H
#define DOUBLE_STACK_H

#include "struct.h"

#define STACK_SIZE 100

typedef struct {
    double items[STACK_SIZE];
    int top;
} DoubleStack;

void init_double_stack(DoubleStack *s);
int empty_double_stack(const DoubleStack *s);
int push_double_stack(DoubleStack *s, double val);
double pop_double_stack(DoubleStack *s);

#endif