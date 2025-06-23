#include "graph.h"

#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "rpn.h"

static TokenType global_rpn_tokens[MAX_LEXEMS];
static int global_rpn_count;

double rpn_evaluator(double x) { return evaluate_rpn(global_rpn_tokens, global_rpn_count, x); }

int main() {
    char expression[256];
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0';

    TokenType tokens[MAX_LEXEMS];
    int token_count = parse_expression(expression, tokens);

    global_rpn_count = to_rpn(tokens, token_count, global_rpn_tokens);

    char graph[HEIGHT][WIDTH];
    calculate_y(rpn_evaluator, graph);

    draw_graph(graph);
    return 0;
}
