# RPN Calculator & Graph Plotter

A mathematical expression evaluator and ASCII function graph renderer written in C.

The same expression pipeline drives two independent outputs: a numeric result and a terminal graph plot.

## Features

- Infix expression parser with unary minus support
- Infix-to-RPN conversion via Dijkstra's shunting-yard algorithm
- Stack-based RPN evaluator
- ASCII graph renderer: 25×80 grid, x ∈ [0, 4π], y ∈ [−1, 1]

Supported operators: `+` `-` `*` `/` `^` and unary `-`

Supported functions: `sin` `cos` `tan` `log` `exp` `sqrt`

## Build

```
make
```

Output binary: `build/graph_app`

## Usage

```
echo "sin(cos(2*x))" | ./build/graph_app
```

Input is read from stdin as a single expression string.

## Architecture

```
src/graph.c          entry point — wires parser, evaluator, renderer
lib/parser.c         tokenizer: infix string → token list
lib/rpn.c            shunting-yard: token list → RPN, RPN evaluation
lib/graph_draw.c     renders expression to 25×80 ASCII grid
lib/Stack.c          integer stack (used in shunting-yard)
lib/double_stack.c   double stack (used in RPN evaluation)
lib/type.c           character classification (no stdlib ctype dependency)
include/             headers for all modules
```

Each module has a single responsibility. The parser does not know about rendering; the evaluator does not know about I/O.

## Example output

Input: `sin(cos(2*x))`

```
................................................................................
................................................................................
.........***.................**..................**.................***.........
........*...................*..*................*..*...................*........
............*...................*..............*...................*............
.......*...................*........................*...................*.......
.............*...................*............*...................*.............
..........................*..........................*..........................
......*..................................................................*......
..............*..................................................*..............
..................................*..........*..................................
.........................*............................*.........................
.....*....................................................................*.....
...............*................................................*...............
...................................*........*...................................
....*...................*..............................*...................*....
................*..............................................*................
....................................*......*....................................
.......................*................................*.......................
...*.............*............................................*.............*...
......................*..............*....*..............*......................
..*...............*...................*..*...................*...............*..
**.................***.................**.................***.................**
................................................................................
................................................................................
```
