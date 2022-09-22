/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 11:16:28 by antbarbi          #+#    #+#             */
/*   Updated: 2022/09/22 15:34:17 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <mlx_int.h>
# include <math.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <libft.h>

# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <unistd.h>
# include "get_next_line.h"

typedef struct s_data
{
	char	**map;
	int		len;
	int		height;
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	char	*f_texture;
	char	*c_texture;
}	t_data;

//Misc
void	exit_message(t_data *data, char *str);
void	free_map(t_data *data);

//Parsing
void	chck_map_elem(t_data *data);
void	chck_map_edges(t_data *data);
void	check_file_name(t_data *data, char *file);
void	read_cub(t_data *data, char *path_cub);
int		parse_content(t_data *data, char *line);
int		parse_color(char **texture, char *line, char c);
int		parse_by_id(char **texture, char *line, char *id);
int		parse_map(t_data *data, char *line);
int		ft_maplen(char **map);
int		ft_mapsize(char **map);
int		nb_of_zeros(char **map);

//Todelete
void	print_map(char	**map);

#endif