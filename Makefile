.PHONY: all clean
CC=gcc
CPP=g++
AR=ar
RANLIB=ranlib
CFLAGS= -g -Wall -Wno-unused-function
LIBS = -lm -pthread
PROGRAMS =  sig_mutex \
			pipe

all: $(PROGRAMS)

%: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -rf $(PROGRAMS) *.dSYM
