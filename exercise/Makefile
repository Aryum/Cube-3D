NAME := cub3D

MAIN_C := src/main.c
HDR_DIR = .

#Libs
MLX_DIR :=	./mlx
MLX_ARC :=	$(MLX_DIR)/libmlx.a

HLP_DIR :=	./helpers
HLP_ARC :=	$(HLP_DIR)/lib/libft.a		\
			$(HLP_DIR)/lists/lst.a		\
			$(HLP_DIR)/print/prt.a		\

SRC_DIR :=	./src
SRC_ARC :=	$(SRC_DIR)/render/render.a		\
			$(SRC_DIR)/draw/draw.a			\
			$(SRC_DIR)/data/data.a			\
			$(SRC_DIR)/input/input.a		\
			$(SRC_DIR)/ray/ray.a			\
			$(SRC_DIR)/var_hlp/var_hlp.a	\
			


ALL_ARC := $(SRC_ARC) $(HLP_ARC)

#Vars
MAKEFLAGS += --no-print-directory

FLAGS := -Wall -Wextra -Werror

LINKS := -lmlx -lXext -lX11 -lm

RM := rm -f

blank :=
define NEWLINE

$(blank)
endef

COLOUR_GREEN := \033[1;32m
COLOUR_RED := \033[1;31m
COLOUR_YELLOW := \033[1;33m
COLOUR_BLUE := \033[1;34m
COLOR_WHITE := \033[0m

all: $(NAME)

$(NAME): $(MLX_ARC) $(ALL_ARC)  $(MAIN_C)
	@cc $(FLAGS) -o $@ -I$(HDR_DIR) $(MAIN_C) $(ALL_ARC) $(LINKS)
	@echo "$(COLOUR_GREEN)Made main file$(COLOR_WHITE)"

$(ALL_ARC): FORCE
	@echo "$(COLOUR_BLUE)Updating archives of $@$(COLOR_WHITE)"
	-@cd $(dir $@ ) && (!(make -q) && make) || echo "$(COLOUR_YELLOW)	Already updated$(COLOR_WHITE)"

$(MLX_ARC): $(MLX_DIR)
	@echo "$(COLOUR_BLUE)Updating archives of $@$(COLOR_WHITE)"
	@cd $(dir $@) && make
	@touch $@

$(MLX_DIR):
	git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR)

clean:
	@echo "$(COLOUR_YELLOW)Cleaning archives$(COLOR_WHITE)"
	@$(foreach dir,$(dir $(SRC_ARC)), cd $(dir) && make fclean && echo$(NEWLINE)$(NEWLINE))
	@$(foreach dir,$(dir $(HLP_ARC)), cd $(dir) && make fclean && echo$(NEWLINE)$(NEWLINE))


fclean: 
	@echo "$(COLOUR_YELLOW)Cleaning everything$(COLOR_WHITE)"
	@$(RM) $(NAME)
	@$(foreach dir,$(dir $(SRC_ARC)), cd $(dir) && make fclean && echo$(NEWLINE)$(NEWLINE))
	@$(foreach dir,$(dir $(HLP_ARC)), cd $(dir) && make fclean && echo$(NEWLINE)$(NEWLINE))
	@echo "$(COLOUR_RED)	Cleaning Mini Libx$(COLOUR_WHITE)"
	@$(RM) -r $(MLX_DIR)

re: clean all


.PHONY: all clean fclean re FORCE
