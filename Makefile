include scripts/colors.mk

CC       		= gcc
SRCDIR	 		= src
CWD				= $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
TARGET			= ngc

ifneq ($(findstring ngc/src,$(CWD)),ngc/src)
PREFIX 			= ./
else
PREFIX 			= ../
endif

BUILDDIR		= $(PREFIX)build 
CONFIG_FILE 	= $(PREFIX)config.h
CONFIGURE_FILE  = $(PREFIX)scripts/configure.sh
PHONY 			=

define write_help
	@echo "$(GREENCOLOR)$1$(RCOLOR)    $2"
endef

PHONY = help build

# check if used runned configure.sh or no (config.h file should exist)
ifeq ($(wildcard $(CONFIG_FILE)),)
info :
	@echo "Please run 'bash $(CONFIGURE_FILE)' or 'make config' Before Building"

else

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

world :
	cd $(SRCDIR); make ngc

remake : clean build

clean:
	cd $(BUILDDIR) ; rm -rfv *

run : world
	@echo "============================="
	@cd $(BUILDDIR); ./$(TARGET) ../example/main.c

.PHONY: $(PHONY)
endif

config :
	bash $(CONFIGURE_FILE)
