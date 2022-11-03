/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:56:06 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/03 15:15:24 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_cross(t_data *data)
{
	exit_game(data);
	return (0);
}

void	exit_game(t_data *data)
{
	mlx_destroy_window(data->mlx, data->img3d.window);
	data->img3d.window = NULL;
}

void	exit_game_clean(t_data *data)
{
	if (data->img2d.img)
		mlx_destroy_image(data->mlx, data->img2d.img);
	if (data->img3d.img)
		mlx_destroy_image(data->mlx, data->img3d.img);
	if (data->texture.walle.img)
		mlx_destroy_image(data->mlx, data->texture.walle.img);
	if (data->texture.wallo.img)
		mlx_destroy_image(data->mlx, data->texture.wallo.img);
	if (data->texture.walls.img)
		mlx_destroy_image(data->mlx, data->texture.walls.img);
	if (data->texture.walln.img)
		mlx_destroy_image(data->mlx, data->texture.walln.img);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}
