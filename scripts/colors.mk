# Colors
GREENCOLOR   = \033[32m
PURPLECOLOR  = \033[35m

# Reset Sequence
RCOLOR   = \033[0m

define change_color
	@echo "$(1)"
endef

define reset_color
	@echo "$(RCOLOR)"
endef
