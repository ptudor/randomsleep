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
LDFLAGS ?=

# Targets
all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

install: $(PROG) $(MAN)
	mkdir -p $(DESTDIR)$(BINDIR)
	mkdir -p $(DESTDIR)$(MANDIR)
	install -m 555 $(PROG) $(DESTDIR)$(BINDIR)/$(PROG)
	install -m 444 $(MAN) $(DESTDIR)$(MANDIR)/$(MAN)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(PROG)
	rm -f $(DESTDIR)$(MANDIR)/$(MAN)

clean:
	rm -f $(PROG) $(OBJS)

.PHONY: all install uninstall clean
