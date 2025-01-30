GREEN = \e[0;32m
RESET = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf
AC = ar rc

SRC_DIR = src
OBJ_DIR = obj
PRINTF_DIR = utils/ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRC = main.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INCLUDES = -I includes/
LIBS = -lreadline

all: $(OBJ_DIR) $(NAME)
$(NAME): $(OBJ)
	@$(MAKE) -C $(PRINTF_DIR)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(PRINTF) $(INCLUDES) $(LIBS)
	@echo "$(GREEN)Compilation Successful.$(RESET)"
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
clean:
	@$(MAKE) clean -C $(PRINTF_DIR)
	@$(RM) $(OBJ) $(OBJ_DIR)
	@echo "$(GREEN)Object files successfully removed.$(RESET)"
fclean: clean
	@$(MAKE) fclean -C $(PRINTF_DIR)
	@$(RM) $(NAME)
	@echo "$(GREEN)Executable file successfully removed.$(RESET)"

re: fclean all
.PHONY: all clean fclean re
