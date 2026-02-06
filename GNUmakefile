# GNUmakefile for randomsleep (Linux)
# Copyright 2026 Patrick Tudor <ptudor@ptudor.net>

PROG    = randomsleep
SRCS    = grandomsleep.c
MAN     = randomsleep.1
OBJS    = $(SRCS:.c=.o)

# Standard Linux paths
PREFIX ?= /usr/local
BINDIR  = $(PREFIX)/bin
MANDIR  = $(PREFIX)/share/man/man1

# Detect macOS and suggest the correct target
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
ifneq ($(MAKECMDGOALS),macos)
ifneq ($(MAKECMDGOALS),macos-install)
ifneq ($(MAKECMDGOALS),macos-clean)
ifneq ($(MAKECMDGOALS),clean)
$(info )
$(info   Detected macOS — this GNUmakefile builds the Linux variant.)
$(info   Run one of:)
$(info     make macos)
$(info     make macos-install)
$(info     make macos-clean)
$(info )
$(error Stopping. Use "make macos" on macOS.)
endif
endif
endif
endif
endif

# GCC settings
CC     ?= gcc
CFLAGS ?= -O2 -Wall -Wextra -pedantic -std=c99 -D_GNU_SOURCE
LDFLAGS ?=

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

install: $(PROG) $(MAN)
	mkdir -p $(DESTDIR)$(BINDIR)
	mkdir -p $(DESTDIR)$(MANDIR)
	install -m 755 $(PROG) $(DESTDIR)$(BINDIR)/$(PROG)
	install -m 644 $(MAN) $(DESTDIR)$(MANDIR)/$(MAN)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(PROG)
	rm -f $(DESTDIR)$(MANDIR)/$(MAN)

clean:
	rm -f $(PROG) $(OBJS)

macos:
	$(MAKE) -f Makefile

macos-install:
	$(MAKE) -f Makefile install

macos-clean:
	$(MAKE) -f Makefile clean

.PHONY: all install uninstall clean macos macos-install macos-clean
