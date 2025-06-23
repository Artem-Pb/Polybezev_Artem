#include "include.h"

int get_priority_to_tok(TokenType *token){

    if (token->type == TYPE_FUNCTION) return 5;
    if (token->type != TYPE_OPERATOR) return 0;

    char op = token->value[0];
    switch(op) {
        case '+': case '-': return 2;
        case '*': case '/': return 3;
        case '^': return 4;
        default: return 0;
    }
}

int is_left_associative(TokenType *token) {
    if (token->type != TYPE_OPERATOR) return 0;
    char op = token->value[0];
    return (op != '^'); 
}

