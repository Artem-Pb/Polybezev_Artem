#ifndef RPN_H
#define RPN_H

#include "struct.h"

int to_rpn(TokenType tokens[], int token_count, TokenType output[]);
double evaluate_rpn(TokenType rpn_tokens[], int token_count, double x);
int get_priority_to_tok(TokenType *token);
int is_left_associative(TokenType *token);

#endif
