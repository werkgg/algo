CC = gcc
BINS = matrix lcs
CFLAGS = -std=gnu99

default: all

all: ${BINS}

${BINS}: %: %.c
	${CC} ${CFLAGS} -o $@ $<

.PHONY: clean
clean:
	- rm -rf ${BINS}

