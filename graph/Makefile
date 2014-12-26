CC = clang++
BINS = scc johnson
CFLAGS = -O3 -std=c++11

default: all

all: ${BINS}

${BINS}: %: %.C
	${CC} ${CFLAGS} -o $@ $<

.PHONY: clean
clean:
	- rm -rf ${BINS}

