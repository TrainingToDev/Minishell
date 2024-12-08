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

SRC = main.c pipe_utils.c quote_utils.c split_pile.c manage_array.c\
		get_token.c token_utils.c get_state.c quote_error.c utils.c\
		split_expand.c  get_env.c list_utils.c specific_case.c\
		exec.c expand.c expand_utils.c get_off_quote.c
		
CC = cc -g -Wall -Werror -Wextra 

RM = rm -f

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT) -lreadline

$(LIBFT):
			make bonus -C libft
	
%.o : %.c
			make bonus -C libft
			$(CC) -o $@ -c $<

clean :
			make clean -C libft
			$(RM) $(OBJ)

fclean : clean
			$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re