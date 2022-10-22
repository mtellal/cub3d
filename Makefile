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

CC=clang 
FLAGS=-Wall -Wextra -Werror -g 
NAME=cub3d
NAMEB=cub3d_bonus

SRC=$(addprefix src/, main.c draw.c events.c utils.c exit.c free_utils.c \
						$(INITDIR) $(GNLDIR) $(PARSINGDIR) $(RAYDIR) $(MOVEDIR))
INITDIR=$(addprefix init/, init.c initTriangle.c initimg2d.c)
GNLDIR= $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)
PARSINGDIR=$(addprefix parsing/, parse_content.c parse_file.c parse_map.c parse_map_utils.c \
								chck_edge.c trim_map.c chck_player.c chck_textures.c init.c)
MOVEDIR=$(addprefix move/, move.c movements.c movements_utils.c rotate.c radians_deg.c vmovements.c)
RAYDIR=$(addprefix rays/, rays.c cast_a_ray.c horizontal_cast.c vertical_cast.c utils.c \
						display/minimap.c display/displayRays.c display/displayTextures.c)
OBJ=$(SRC:.c=.o)

SRCBONUS= $(addprefix bonus/, $(SRC:.c=_bonus.c)) 
OBJBONUS=$(SRCBONUS:_bonus.c=_bonus.o)

HEADERS = -I/usr/include -I./libft/ -I./include/ -I./minilibx-linux
LIBMLX  =  -Llibft/ -lft -L./minilibx-linux -lmlx_Linux -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): LIBS $(OBJ) 
	@$(CC) $(FLAGS) $(HEADERS) -o $(NAME) $(OBJ) $(LIBMLX)
	@echo '\033[0;32m' "compilation succeed"

bonus: LIBS $(OBJBONUS)
	@$(CC) $(FLAGS) $(HEADERS) -o $(NAMEB) $(OBJBONUS) $(LIBMLX)
	@echo '\033[0;32m' "compilation succeed"

%.o: %.c 
	@echo "compiling " $(@D) "/" $(@F)
	@$(CC) $(FLAGS) $(HEADERS) -o $@ -c $<


LIBS:
	@make -C libft/ 
	@make -C minilibx-linux/

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJBONUS)
	@make clean -C libft/
	@make clean -C minilibx-linux/

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAMEB)
	@make fclean -C libft/

re: fclean all 


