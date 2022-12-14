/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayTextures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:09:09 by mtellal           #+#    #+#             */
/*   Updated: 2022/10/22 10:17:42 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dcieling(t_frame *img3d, int c, t_coor pos_wall, int l)
{
	int		i;
	int		j;

	i = 0;
	while (i < pos_wall.y)
	{
		j = 0;
		while (j < l)
		{
			put_pixel(img3d, i, pos_wall.x + j, c);
			j++;
		}
		i++;
	}
}

void	dfloor(t_frame *img3d, int f, t_coor pos_wall, int l)
{
	int	i;
	int	j;

	i = pos_wall.y;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < l)
		{
			put_pixel(img3d, i, pos_wall.x + j, f);
			j++;
		}
		i++;
	}
}

int	f_pixelt(t_img *tw, t_drays *drays, t_coor dim, double sy)
{
	int		h;
	int		l;
	int		i;
	int		j;

	i = (int)dim.y;
	j = (int)dim.x;
	h = (int)drays->piw.y * tw->length + (int)(i * sy) *tw->length;
	l = (int)drays->piw.x * (tw->bpp / 8) + j * (tw->bpp / 8);
	return (*(int *)(tw->addr + l + h));
}

void	dwall(t_frame *im, t_img *tw, t_drays *d, double sy)
{
	int		i;
	int		j;
	int		p;
	t_coor	dim;

	i = 0;
	while (i < d->w.h)
	{
		j = 0;
		dim.y = i;
		while (j < d->w.l)
		{
			dim.x = j;
			p = f_pixelt(tw, d, dim, sy);
			put_pixel(im, (int)d->pw.y + i, (int)d->pw.x + j, p);
			j++;
		}
		i++;
	}
}
