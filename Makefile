CC       =  gcc
CFLAGS	 = -g -Wall -I.
SRCDIR	 = src
OBJDIR	 = obj
BINDIR	 = bin

SOURCES  = $(shell find $(SRCDIR) -type f -name '*.c') # fine c files in SRCDIR folder
OBJECTS  = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.c=.o)) # main.o say_hello.o
DEPS     = $(OBJECTS:.o=.d)
BINARY   = $(BINDIR)/Program.bin

HCOLOR   = \033[32m
RCOLOR   = \033[0m
#-include $(DEPS)

help:
	@echo "$(HCOLOR)build$(RCOLOR)    build world, all of language"
	@echo "$(HCOLOR)parser$(RCOLOR)    build parser"
	@echo "$(HCOLOR)lexer$(RCOLOR)     build lexer"
	@echo "$(HCOLOR)ast$(RCOLOR)       build abstract sytanx tree"
	@echo "$(HCOLOR)CG$(RCOLOR)        build Code Generator"
	
	@echo "$(HCOLOR)tests\033[0m     build world and run tests in tests folder"
	@echo "$(HCOLOR)  test-lexer$(RCOLOR)     test just lexer of language"
	@echo "$(HCOLOR)  test-parser$(RCOLOR)    test just parserof language"
	@echo "$(HCOLOR)  test-ast$(RCOLOR)       test ast"
	@echo "$(HCOLOR)  test-cg$(RCOLOR)        test code generator"
	
	@echo "$(HCOLOR)install$(RCOLOR)   install language on your machine"
	@echo "$(HCOLOR)doc$(RCOLOR)       create documents and help files"

all : help
	
#
#buildsolution: dir $(BINARY)
#
#dir:
#	# create folder with p switch to prevent of showing error when they exists
#    mkdir -p $(OBJDIR)
#    mkdir -p $(BINDIR)
#
#$(BINARY): $(OBJECTS)
#    $(CC) $(CFLAGS) $^ -o $@
#
#$(OBJDIR)/%.o: $(SRCDIR)/%.c
#    $(CC) $(CFLAGS) -c -MMD -MP -o $@ $<
#

#clean:
 #   echo "clean runing..."
