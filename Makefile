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

SRC =	$(addprefix src/, main.c draw.c operations.c $(MOVEDIR))

MOVEDIR = $(addprefix move/, move.c movements.c utils.c)

OBJ = $(SRC:.c=.o)

HEADERMLX = -I/usr/include -I./libft/ -I./include/

HEADERS = $(addprefix include/, types.h)

LIBMLX  =  -Llibft/ -lft -L/usr/lib/ -lmlx_Linux -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) $(HEADERMLX) -o $@ -c $<

$(NAME): $(OBJ) $(HEADERS)
	make -C libft/ 
	$(CC) $(FLAGS) $(HEADERMLX) -o $(NAME) $(OBJ) $(LIBMLX)


clean:
	make clean -C libft/
	rm -rf $(OBJ)

fclean: clean 
	make fclean -C libft/
	rm -rf $(NAME)

re: fclean all 
