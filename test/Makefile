# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miaandri <miaandri@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 13:54:57 by miaandri          #+#    #+#              #
#    Updated: 2024/11/03 08:39:15 by miaandri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c echo.c get_struct.c utils.c pwd.c get_env.c list_utils.c \
		env.c

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