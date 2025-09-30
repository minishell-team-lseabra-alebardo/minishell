# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alebarbo <alebarbo@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/29 20:54:21 by alebarbo          #+#    #+#              #
#    Updated: 2025/09/30 02:04:46 by alebarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc -Wall -Wextra -Werror -ggdb -fsanitize=address
INC = -Ilibft -Iincs
LIB = -Llibft -lft -lreadline
SRC = srcs/ft_add_history.c srcs/ft_built_ins.c
OBJ = $(SRC:.c=.o)

PHONY: all libft re fclean clean

all: $(NAME)

re: fclean all

$(NAME): $(OBJ)
	$(CC) $(INC) $^ $(LIB) -o $@

$(OBJ): $(SRC)
	$(CC) $(INC) -c $^

libft:
	$(MAKE) -C ./libft/ all

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C ./libft/ fclean

clean:
	rm -rf $(OBJ)
	$(MAKE) -C ./libft/ clean