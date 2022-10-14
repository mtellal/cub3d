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

SRC =	$(addprefix src/, main.c draw.c operations.c events.c init.c $(RAYDIR) $(MOVEDIR))

MOVEDIR = $(addprefix move/, move.c movements.c utils.c vmovements.c rotate.c)

RAYDIR = $(addprefix rays/, rays.c utils.c displayRays.c)

OBJ = $(SRC:.c=.o)

HEADERMLX = -I/usr/include -I./libft/ -I./include/ -I./minilibx-linux

HEADERS = $(addprefix include/, types.h cub3d.h )

LIBMLX  =  -Llibft/ -lft -L./minilibx-linux -lmlx_Linux -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) $(HEADERMLX) -o $@ -c $<

$(NAME): $(OBJ) $(HEADERS)
	make -C libft/ 
	make -C minilibx-linux/
	$(CC) $(FLAGS) $(HEADERMLX) -o $(NAME) $(OBJ) $(LIBMLX)


clean:
	rm -rf $(OBJ)
	make clean -C libft/
	make clean -C minilibx-linux/
	

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/
	#make fclean -C minilibx-linux/
	

re: fclean all 
