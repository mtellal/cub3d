/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:31:58 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/20 12:54:51 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	exit_game_clean(&data);
	free_rays(data.rays, data.img2D.width);
	free_texture(&data);
	free_map(&data);
}
