CC       =  gcc
CFLAGS	 = -g -Wall -I.
SRCDIR	 = src
OBJDIR	 = obj
BINDIR	 = bin

SOURCES  = $(shell find $(SRCDIR) -type f -name '*.c') # fine c files in SRCDIR folder
OBJECTS  = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.c=.o)) # main.o say_hello.o
DEPS     = $(OBJECTS:.o=.d)
BINARY   = $(BINDIR)/Program.bin

# Help Color
HCOLOR   = \033[32m
# Reset Sequence
RCOLOR   = \033[0m

define write_help
	@echo "$(HCOLOR)$1$(RCOLOR)    $2"
endef
export HEADER

#-include $(DEPS)

help:
	$(call write_help,build,   build world, all of language)
	$(call write_help,parser,  build parser)
	$(call write_help,lexer,   build lexer)
	$(call write_help,ast,     build abstract sytanx tree)
	$(call write_help,CG,      build Code Generator)
	$(call write_help,tests,   build world and run tests in tests folder)
	$(call write_help,  test-lexer,  test just lexer of language)
	$(call write_help,  test-parser, test just parserof language)
	$(call write_help,  test-ast,    test test ast)
	$(call write_help,  test-cg,     test code generator)
	$(call write_help,install, install language on your machine)
	$(call write_help,doc,     create documents and help files)

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
