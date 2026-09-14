NAME = minishell

SRC_DIR = sources
TOKENIZER_DIR =$(SRC_DIR)/tokenizer
AST_DIR       = $(SRC_DIR)/AST
BUILTINS_DIR = $(SRC_DIR)/builtins
ENV_DIR      = $(SRC_DIR)/env
EXPANSION_DIR = $(SRC_DIR)/expansion
EXEC_DIR = $(SRC_DIR)/execution
REDIR_DIR = $(SRC_DIR)/redirections
UTILS_DIR = $(SRC_DIR)/utils
SIGNALS_DIR = $(SRC_DIR)/signals
LIBFT_DIR = libft
INCLUDES_DIR = includes
READLINE_DIR = $(shell brew --prefix readline 2>/dev/null)
LIBFT = $(LIBFT_DIR)/libft.a

ifeq ($(READLINE_DIR),)
READLINE_INC =
READLINE_LIB = -lreadline
else
READLINE_INC = -I$(READLINE_DIR)/include
READLINE_LIB = -L$(READLINE_DIR)/lib -lreadline
endif

SRCS = $(SRC_DIR)/main.c \
       $(SIGNALS_DIR)/signals.c \
       $(TOKENIZER_DIR)/ft_strndup.c \
       $(TOKENIZER_DIR)/tokenizer.c \
       $(TOKENIZER_DIR)/tokenizer_utils.c \
       $(AST_DIR)/ast.c \
       $(AST_DIR)/free_ast.c \
       $(AST_DIR)/node_utils.c \
       $(AST_DIR)/ast_to_cmd.c \
       $(AST_DIR)/ast_to_cmd_fill.c \
       $(AST_DIR)/ast_to_cmd_redir.c \
       $(AST_DIR)/ast_to_cmd_tree.c \
       $(AST_DIR)/builders_fn/and_fn.c \
       $(AST_DIR)/builders_fn/heredoc_fn.c \
       $(AST_DIR)/builders_fn/lparen_fn.c \
       $(AST_DIR)/builders_fn/or_fn.c \
       $(AST_DIR)/builders_fn/pipeline_fn.c \
       $(AST_DIR)/builders_fn/redirect_append_fn.c \
       $(AST_DIR)/builders_fn/redirect_in_fn.c \
       $(AST_DIR)/builders_fn/redirect_out_fn.c \
       $(AST_DIR)/builders_fn/word_fn.c \
       $(BUILTINS_DIR)/cd.c \
       $(BUILTINS_DIR)/echo.c \
       $(BUILTINS_DIR)/env.c \
       $(BUILTINS_DIR)/exit.c \
       $(BUILTINS_DIR)/export.c \
       $(BUILTINS_DIR)/pwd.c \
       $(BUILTINS_DIR)/unset.c \
       $(ENV_DIR)/env.c \
       $(ENV_DIR)/env_set.c \
       $(EXPANSION_DIR)/identify_var.c \
       $(EXPANSION_DIR)/expand_word.c \
       $(EXPANSION_DIR)/expand_command.c \
       $(EXPANSION_DIR)/quotes_handler.c \
       $(EXPANSION_DIR)/quotes_remover.c \
       $(EXPANSION_DIR)/recover_value.c \
       $(EXPANSION_DIR)/replace_var.c \
       $(EXPANSION_DIR)/var_expander.c \
       $(EXPANSION_DIR)/var_expander_utils.c \
       $(EXEC_DIR)/execute.c \
       $(EXEC_DIR)/execute_pipeline.c \
       $(EXEC_DIR)/execute_cmd.c \
       $(EXEC_DIR)/execute_utils.c \
       $(EXEC_DIR)/parse_path.c \
       $(REDIR_DIR)/file_io.c \
       $(REDIR_DIR)/heredoc.c \
       $(REDIR_DIR)/heredoc_utils.c \
       $(REDIR_DIR)/pipe.c \
       $(REDIR_DIR)/prepare_redir.c \
       $(UTILS_DIR)/cleanup.c \
       $(UTILS_DIR)/error.c \
       $(UTILS_DIR)/exit.c \
       $(UTILS_DIR)/init_data.c \
       $(UTILS_DIR)/list_utils.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

INCLUDES = -I$(INCLUDES_DIR) \
	   -I$(TOKENIZER_DIR) \
	   -I$(AST_DIR) \
	   -I$(SIGNALS_DIR) \
	   -I$(LIBFT_DIR) \
	   $(READLINE_INC)

all :	$(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_LIB) -o $(NAME)

%.o:	%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean :
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY: all clean fclean re
