#include "double_stack.h"

void init_double_stack(DoubleStack *s) { s->top = -1; }
int empty_double_stack(const DoubleStack *s) { return s->top == -1; }
int push_double_stack(DoubleStack *s, double val) {
    if (s->top >= STACK_SIZE - 1) return 0;
    s->items[++s->top] = val;
    return 1;
}
double pop_double_stack(DoubleStack *s) {
    if (empty_double_stack(s)) return 0.0;
    return s->items[s->top--];
}