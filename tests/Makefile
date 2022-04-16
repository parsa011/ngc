include ../scripts/colors.mk

CC = cc
CFLAGS = 
#SUBDIRS := $(shell find . -maxdepth 1 -type d)
SUBDIRS := lexer token
BUILD_DIR := ../build

# Super dirty :)
#==========================================
SRCS := $(shell find $(SUBDIRS) -name '*.c')
INCS := $(shell find $(SUBDIRS) -name '*.h')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

LEX_SRC := $(shell find lexer -name '*.c')
LEX_INCS := $(shell find lexer -name '*.h')
LEX_OBJS := $(LEX_SRC:%=%.o)

TOKEN_SRC := $(shell find token -name '*.c')
TOKEN_INCS := $(shell find token -name '*.h')
TOKEN_OBJS := $(TOKEN_SRC:%=%.o)

#==========================================

all : lexer token

lexer : $(LEX_OBJS) $(LEX_INCS)

token : $(TOKEN_OBJS) $(TOKEN_INCS)

# Build step for C source
%.c.o: %.c $(INCS)
	@mkdir -p $(dir $@)
	@echo " - Compile $(GREENCOLOR)$(<)$(RCOLOR)"
	@$(CC) $(CFLAGS) $< ../src/lexer/lexer.c ../src/util/mem.c ../lib/prosing.c ../src/lexer/lexer_file.c ../src/token/token.c -o $@
	@./$<.o

clean :
	find . -name "*.o" -type f -delete
