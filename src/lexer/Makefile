include ../../Makefile

# fine c files in SRCDIR folder
SOURCES  = $(shell find . -type f -name '*.c')
#OBJS := $(.:%=$(OBJDIR)/%.o)

CFLAGS	 = -g -Wall -I. -c

.PHONY : all

# we need to change this later
all : lexer.c lexer.h
	$(CC) $(CFLAGS) lexer.c -c -o ../../build/lexer.o
