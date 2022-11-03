/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:40:42 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/20 16:04:51 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct_and_parsing(t_data *data, char *str)
{
	data->map = NULL;
	data->n_texture = NULL;
	data->s_texture = NULL;
	data->w_texture = NULL;
	data->e_texture = NULL;
	data->f_texture = NULL;
	data->c_texture = NULL;
	check_file_name(data, str);
	read_cub(data, str);
	chck_textures(data);
	chck_map_elem(data);
	chck_map_edges(data);
	final_map(data);
}
