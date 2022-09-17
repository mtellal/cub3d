# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtellal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/17 16:32:26 by mtellal           #+#    #+#              #
#    Updated: 2022/09/17 22:21:36 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 

FLAGS = -Wall -Wextra -Werror

NAME = cub3d

SRC = main.c

OBJ = $(SRC:.c=.o)

HEADERMLX = -I/usr/include -I./libft/ 

LIBMLX  =  -Llibft/ -lft -L/usr/lib/ -lmlx_Linux -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(OBJ): $(SRC)
	$(CC) $(FLAGS) $(HEADERMLX) -c $(SRC)

$(NAME): $(OBJ) $(HEADER)
	make -C libft/
	$(CC) $(FLAGS) $(HEADERMLX) -o $(NAME) $(OBJ) $(LIBMLX)

clean:
	make clean -C libft/
	rm -rf $(OBJ)

fclean: clean 
	make fclean -C libft/
	rm -rf $(NAME)

re: fclean all 
