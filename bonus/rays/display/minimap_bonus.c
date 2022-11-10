/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:29:44 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/08 18:14:00 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap_init_img3d(int *s_map, t_coor *pos_mnmap3D)
{
	*s_map = WIDTH * 0.2;
	pos_mnmap3D->x = WIDTH - (*s_map + *s_map * 0.1);
	pos_mnmap3D->y = HEIGHT - (*s_map + *s_map * 0.1);
}

int	pixel(t_data *d, t_coor pos_pixel, int i, int j)
{
	if ((int)(pos_pixel.y + i * 4) / GRID >= d->height ||
		(int)(pos_pixel.x + j * 4) / GRID >= d->len ||
		(int)(pos_pixel.y + i * 4) / GRID < 0 ||
		(int)(pos_pixel.x + j * 4) / GRID < 0)
		return (0);
	else if (d->map[(int)(pos_pixel.y + i * 4) / GRID]
		[(int)(pos_pixel.x + j * 4) / GRID] == '1')
		return (WALLCOLOR);
	else if (d->p.pos.y == (pos_pixel.y + i * 4)
		&& d->p.pos.x == (pos_pixel.x + j * 4))
		return (BLANC);
	else
		return (0);
}

void	display_map(t_data *data, int size, t_coor p3d)
{
	t_coor	pos_pixel;
	int		pm;
	int		i;
	int		j;

	i = 0;
	pos_pixel.x = data->p.pos.x - size * 2;
	pos_pixel.y = data->p.pos.y - size * 2;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			pm = pixel(data, pos_pixel, i, j);
			if (i == 0 || j == 0 || i + 1 >= size || j + 1 >= size)
				put_pixel(&data->img3d, (int)p3d.y + i, (int)p3d.x + j, BLANC);
			else
				put_pixel(&data->img3d, (int)p3d.y + i, (int)p3d.x + j, pm);
			j++;
		}
		i++;
	}
}

void	minimap(t_data *data)
{
	int		size_minimap;
	t_coor	pos_minimap_img3d;

	minimap_init_img3d(&size_minimap, &pos_minimap_img3d);
	display_map(data, size_minimap, pos_minimap_img3d);
}
