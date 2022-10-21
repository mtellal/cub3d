# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/17 16:32:26 by mtellal           #+#    #+#              #
#    Updated: 2022/10/21 11:33:30 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang 
FLAGS = -Wall -Wextra -Werror -g 
NAME = cub3d


SRC=$(addprefix src/, main.c draw.c events.c utils.c exit.c $(INITDIR) $(DISPLAYDIR) $(GNLDIR) $(PARSINGDIR) $(RAYDIR) $(MOVEDIR))
INITDIR=$(addprefix init/, init.c initTriangle.c initImg2D.c)
DISPLAYDIR=$(addprefix display/, minimap.c)
GNLDIR= $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)
PARSINGDIR=$(addprefix parsing/, parse_content.c parse_file.c parse_map.c parse_map_utils.c \
			chck_edge.c trim_map.c chck_player.c chck_textures.c init.c free_utils.c)
MOVEDIR=$(addprefix move/, move.c movements.c movements_utils.c rotate.c radians_deg.c vmovements.c)
RAYDIR=$(addprefix rays/, rays.c horizontal_cast.c vertical_cast.c utils.c \
			display/displayRays.c )
OBJ=$(SRC:.c=.o)

HEADERMLX = -I/usr/include -I./libft/ -I./include/ -I./minilibx-linux

HEADERS = $(addprefix include/, types.h cub3d.h macros.h)

LIBMLX  =  -Llibft/ -lft -L./minilibx-linux -lmlx_Linux -lmlx -lXext -lX11 -lm -lz


all: $(NAME)

$(NAME): LIBS $(OBJ) 
	@$(CC) $(FLAGS) $(HEADERMLX) -o $(NAME) $(OBJ) $(LIBMLX)
	@echo '\033[0;32m' "compilation succeed"


%.o: %.c 
	@echo "compiling " $(@D) "/" $(@F)
	@$(CC) $(FLAGS) $(HEADERMLX) -o $@ -c $<

LIBS:
	@make -C libft/ 
	@make -C minilibx-linux/

clean:
	@rm -rf $(OBJ)
	@make clean -C libft/
	@make clean -C minilibx-linux/
	

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft/

re: fclean all 


