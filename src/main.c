/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:31:58 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/17 22:18:47 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_data *data)
{
	int i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
		{
			if (data->map[i])
			{
				free(data->map[i]);
				data->map[i] = NULL;
			}
			i++;
		}
		free(data->map);
		data->map = NULL;
	}
}

void	free_texture(t_data *data)
{
	if (data->n_texture)
		free(data->n_texture);
	if (data->s_texture)
		free(data->s_texture);
	if (data->w_texture)
		free(data->w_texture);
	if (data->e_texture)	
		free(data->e_texture);
	if (data->c_texture)	
		free(data->c_texture);
	if (data->f_texture)	
		free(data->f_texture);	
}

void	exit_message(t_data *data, char *str)
{
	ft_putendl_fd("Error", 2);
	if (str)
		ft_putendl_fd(str, 2);
	free_texture(data);
	free_map(data);
	exit(-1);
}

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


void	game(t_data *data)
{
	mlx_hook(data->img3D.window, 3, 1L<<1, keyReleased, &data->img2D);

	mlx_hook(data->img3D.window, 2, 1L<<0,  keyPressed, data);

	mlx_hook(data->img3D.window, ClientMessage,
		StructureNotifyMask, exit_cross, data);
 
	mlx_loop_hook(data->mlx, handle_input, data);
}



int main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Not enough arguments", 2);
		return (-1);
	}
	init_struct_and_parsing(&data, argv[1]);

	init(&data);
	game(&data);

	mlx_loop(data.mlx);

	free_texture(&data);
	free_map(&data);
}
