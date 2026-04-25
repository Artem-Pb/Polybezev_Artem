#ifndef PARSER_H
#define PARSER_H

#include "struct.h"

int parse_expression(const char *src, TokenType *tokens);
int is_function(const char *str);

#endif
