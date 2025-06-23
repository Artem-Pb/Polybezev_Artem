#ifndef INPUT_H
#define INPUT_H
#include "include.h"

int is_function(const char* str);
int parse_expression(const char* expr, Token* tokens);
int to_rpn(Token tokens[], int token_count, Token output[]);

#endif
