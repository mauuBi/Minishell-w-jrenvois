NAME = minishell

CC = cc

INCLUDES_PATH = includes

# LIBFT LIB
LIBFT_PATH = src/libft
LIBFT_LIB = $(LIBFT_PATH)/libft.a

LIBFLAGS = -lreadline
CFLAGS = -I$(LIBFT_PATH) -I$(INCLUDES_PATH) -Wall -Wextra -Werror -g

SRC_FILES = src/main.c src/lexer/token.c src/lexer/token_list.c src/lexer/handlers/handle_word.c src/utils/char_utils.c \
			src/lexer/lexer.c src/lexer/handlers/handle_operator.c src/lexer/handlers/handle_quote.c \
			src/lexer/handlers/handle_backslash.c src/lexer/error.c src/lexer/handlers/handle_newline.c src/lexer/validator.c \
			src/lexer/validator_utils.c src/utils/free_utils.c src/ast/ast.c src/ast/node.c \
			src/parser/movement.c src/parser/parse_command.c src/parser/parse_redirects.c src/parser/parser.c \
			src/parser/parse_pipe.c src/parser/parse_operator.c src/parser/parse_list.c src/parser/heredoc_handler.c \
			src/builtins/echo.c src/utils/env_utils.c src/utils/tab_utils.c src/utils/path_utils.c \
			src/builtins/pwd.c src/builtins/env.c src/builtins/export.c \
			src/builtins/unset.c src/builtins/cd.c src/builtins/exit.c src/expand/expand.c src/expand/expand_utils.c \
			src/expand/env.c src/expand/quotes.c src/expand/chars.c src/exec/exec.c src/exec/exec_utils.c \
			src/exec/exec_builtin.c src/exec/exec_external.c src/exec/exec_pipe.c src/exec/exec_redirects.c \
			src/utils/signal_utils.c src/utils/heredoc_utils.c src/parser/heredoc.c

OBJ_FILES = $(SRC_FILES:.c=.o)

all: libft $(NAME)

%.o : %.c $(INCLUDES_PATH)/minishell.h
	$(CC) $(CFLAGS) -c -o $@ $<

libft:
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJ_FILES) includes/minishell.h
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT_LIB) $(LIBFLAGS) -o $(NAME)

clean:
	@make -C $(LIBFT_PATH) clean
	rm -f $(OBJ_FILES)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft