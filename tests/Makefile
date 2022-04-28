include ../scripts/colors.mk

CC = cc
CFLAGS = 
#SUBDIRS := $(shell find . -maxdepth 1 -type d)
SUBDIRS := lexer

all : $(SUBDIRS) 

.PHONY : lexer
$(SUBDIRS): 
	@cd $@; make 

clean :
	rm *.out -rf
