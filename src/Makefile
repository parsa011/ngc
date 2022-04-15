include ../scripts/colors.mk

TARGET := ngc
CFLAGS = -Wall
#SUBDIRS := $(shell find . -maxdepth 1 -type d)
SUBDIRS := lexer token util ../lib
BUILD_DIR := ../build

SRCS := $(shell find $(SUBDIRS) -name '*.c')
INCS := $(shell find $(SUBDIRS) -name '*.h')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# The final build step.


.PHONY : $(SUBDIRS)
$(TARGET) : $(SUBDIRS) main.c
	$(CC) main.c $(OBJS) -o $(BUILD_DIR)/$@

$(SUBDIRS) : $(OBJS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c $(INCS)
	@mkdir -p $(dir $@)
	@echo " - Compile $(GREENCOLOR)$(<)$(RCOLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)

%.d: %.c
	$(CC) $(CFLAGS) -MM -MT $@ -MF $@ $<
