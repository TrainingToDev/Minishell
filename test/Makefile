# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 13:54:57 by miaandri          #+#    #+#              #
#    Updated: 2024/11/02 14:52:56 by miaandri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c echo.c get_struct.c utils.c

CC = cc -g -Wall -Werror -Wextra 

RM = rm -f

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT) -lreadline

$(LIBFT):
			make -C libft
	
%.o : %.c
			make -C libft
			$(CC) -o $@ -c $<

clean :
			make clean -C libft
			$(RM) $(OBJ)

fclean : clean
			$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re