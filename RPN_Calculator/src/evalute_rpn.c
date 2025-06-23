#include "include.h"

double evaluate_rpn(Token rpn_tokens[], int token_count, double x) {
    Stack stack;
    init(&stack);

    for (int i = 0; i < token_count; i++) {
        Token token = rpn_tokens[i];

        if (token.type == TYPE_NUMBER) {
            push(&stack, token);
        }
        else if (strcmp(token.value, "x") == 0) {
            Token x_token;
            snprintf(x_token.value, MAX_TOKEN_LEN, "%f", x);
            x_token.type = TYPE_NUMBER;
            push(&stack, x_token);
        }
        else if (token.type == TYPE_OPERATOR) {
            double b = atof(pop(&stack).value);
            double a = atof(pop(&stack).value);
            double result = 0;

            switch (token.value[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                case '^': result = pow(a, b); break;
            }

            Token result_token;
            snprintf(result_token.value, MAX_TOKEN_LEN, "%f", result);
            result_token.type = TYPE_NUMBER;
            push(&stack, result_token);
        }
        else if (token.type == TYPE_FUNCTION) {
            double a = atof(pop(&stack).value);
            double result = 0;

            if (strcmp(token.value, "sin") == 0) {
                result = sin(a);
            }
            else if (strcmp(token.value, "cos") == 0) {
                result = cos(a);
            }
            else if (strcmp(token.value, "tan") == 0) {
                result = tan(a);
            }
            else if (strcmp(token.value, "log") == 0) {
                result = log(a);
            }
            else if (strcmp(token.value, "exp") == 0) {
                result = exp(a);
            }

            Token result_token;
            snprintf(result_token.value, MAX_TOKEN_LEN, "%f", result);
            result_token.type = TYPE_NUMBER;
            push(&stack, result_token);
        }
    }

    if (!empty(&stack)) {
        return atof(pop(&stack).value);
    }
    return 0.0;
}
