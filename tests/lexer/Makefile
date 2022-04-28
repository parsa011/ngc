SRCS = $(shell find . -name "[0-9]*.c")
TEST := $(SRCS:.c=.test)

.PHONY : all
all: test

test: $(TEST)

%.test: %.c
	@echo ==========================
	@echo Test: $<
	@gcc $< run_test.c ../../src/lexer/lexer.c ../../src/util/mem.c ../../lib/prosing.c ../../src/lexer/lexer_file.c ../../src/token/token.c
	@./a.out

