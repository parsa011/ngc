BUILD_DIR := ../../build
SRC_DIRS := .

SRCS := $(shell find $(SRC_DIRS) -name '*.c' -or -name '*.c' -or -name '*.s')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CPPFLAGS := $(INC_FLAGS)# -MMD -MP

# The final build step.
all : $(BUILD_DIR)

$(BUILD_DIR): $(OBJS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	@$(call change_color, \033[35m)
	@mkdir -p $(dir $@)
	@echo "Building Utils : "
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	@$(call reset_color)
