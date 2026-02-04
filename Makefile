# Makefile for randomsleep
# Copyright 2026 Patrick Tudor <ptudor@ptudor.net>

PROG    = randomsleep
SRCS    = randomsleep.c
MAN     = randomsleep.1
OBJS    = $(SRCS:.c=.o)

# Installation paths
PREFIX ?= /usr/local
BINDIR  = $(PREFIX)/bin
MANDIR  = $(PREFIX)/man/man1

# Compiler settings
CC     ?= clang
CFLAGS ?= -O2 -Wall -Wextra -pedantic -std=c99

# Targets
all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

install: $(PROG) $(MAN)
	mkdir -p $(BINDIR)
	mkdir -p $(MANDIR)
	install -m 555 $(PROG) $(BINDIR)/$(PROG)
	install -m 444 $(MAN) $(MANDIR)/$(MAN)

uninstall:
	rm -f $(BINDIR)/$(PROG)
	rm -f $(MANDIR)/$(MAN)

clean:
	rm -f $(PROG) $(OBJS)

.PHONY: all install uninstall clean
