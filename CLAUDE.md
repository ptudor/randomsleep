# CLAUDE.md

## Project

randomsleep - cron jitter utility. ISC license.

Introduces a cryptographically secure random delay for cron jobs to prevent thundering herd problems.

## Architecture

Two source files, one binary:
- `randomsleep.c` - BSD variant, uses `arc4random_uniform()`
- `grandomsleep.c` - Linux variant, uses `getrandom()` syscall

Both produce a binary named `randomsleep`.

## Build

`make` auto-selects the right Makefile:
- **Linux** (GNU make): reads `GNUmakefile`, compiles `grandomsleep.c`
- **BSD** (BSD make): ignores `GNUmakefile`, reads `Makefile`, compiles `randomsleep.c`
- **macOS** (GNU make via Xcode): `GNUmakefile` detects Darwin and tells you to run `make macos`

## Install

```sh
# BSD / Linux
make install          # PREFIX defaults to /usr/local

# macOS (GNU make)
make macos-install
```

## Testing

No test suite. Manual smoke test:

```sh
./randomsleep -f 1 -c 3
```

This should sleep between 1 and 3 seconds and print the chosen delay.
