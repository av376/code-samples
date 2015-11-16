# Makefile

# compiler to use
CC = g++

# flags to pass compiler
CFLAGS = -ggdb3 -O0 -Qunused-arguments -Werror #-Wall

# name for executable
EXE = test

# space-separated list of header files
HDRS = HashMap_v1p.h HashMap_v2p.h

# space-separated list of libraries, if any,
# each of which should be prefixed with -l
LIBS =

# space-separated list of source files
SRCS = test.cpp

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)


# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies 
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o
