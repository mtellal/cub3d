/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:57:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/09/23 12:57:44 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initImg3D(t_data *data, t_frame *img3D)
{
	img3D->window = mlx_new_window(data->mlx, img3D->width, img3D->height, "cub3d");
	img3D->img = mlx_new_image(data->mlx, img3D->width, img3D->height);
	img3D->addr = mlx_get_data_addr(img3D->img, &img3D->bpp, &img3D->length, &img3D->endian);
	cast_and_display(data);
}

int	get_color(char *s)
{
	int r = ft_atoi(s);
	int g = ft_atoi(s + 4);
	int b = ft_atoi(s + 8);
	return (r << 16 | g << 8 | b);
}

void	initTexture(t_data *data, void *mlx, t_texture *texture)
{
	texture->walln.img = mlx_xpm_file_to_image(mlx, data->n_texture, &texture->walln.width, &texture->walln.height);
	texture->walln.addr = mlx_get_data_addr(texture->walln.img, &texture->walln.bpp, 
	&texture->walln.length,&texture->walln.endian);

	texture->walls.img = mlx_xpm_file_to_image(mlx, data->s_texture, &texture->walls.width, &texture->walls.height);
	texture->walls.addr = mlx_get_data_addr(texture->walls.img, &texture->walls.bpp, 
	&texture->walls.length, &texture->walls.endian);

	texture->wallo.img = mlx_xpm_file_to_image(mlx, data->w_texture, &texture->wallo.width, &texture->wallo.height);
	texture->wallo.addr = mlx_get_data_addr(texture->wallo.img, &texture->wallo.bpp, 
	&texture->wallo.length, &texture->wallo.endian);

	texture->walle.img = mlx_xpm_file_to_image(mlx, data->e_texture, &texture->walle.width, &texture->walle.height);
	texture->walle.addr = mlx_get_data_addr(texture->walle.img, &texture->walle.bpp, 
	&texture->walle.length, &texture->walle.endian);

	texture->cieling = get_color(data->c_texture);
	texture->floor = get_color(data->f_texture);
}

void	initImgDimensions(t_data *data)
{
	data->img2D.height = data->height * GRID;
	data->img2D.width = data->len * GRID;
	data->img3D.height = data->height * GRID2;
	data->img3D.width = data->len * GRID2;
}

void	init(t_data *data)
{
	data->rays = NULL;
	data->mlx = mlx_init();
	initImgDimensions(data);
	initImg2D(data, &data->img2D);
	initTexture(data, data->mlx, &data->texture);
	initImg3D(data, &data->img3D);
}
