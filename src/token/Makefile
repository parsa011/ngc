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
	@mkdir -p $(dir $@)
	@$(call change_color, $(RCOLOR))
	@echo "Building Token : "
	@echo " - Compile $(GREENCOLOR)$(<)$(RCOLOR)" 
	@$(call reset_color)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
