CC       = gcc
SRCDIR	 = src
OBJDIR	 = build 

# main.o 
#OBJECTS  = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.c=.o))
#DEPS     = $(OBJECTS:.o=.d)

# Colors
GREENCOLOR   = \033[32m
PURPLECOLOR  = \033[35m

# Reset Sequence
RCOLOR   = \033[0m

define write_help
	@echo "$(GREENCOLOR)$1$(RCOLOR)    $2"
endef
export write_help

define change_color
	@echo "$(1)"
endef
export change_color

define reset_color
	@echo "$(RCOLOR)"
endef
export reset_color

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

lexer token:
	@cd $(SRCDIR)/$@ ; make all

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
