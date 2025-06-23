#ifndef STRUCT_H
#define STRUCT_H

#define MAX_LEXEMS 256
#define MAX_TOKEN_LEN 100

#define TYPE_NUMBER 0
#define TYPE_OPERATOR 1
#define TYPE_FUNCTION 2
#define TYPE_LPAREN 3
#define TYPE_RPAREN 4
#define TYPE_VARIABLE 5

typedef struct {
    char value[MAX_TOKEN_LEN];
    int type;
    int priority;
    int is_unary;
} TokenType;

#endif