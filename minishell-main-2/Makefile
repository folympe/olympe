NAME = minishell

TOKENIZER_DIR = tokenizer
AST_DIR       = AST
EXEC_DIR      = exec

SRCS = minishell.c \
       $(TOKENIZER_DIR)/ft_strlen.c \
       $(TOKENIZER_DIR)/ft_strncmp.c \
       $(TOKENIZER_DIR)/ft_strndup.c \
       $(TOKENIZER_DIR)/tokenizer.c \
       $(AST_DIR)/ast.c \
       $(AST_DIR)/node_utils.c \
       $(AST_DIR)/builders_fn/and_fn.c \
       $(AST_DIR)/builders_fn/or_fn.c \
       $(AST_DIR)/builders_fn/pipeline_fn.c \
       $(AST_DIR)/builders_fn/redirect_append_fn.c \
       $(AST_DIR)/builders_fn/redirect_in_fn.c \
       $(AST_DIR)/builders_fn/redirect_out_fn.c \
       $(AST_DIR)/builders_fn/word_fn.c

OBJDIR = obj
DEPDIR = dep


OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
DEPS = $(addprefix $(DEPDIR)/,$(SRCS:.c=.d))

CC = cc

FLAGS = -Wall -Werror -Wextra -g

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME)

$(OBJDIR)/%.o : %.c
	mkdir -p $(dir $@)
	mkdir -p $(DEPDIR)/$(dir $*)
	$(CC) $(FLAGS) -MMD -MP -MF $(DEPDIR)/$*.d -c $< -o $@

$(OBJDIR) $(DEPDIR):
	mkdir -p $@

all : $(NAME)

clean :
	rm -f $(OBJS) $(DEPS)
	rm -rf $(OBJDIR) $(DEPDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

-include $(DEPS)

.PHONY: all clean fclean re