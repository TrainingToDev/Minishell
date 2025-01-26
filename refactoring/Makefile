# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 13:54:57 by miaandri          #+#    #+#              #
#    Updated: 2024/12/07 03:30:30 by miaandri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDE_DIR)

SRC_DIR = srcs
INCLUDE_DIR = include
OBJ_DIR = obj
BUILTINS_DIR = $(SRC_DIR)/builtins
EXEC_DIR = $(SRC_DIR)/exec
LEXER_DIR = $(SRC_DIR)/lexer
EXPAND_DIR = $(SRC_DIR)/expand
PARSER_DIR = $(SRC_DIR)/parser
UTILS_DIR = $(SRC_DIR)/utils
LIBFT_DIR = libft/libft.a

SRC_FILES = $(SRC_DIR)/main.c \
			$(LEXER_DIR)/lexer.c  \
			$(LEXER_DIR)/token_operator.c  \
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
			$(EXPAND_DIR)/expand_status.c\
			$(EXPAND_DIR)/expand_var.c \
			$(EXPAND_DIR)/expand.c \
			$(EXPAND_DIR)/utils_expand.c\
			$(PARSER_DIR)/free_ast.c\
			$(PARSER_DIR)/main_cmd.c\
			$(PARSER_DIR)/main_list.c\
			$(PARSER_DIR)/node_parser.c\
			$(PARSER_DIR)/parser_pipe.c\
			$(PARSER_DIR)/parser_cmd.c\
			$(PARSER_DIR)/parser_cond.c\
			$(PARSER_DIR)/parser_operation.c\
			$(PARSER_DIR)/parser_redir.c\
			$(PARSER_DIR)/parser_subshell.c\
			$(PARSER_DIR)/utils_parser.c\
			$(PARSER_DIR)/parser.c\
			$(PARSER_DIR)/print_parser.c\
			$(EXEC_DIR)/exec_builtins.c\
			$(EXEC_DIR)/exec_ext_utils.c\
			$(EXEC_DIR)/exec_external.c\
			$(EXEC_DIR)/exec.c\
			$(EXEC_DIR)/heredoc_utils.c \
			$(EXEC_DIR)/heredoc_utils_2.c\
			$(EXEC_DIR)/part_bonus.c\
			$(EXEC_DIR)/pipe.c\
			$(EXEC_DIR)/redir.c\
			$(EXEC_DIR)/redirection.c\
			$(EXEC_DIR)/utils.c\
			$(EXEC_DIR)/utils_1.c\
			$(UTILS_DIR)/check_args.c \
			$(UTILS_DIR)/content_heredoc.c \
			$(UTILS_DIR)/environement.c \
			$(UTILS_DIR)/error.c \
			$(UTILS_DIR)/prompt.c \
			$(UTILS_DIR)/signal.c \
			$(UTILS_DIR)/utils_heredoc.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT_DIR) -lreadline

$(LIBFT_DIR):
	@echo "Making libft..."
	@make -sC libft
	@echo "LIBFT success"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/utils $(OBJ_DIR)/lexer $(OBJ_DIR)/parser $(OBJ_DIR)/exec $(OBJ_DIR)/builtins $(OBJ_DIR)/expand
	@echo "Building $@ from $<"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re

