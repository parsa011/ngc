include ../scripts/colors.mk

CC = cc
TARGET := ngc
CFLAGS = 
#SUBDIRS := $(shell find . -maxdepth 1 -type d)
SUBDIRS := lexer token util ast parser type ../lib
BUILD_DIR := ../build

# Super dirty :)
# TODO : find a single way for all of them
#==========================================
SRCS := $(shell find $(SUBDIRS) -name '*.c')
INCS := $(shell find $(SUBDIRS) -name '*.h')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

LEX_SRC := $(shell find lexer -name '*.c')
LEX_INCS := $(shell find lexer -name '*.h')
LEX_OBJS := $(LEX_SRC:%=$(BUILD_DIR)/%.o)

TOKEN_SRC := $(shell find token -name '*.c')
TOKEN_INCS := $(shell find token -name '*.h')
TOKEN_OBJS := $(TOKEN_SRC:%=$(BUILD_DIR)/%.o)

UTIL_SRC := $(shell find util -name '*.c')
UTIL_INCS := $(shell find util -name '*.h')
UTIL_OBJS := $(UTIL_SRC:%=$(BUILD_DIR)/%.o)

AST_SRC := $(shell find ast -name '*.c')
AST_INCS := $(shell find ast -name '*.h')
AST_OBJS := $(AST_SRC:%=$(BUILD_DIR)/%.o)

PARSER_SRC := $(shell find parser -name '*.c')
PARSER_INCS := $(shell find parser -name '*.h')
PARSER_OBJS := $(PARSER_SRC:%=$(BUILD_DIR)/%.o)

#==========================================

$(TARGET) : $(OBJS)
	$(CC) main.c $(OBJS) -g -o $(BUILD_DIR)/$@

lexer : $(LEX_OBJS) $(LEX_INCS)

token : $(TOKEN_OBJS) $(TOKEN_INCS)

util : $(UTIL_OBJS) $(UTIL_INCS)

ast : $(AST_SRC) $(AST_INCS)

parser : $(PARSER_SRC) $(PARSER_INCS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c $(INCS)
	@mkdir -p $(dir $@)
	@echo " - Compile $(GREENCOLOR)$(<)$(RCOLOR)"
	@$(CC) $(CFLAGS) -g -c $< -o $@

clean :
	@cd ..; make clean

%.d: %.c
	$(CC) $(CFLAGS) -MM -MT $@ -MF $@ $<

-include $(OBJS:.o=.d)
