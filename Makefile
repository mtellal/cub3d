# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/04 15:56:25 by antbarbi          #+#    #+#              #
#    Updated: 2022/09/20 15:33:42 by antbarbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d
CC = clang
FLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -L./minilibx_linux -lmlx_Linux -L/usr/bin -lX11 -lXext -lm 
MLX_INC = -Iminilibx_linux
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = -Iinclude -Ilibft
RM = rm -rf
LIBS = minilibx_linux
MYLIB = libft

SRC = $(GNL) $(PARSING)

GNL = get_next_line.c get_next_line_utils.c
PARSING = parse_content.c parse_file.c parse_map.c parse_map_utils.c chck_edge.c

GNL := $(GNL:%.c=get_next_line/%.c)
PARSING := $(PARSING:%.c=parsing/%.c)
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(NAME): libs $(OBJ) $(INCLUDE:%.h=$(INC_DIR)/%.h)
	@echo "Compiling $(NAME)..."
	@$(CC) $(MLX_INC) $(INC_DIR) $(FLAGS) -o cub3d src/main.c $(OBJ) -L$(MYLIB) -lft -lncurses $(MLX_FLAGS)
	@echo "Compilation success!"
	
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo "compiling $@..."
	@$(CC) $(FLAGS) $(MLX_INC) $(INC_DIR) -c $< -o $@

libs:
	@echo "Making libs..."
	@$(MAKE) -C $(LIBS)
	@$(MAKE) -C $(MYLIB)

clean :
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBS) clean
	@$(MAKE) -C $(MYLIB) clean

fclean : clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(MYLIB) fclean

re : fclean all

debug: CFLAGS += -g
debug: fclean
sanitize: CFLAGS += -fsanitize=address
sanitize: debug

.PHONY: all $(NAME) clean fclean libs re debug