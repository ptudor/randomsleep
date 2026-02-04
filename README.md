# randomsleep

A lightweight, cryptographically secure delay utility designed for BSDs, macOS, and Linux.

It is designed primarily for cron jobs to introduce "jitter" (randomized delay) to prevent "thundering herd" problems where many servers contact a central API or run high-load backups at the exact same second.

## Usage

```sh
randomsleep [-q] [-f floor] [-c ceiling]
```

With no flags, `randomsleep` sleeps for a random duration between 0 and 1800 seconds (30 minutes).

| Flag | Description | Default |
|------|-------------|---------|
| `-f` | Minimum seconds to sleep | 0 |
| `-c` | Maximum seconds to sleep | 1800 |
| `-q` | Quiet mode (suppress output) | off |

### Examples

```sh
# Sleep 0-1800 seconds (default)
randomsleep

# Sleep 10-60 seconds
randomsleep -f 10 -c 60

# Crontab: backup at 3 AM with up to 10 minutes of jitter
0 3 * * * /usr/local/bin/randomsleep -c 600 && /path/to/backup.sh
```

## Features

* **Secure:** Uses native `arc4random_uniform()` (BSD/macOS) or `getrandom()` (Linux) for unbiased, cryptographically secure randomness.
* **Portable:** Designed for FreeBSD, OpenBSD, NetBSD, macOS, and Linux.
* **Simple:** Defaults to 0-1800 seconds (30 minutes) with a single command.
* **Quiet:** Optional `-q` flag to suppress output for clean cron logs.

## Installation

### Requirements
* FreeBSD, OpenBSD, NetBSD, or macOS (Base system)
* Linux (Base system, uses `getrandom()` syscall)

### Build and Install

On BSD systems, `make` (BSD make) reads `Makefile` and builds from `randomsleep.c`.
On Linux, `make` (GNU make) reads `GNUmakefile` and builds from `grandomsleep.c`.

```sh
make
sudo make install
```

On macOS where `make` is GNU make (e.g., installed via Xcode or Homebrew), use:

```sh
make macos
sudo make macos-install
```

### License

Copyright 2026 Patrick Tudor ptudor@ptudor.net

Permission to use, copy, modify, and distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.
