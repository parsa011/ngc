CC       		= gcc
SRCDIR	 		= src
CWD				= $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

ifneq ($(findstring ngc/src,$(CWD)),ngc/src)
PREFIX 			= ./
else
PREFIX 			= ../../
endif

BUILDDIR		= $(PREFIX)build 
CONFIG_FILE 	= $(PREFIX)config.h
CONFIGURE_FILE  = $(PREFIX)scripts/configure.sh
PHONY 			=

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

PHONY = help build

# check if used runned configure.sh or no (config.h file should exist)
ifeq ($(wildcard $(CONFIG_FILE)),)
PHONY = info
info :
	@echo "Please run 'bash $(CONFIGURE_FILE)' or 'make config' Before Building"
	@exit
else

BUILDS = lexer token util

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
	$(call write_help,util,    compile utility function)
	$(call write_help,install, install language on your machine)
	$(call write_help,doc,     create documents and help files)
	
build: $(BUILDS)

$(BUILDS):
	@cd $(SRCDIR)/$@ ; make all

clean:
	cd $(BUILDDIR) ; rm -rfv *

.PHONY: $(PHONY)
endif

config :
	bash $(CONFIGURE_FILE)
