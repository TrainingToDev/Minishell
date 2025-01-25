
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDE_DIR)

SRC_DIR = srcs
INCLUDE_DIR = include
OBJ_DIR = obj
BUILTINS_DIR = $(SRC_DIR)/builtins
EXEC_DIR = $(SRC_DIR)/exec
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
UTILS_DIR = $(SRC_DIR)/utils
FREE_DIR = $(SRC_DIR)/free
LIBFT_DIR = libft/libft.a


#lexer
SRC_FILES = $(SRC_DIR)/main.c \
			$(FREE_DIR)/lexer.c  \
			$(FREE_DIR)/token_operator.c  \
			$(LEXER_DIR)/token_word.c  \
			$(LEXER_DIR)/check_operators.c  \
			$(LEXER_DIR)/check_parentheses.c  \
			$(LEXER_DIR)/check_redirection.c  \
			$(LEXER_DIR)/check_syntax.c  \
			$(LEXER_DIR)/invalid_redir.c  \
			$(LEXER_DIR)/utils_invalid.c  \
			$(LEXER_DIR)/utils_paren.c  \
			$(LEXER_DIR)/utils_token.c  \
			$(LEXER_DIR)/utils_word.c  \
			$(LEXER_DIR)/free_tokens.c  \
			$(LEXER_DIR)/print_tokens.c  \
			
			$(UTILS_DIR)/check_args.c  \
			$(UTILS_DIR)/error.c  \
			$(UTILS_DIR)/prompt.c  \
			$(UTILS_DIR)/signal.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT_DIR) -lreadline

$(LIBFT_DIR):
	@echo "Making libft..."
	@make -sC libft
	@echo "LIBFT success"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/lexer $(OBJ_DIR)/utils $(OBJ_DIR)/free
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
