/*
 * randomsleep.c (Linux Variant)
 *
 * Copyright 2026 Patrick Tudor <ptudor@ptudor.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE.
 *
 * Designed for GNU/Linux.
 * Uses getrandom() (Kernel 3.17+) for cryptographically secure randomness.
 */

#define _GNU_SOURCE

#include <sys/random.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>
#include <err.h>

#define DEFAULT_MIN 0
#define DEFAULT_MAX 1800

static void usage(void);
static uint32_t secure_uniform(uint32_t upper_bound);

int main(int argc, char *argv[]) {
    int ch;
    long min_arg = DEFAULT_MIN;
    long max_arg = DEFAULT_MAX;
    int quiet = 0;
    char *endptr;

    while ((ch = getopt(argc, argv, "c:f:qh")) != -1) {
        switch (ch) {
        case 'c':
            errno = 0;
            max_arg = strtol(optarg, &endptr, 10);
            if (optarg[0] == '\0' || *endptr != '\0')
                errx(1, "invalid ceiling value: %s", optarg);
            if (errno == ERANGE || max_arg < 0)
                errx(1, "ceiling value out of range: %s", optarg);
            break;

        case 'f':
            errno = 0;
            min_arg = strtol(optarg, &endptr, 10);
            if (optarg[0] == '\0' || *endptr != '\0')
                errx(1, "invalid floor value: %s", optarg);
            if (errno == ERANGE || min_arg < 0)
                errx(1, "floor value out of range: %s", optarg);
            break;

        case 'q':
            quiet = 1;
            break;

        case 'h':
        default:
            usage();
        }
    }

    if (min_arg > max_arg) {
        errx(1, "error: floor (%ld) cannot be greater than ceiling (%ld)", min_arg, max_arg);
    }

    long delta = max_arg - min_arg;

    if (delta >= UINT32_MAX) {
        errx(1, "error: range between floor and ceiling is too large");
    }

    uint32_t range = (uint32_t)delta + 1;
    
    // Use our Linux-native secure implementation
    uint32_t random_offset = secure_uniform(range);
    
    uint32_t sleep_seconds = (uint32_t)min_arg + random_offset;

    if (!quiet) {
        printf("sleeping %u seconds...\n", sleep_seconds);
        fflush(stdout);
    }

    sleep(sleep_seconds);

    return 0;
}

/*
 * secure_uniform(n)
 * Returns a cryptographically secure random number in [0, n-1]
 * without modulo bias, using Linux getrandom().
 */
static uint32_t secure_uniform(uint32_t upper_bound) {
    uint32_t r, min;
    ssize_t ret;

    if (upper_bound < 2) return 0;

    /*
     * Calculate the "waste" threshold.
     * To avoid modulo bias, we must discard any random value 'r'
     * that falls in the incomplete range at the top of UINT32_MAX.
     * * This magic calculation is (2^32 % upper_bound) using unsigned overflow.
     */
    min = -upper_bound % upper_bound;

    for (;;) {
        // Fill 'r' with random bytes from the kernel
        ret = getrandom(&r, sizeof(r), 0);
        
        // Handle interruptions or failures
        if (ret != sizeof(r)) {
            if (ret == -1 && errno == EINTR) continue;
            err(1, "getrandom failed");
        }

        // Rejection sampling: if we are above the waste threshold, we are safe.
        if (r >= min) break;
    }

    return r % upper_bound;
}

static void usage(void) {
    fprintf(stderr, "usage: randomsleep [-q] [-f floor] [-c ceiling]\n");
    fprintf(stderr, "  -q   Quiet mode (do not print sleep duration)\n");
    fprintf(stderr, "  -f   Minimum sleep seconds (default: %d)\n", DEFAULT_MIN);
    fprintf(stderr, "  -c   Maximum sleep seconds (default: %d)\n", DEFAULT_MAX);
    exit(1);
}
