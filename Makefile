CC       = gcc
SRCDIR	 = src
OBJDIR	 = build 

# main.o 
#OBJECTS  = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.c=.o))
#DEPS     = $(OBJECTS:.o=.d)

# Help Color
HCOLOR   = \033[32m
# Reset Sequence
RCOLOR   = \033[0m

define write_help
	@echo "$(HCOLOR)$1$(RCOLOR)    $2"
endef
export HEADER

#-include $(DEPS)

.PHONY: help build

help:
	$(call write_help,build,   build world, all of language)
	$(call write_help,lexer,   build lexer)
	$(call write_help,token,   build token)
	$(call write_help,parser,  build parser)
	$(call write_help,ast,     build abstract sytanx tree)
	$(call write_help,CG,      build Code Generator)
	$(call write_help,tests,   build world and run tests in tests folder)
	$(call write_help,  test-lexer,  test just lexer of language)
	$(call write_help,  test-parser, test just parserof language)
	$(call write_help,  test-ast,    test test ast)
	$(call write_help,  test-cg,     test code generator)
	$(call write_help,install, install language on your machine)
	$(call write_help,doc,     create documents and help files)
	
build: lexer token
	@echo "TODO"


lexer :
	@cd $(SRCDIR)/lexer ; make all

token :
	@cd $(SRCDIR)/token ; make all

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

clean:
	cd $(OBJDIR) ; rm -rf *
