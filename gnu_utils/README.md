# GNU Utils

C reimplementation of `cat` and `grep` — faithful to POSIX behaviour, verified against the originals via automated diff-based tests.

## Utilities

### cat

Replicates all standard flags:

| Flag | Description |
|------|-------------|
| `-b`, `--number-nonblank` | Number non-empty lines |
| `-n`, `--number` | Number all lines |
| `-s`, `--squeeze-blank` | Suppress repeated blank lines |
| `-e` / `-E` | Show `$` at end of each line (`-e` also enables `-v`) |
| `-t` / `-T` | Show tabs as `^I` (`-t` also enables `-v`) |
| `-v` | Show non-printing characters |

### grep

Supports all standard flags including bonus combinations:

| Flag | Description |
|------|-------------|
| `-e` | Specify pattern |
| `-i` | Case-insensitive match |
| `-v` | Invert match |
| `-c` | Count matching lines only |
| `-l` | Print matching filenames only |
| `-n` | Prefix lines with line number |
| `-h` | Suppress filename prefix |
| `-s` | Suppress errors for missing files |
| `-f FILE` | Read patterns from file |
| `-o` | Print only the matching part |

Flag combinations (e.g. `-iv`, `-cn`) are fully supported.

## Build

```bash
# cat
cd src/cat && make

# grep
cd src/grep && make
```

## Tests

Automated bash test suites compare output against system `cat` and `grep` via `diff`. Each script logs failed cases and prints a pass/fail summary.

```bash
# Run cat tests (from src/cat/)
./test_cat.sh

# Run grep tests (from src/grep/)
./test_grep.sh
```

## Tech stack

C11 · POSIX · Makefile · Bash · regex.h · getopt
