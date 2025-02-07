GREEN = \e[0;32m
RESET = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
AC = ar rc

SRC_DIR = src
OBJ_DIR = obj
UTILS_DIR = utils
LIBFT_DIR = $(UTILS_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = 		main.c \
			init/initialize_shell.c \
			prompt/read_input_line.c  \
			prompt/get_env_info.c  \
			prompt/create_prompt.c \
			free/free_memory.c \
			free/free_list_memory.c \
			signals/handle_signal.c \
			exit/exit_with_error.c \

UTILS_SRC = node_actions/add_node_back.c \
			node_actions/create_new_node.c \
			node_actions/last_node.c \

SRC := $(addprefix $(SRC_DIR)/, $(SRC))
UTILS_SRC := $(addprefix $(UTILS_DIR)/, $(UTILS_SRC))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
UTILS_OBJ = $(UTILS_SRC:$(UTILS_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES = -I includes/
LIBS = -lreadline

all: $(OBJ_DIR) $(NAME)
$(NAME): $(OBJ) $(UTILS_OBJ) 
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(UTILS_OBJ) -o $(NAME) $(LIBFT) $(INCLUDES) $(LIBS)
	@echo "$(GREEN)Compilation Successful.$(RESET)"
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(RM) $(OBJ) $(OBJ_DIR)
	@echo "$(GREEN)Object files successfully removed.$(RESET)"
fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME) 
	@echo "$(GREEN)Executable file successfully removed.$(RESET)"
re: fclean all
.PHONY: all clean fclean re
