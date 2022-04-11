include ../../scripts/colors.mk

BUILD_DIR := ../../build
SRC_DIRS := .

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
INCS := $(shell find $(SRC_DIRS) -name '*.h')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CPPFLAGS := $(INC_FLAGS)# -MMD -MP

# The final build step.
all : $(BUILD_DIR)

$(BUILD_DIR): $(OBJS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c $(INCS)
	@$(call change_color, $(PURPLECOLOR))
	@mkdir -p $(dir $@)
	@echo "Building Lexer : "
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	@$(call reset_color)
