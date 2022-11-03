/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:57:36 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/03 15:27:02 by antbarbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initimg3d(t_data *d, t_frame *i)
{
	i->window = mlx_new_window(d->mlx, i->width, i->height, "cub3d");
	i->img = mlx_new_image(d->mlx, i->width, i->height);
	if (!i->window || !i->img)
		exit_message(d, "Mlx new window/img failed");
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

int	err_init_texture(t_img *texture, void *mlx, char *file)
{
	texture->img = mlx_xpm_file_to_image(mlx, file,
			&texture->width, &texture->height);
	if (!texture->img)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->length, &texture->endian);
	return (0);
}

void	inittexture(t_data *d, void *mlx, t_texture *t)
{
	if (err_init_texture(&t->walln, mlx, d->n_texture))
	{
		exit_game_clean(d);
		exit_message(d, "NO file can't be converted to xpm file");
	}
	if (err_init_texture(&t->walls, mlx, d->s_texture))
	{
		exit_game_clean(d);
		exit_message(d, "SO file can't be converted to xpm file");
	}
	if (err_init_texture(&t->wallo, mlx, d->w_texture))
	{
		exit_game_clean(d);
		exit_message(d, "WE file can't be converted to xpm file");
	}
	if (err_init_texture(&t->walle, mlx, d->e_texture))
	{
		exit_game_clean(d);
		exit_message(d, "EA file can't be converted to xpm file");
	}
	t->cieling = get_color(d->c_texture);
	t->floor = get_color(d->f_texture);
}

void	init(t_data *data)
{
	data->img2d.height = data->height * GRID;
	data->img2d.width = data->len * GRID;
	data->img3d.height = data->height * GRID2;
	data->img3d.width = data->len * GRID2;
	data->rays = NULL;
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_message(data, "Mlx init failed");
	inittexture(data, data->mlx, &data->texture);
	initimg2d(data, &data->img2d);
	initimg3d(data, &data->img3d);
}
