/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:29:44 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/05 16:42:48 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap_init_img3d(t_frame *img3d, int *s_map, t_coor *pos_mnmap3D)
{
	if (img3d->width * 0.3 > img3d->height * 0.3)
		*s_map = img3d->height * 0.3;
	else
		*s_map = img3d->width * 0.3;
	pos_mnmap3D->x = img3d->width - (*s_map + *s_map * 0.1);
	pos_mnmap3D->y = img3d->height - (*s_map + *s_map * 0.1);
}

int	pick_pixel_img2d(t_frame *minimap, t_coor pos_mnmap, int i, int j)
{
	char	*addr;
	int		l;
	int		h;

	addr = minimap->addr;
	h = (int)pos_mnmap.y * minimap->length + i * 4 * minimap->length;
	l = (int)pos_mnmap.x * (minimap->bpp / 8) + j * 4 * (minimap->bpp / 8);
	return (*(int *)(addr + h + l));
}

void	display_map(t_data *data, int _s, t_coor p2d, t_coor p3d)
{
	t_frame	*map;
	int		pm;
	int		i;
	int		j;

	i = 0;
	map = &data->img2d;
	while (i < _s)
	{
		j = 0;
		while (j < _s)
		{
			pm = 0;
			if (p2d.y + i * 4 < map->height && p2d.x + j * 4 < map->width)
				pm = pick_pixel_img2d(map, p2d, i, j);
			if (i == 0 || j == 0 || i + 1 >= _s || j + 1 >= _s)
				put_pixel(&data->img3d, (int)p3d.y + i, (int)p3d.x + j, BLANC);
			else
				put_pixel(&data->img3d, (int)p3d.y + i, (int)p3d.x + j, pm);
			j++;
		}
		i++;
	}
}

void	minimap(t_data *data, t_frame *minimap, t_frame *img3d)
{
	int		size_minimap;
	t_coor	pos_minimap_img3d;
	t_coor	pos_player;
	t_coor	pos_minimap_img2d;

	minimap_init_img3d(img3d, &size_minimap, &pos_minimap_img3d);
	pos_player.x = minimap->triangle.milieu.x;
	pos_player.y = minimap->triangle.milieu.y;
	pos_minimap_img2d.x = pos_player.x - size_minimap * 2;
	pos_minimap_img2d.y = pos_player.y - size_minimap * 2;
	if (pos_minimap_img2d.x < 0)
		pos_minimap_img2d.x = 0;
	if (pos_minimap_img2d.y < 0)
		pos_minimap_img2d.y = 0;
	display_map(data, size_minimap, pos_minimap_img2d, pos_minimap_img3d);
}
