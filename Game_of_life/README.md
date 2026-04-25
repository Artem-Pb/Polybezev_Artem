# Game of Life

Conway's Game of Life simulation in the terminal, written in C.

Team project (3 developers).

## Features

- 80×25 toroidal grid — edges wrap: top connects to bottom, left to right
- Colour rendering with ANSI escape codes and Unicode symbols (no ncurses)
- Non-blocking keyboard input via `ioctl` + `stty`
- Speed control with `+` / `-`, quit with `q`
- Auto-stop when no live cells remain
- Initial state loaded from stdin (text file of `0`/`1` characters)

## Build

```
gcc src/game_of_life.c -o game_of_life
```

## Usage

```
./game_of_life < src/file_2.txt
```

Seven example initial states are included in `src/`:

| File | Pattern type |
|------|--------------|
| `file_1.txt` | Empty grid |
| `file_2.txt` | Still lifes + small clusters |
| `file_3.txt` | Oscillators |
| `file_4.txt` | Gliders |
| `file_5.txt` | Dense random |
| `file_6.txt` | Sparse random |
| `file_7.txt` | Near-full grid |

## Controls

| Key | Action |
|-----|--------|
| `+` | Speed up |
| `-` | Slow down |
| `q` | Quit |

## Input format

Plain text file: 25 rows × 80 columns of `0` (dead) and `1` (live) characters, one row per line.
