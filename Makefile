SYSTEM := $(shell uname -s)

ifeq ($(SYSTEM), Darwin)
    GREEN = \033[0;32m
	RESET = \033[0m
else
    GREEN = \e[0;32m
	RESET = \033[0m
endif

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
AC = ar rc

SRC_DIR = src
OBJ_DIR = obj
UTILS_DIR = utils
LIBFT_DIR = $(UTILS_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = 		main.c \
			init/initialize_shell.c \
			init/copy_env.c \
			init/make_env_arr.c \
			init/env_utils.c \
			prompt/read_input_line.c  \
			prompt/get_env_info.c  \
			prompt/create_prompt.c \
			free/free_memory.c \
			free/free_list_memory.c \
			free/free_child.c \
			free/close_fd.c \
			signals/handle_signal.c \
			signals/signal_parts_two.c \
			exit/exit_with_error.c \
			exit/print_message.c \
			executor/executor.c \
			executor/exe_single_buildin.c \
			executor/exe_child.c \
			executor/redirects_child.c \
			executor/execution_utils.c \
			lexer/lexing_inputs_data.c \
			lexer/handle_command.c \
			lexer/handle_heredoc.c \
			lexer/handle_operators.c \
			lexer/handle_variable.c \
			lexer/lexing_utils.c \
			lexer/command_utils.c \
			lexer/lexing_checker.c \
			parse/parse_tokens.c \
			parse/parse_command.c \
			parse/parse_arguments.c \
			parse/parse_utils.c \
			builtins/unset/unset.c \
			builtins/utils.c \
			builtins/pwd/pwd.c \
			builtins/env/env.c \
			builtins/echo/echo.c \
			builtins/cd/cd.c \
			builtins/cd/cd_utils.c \
			builtins/cd/cd_get_dir.c \
			builtins/exit/exit.c \
			builtins/exit/exit_utils.c \
			builtins/exit/validation.c \
			heredoc/heredoc.c \
			heredoc/heredoc_utils.c \
			heredoc/heredoc_free.c \
			builtins/export/export.c \
			builtins/export/export_utils.c \
			builtins/export/validate_arg.c \
			builtins/export/change_env.c \

UTILS_SRC = node_actions/cmd_node/add_cmd_back.c \
			node_actions/cmd_node/create_new_cmd.c \
			node_actions/cmd_node/last_cmd_node.c \
			node_actions/cmd_node/cmd_len.c \
			node_actions/envp_node/add_envp_back.c \
			node_actions/envp_node/last_envp_node.c \
			node_actions/envp_node/create_new_envp.c \
			node_actions/envp_node/get_envp_len.c \
			node_actions/envp_node/find_envp_node.c \
			node_actions/token_node/add_token_back.c \
			node_actions/token_node/create_new_token.c \
			node_actions/token_node/last_token_node.c \
			node_actions/token_node/token_len.c \
			node_actions/token_node/count_types.c \
			node_actions/token_node/get_type_existence.c \
			node_actions/redir_node/add_redir_back.c \
			node_actions/redir_node/create_new_redir.c \
			node_actions/redir_node/last_redir_node.c \
			node_actions/redir_node/count_redir.c \

SRC := $(addprefix $(SRC_DIR)/, $(SRC))
UTILS_SRC := $(addprefix $(UTILS_DIR)/, $(UTILS_SRC))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
UTILS_OBJ = $(UTILS_SRC:$(UTILS_DIR)/%.c=$(OBJ_DIR)/%.o)

ifeq ($(SYSTEM), Darwin)
    READLINE_DIR = /opt/homebrew/opt/readline
    INCLUDES = -I$(READLINE_DIR)/include -I includes/
    LIBS = -L$(READLINE_DIR)/lib -lreadline
else
    INCLUDES = -I includes/
    LIBS = -lreadline
endif

all: $(OBJ_DIR) $(NAME)
$(NAME): $(OBJ) $(UTILS_OBJ) 
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(UTILS_OBJ)  -o  $(NAME) $(LIBFT) $(INCLUDES) $(LIBS) 
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
