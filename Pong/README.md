# Pong

Two-player Pong in the terminal, written in C.

## Features

- 80×25 field rendered with ASCII characters
- Two-player keyboard control: `A`/`Z` (left paddle) and `K`/`M` (right paddle)
- Space bar skips a step in step-by-step mode
- Simple ball physics: bounce off paddles and walls
- Score tracking — first to 21 wins
- No external libraries

## Build

```
gcc src/pong.c -o pong
```

## Usage

```
./pong
```
