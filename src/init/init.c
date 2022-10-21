/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:57:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/21 15:39:44 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initimg3d(t_data *d, t_frame *i)
{
	i->window = mlx_new_window(d->mlx, i->width, i->height, "cub3d");
	i->img = mlx_new_image(d->mlx, i->width, i->height);
	i->addr = mlx_get_data_addr(i->img, &i->bpp, &i->length, &i->endian);
	cast_and_display(d);
}

int	get_color(char *s)
{
	char	**srgb;
	int		r;
	int		g;
	int		b;

	srgb = ft_split(s, ',');
	r = ft_atoi(srgb[0]);
	g = ft_atoi(srgb[1]);
	b = ft_atoi(srgb[2]);
	free_tabs(srgb);
	return (r << 16 | g << 8 | b);
	return (0);
}

void	inittexture(t_data *d, void *mlx, t_texture *t)
{
	t->walln.img = mlx_xpm_file_to_image(mlx, d->n_texture,
			&t->walln.width, &t->walln.height);
	t->walln.addr = mlx_get_data_addr(t->walln.img, &t->walln.bpp,
			&t->walln.length, &t->walln.endian);
	t->walls.img = mlx_xpm_file_to_image(mlx, d->s_texture,
			&t->walls.width, &t->walls.height);
	t->walls.addr = mlx_get_data_addr(t->walls.img, &t->walls.bpp,
			&t->walls.length, &t->walls.endian);
	t->wallo.img = mlx_xpm_file_to_image(mlx, d->w_texture,
			&t->wallo.width, &t->wallo.height);
	t->wallo.addr = mlx_get_data_addr(t->wallo.img, &t->wallo.bpp,
			&t->wallo.length, &t->wallo.endian);
	t->walle.img = mlx_xpm_file_to_image(mlx, d->e_texture,
			&t->walle.width, &t->walle.height);
	t->walle.addr = mlx_get_data_addr(t->walle.img, &t->walle.bpp,
			&t->walle.length, &t->walle.endian);
	t->cieling = get_color(d->c_texture);
	t->floor = get_color(d->f_texture);
}

void	initimgdimensions(t_data *data)
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
	initimgdimensions(data);
	initimg2d(data, &data->img2D);
	inittexture(data, data->mlx, &data->texture);
	initimg3d(data, &data->img3D);
}
