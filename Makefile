# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/17 16:32:26 by mtellal           #+#    #+#              #
#    Updated: 2022/11/05 16:55:52 by mtellal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=clang 
FLAGS=-Wall -Wextra -Werror -g -fsanitize=address 
NAME=cub3D

SRCDIR=src
BONUSDIR=bonus
OBJDIR=obj

SRC=main.c draw.c events.c utils.c exit.c free_utils.c
INIT=init.c initTriangle.c initimg2d.c
MOVE=move.c movements.c movements_utils.c rotate.c radians_deg.c vmovements.c
GNL=get_next_line.c get_next_line_utils.c
PARSING=parse_content.c parse_file.c parse_map.c parse_map_utils.c chck_edge.c trim_map.c chck_player.c chck_textures.c chck_textures_utils.c init.c
RAYS=rays.c cast_a_ray.c horizontal_cast.c vertical_cast.c rays_utils.c
RAYS_DISPLAY= displayRays.c displayTextures.c

INITDIR=$(addprefix init/, $(INIT))
MOVEDIR=$(addprefix move/, $(MOVE))
GNLDIR= $(addprefix get_next_line/, $(GNL))
PARSINGDIR=$(addprefix parsing/, $(PARSING))
RAYSDIR=$(addprefix rays/, $(RAYS) $(RAYS_DISPLAY:%.c=display/%.c))

SRCFILES=$(addprefix $(SRCDIR)/, $(SRC) $(INITDIR) $(MOVEDIR) $(GNLDIR) $(PARSINGDIR) $(RAYSDIR))
SRCFILESB=$(addprefix $(BONUSDIR)/, $(SRC:.c=_bonus.c) $(INITDIR:.c=_bonus.c) $(MOVEDIR:.c=_bonus.c) \
						$(GNLDIR:.c=_bonus.c) $(PARSINGDIR:.c=_bonus.c) $(RAYSDIR:.c=_bonus.c)) \
						bonus/rays/display/minimap_bonus.c

OBJ=$(addprefix $(OBJDIR)/, $(SRCFILES:.c=.o))
OBJBONUS=$(addprefix $(OBJDIR)/, $(SRCFILESB:.c=.o))

HEADERS = -I/usr/include -I./libft/ -I./include/ -I./minilibx-linux
LIBMLX  =  -Llibft/ -lft -L./minilibx-linux -lmlx_Linux -lmlx -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/ 
	@make -C minilibx-linux/
	@$(CC) $(FLAGS) $(HEADERS) -o $(NAME) $(OBJ) $(LIBMLX)
	@echo '\033[0;32m' "compilation succeed"

bonus: $(OBJBONUS)
	@make -C libft/ 
	@make -C minilibx-linux/
	@$(CC) $(FLAGS) $(HEADERS) -o $(NAME) $(OBJBONUS) $(LIBMLX)
	@echo '\033[0;32m' "compilation succeed"

$(OBJDIR)/$(BONUSDIR)/%.o: $(BONUSDIR)/%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(@D)
	@echo "compiling " $(@D) "/" $(@F)
	@$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< 

$(OBJDIR)/$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(@D)
	@echo "compiling " $(@D) "/" $(@F)
	@$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< 


clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(OBJBONUS)
	@make clean -C libft/
	@make clean -C minilibx-linux/

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAMEB)
	@make fclean -C libft/

re: fclean all 


